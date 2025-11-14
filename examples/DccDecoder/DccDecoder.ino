#include <Arduino.h>
#include <NmraDcc.h>
#include "xDuinoRails_xTrainAPI.h"

// DCC Address for this decoder
#define DCC_ADDRESS 3

// Create a DCC object
NmraDcc dcc;

// Custom implementation of the xTrainAPI listener
class DccDecoderListener : public ModelRail::IUnifiedModelTrainListener {
public:
    // Implement all pure virtual functions from the interface
    void onLocoSpeedChanged(const ModelRail::LocoHandle& loco, float speedPercent, ModelRail::Direction direction, int speedSteps) override {
        Serial.print("Speed changed for loco: ");
        Serial.print(loco.address);
        Serial.print(", Speed: ");
        Serial.print(speedPercent);
        Serial.print("%, Direction: ");
        Serial.println(direction == ModelRail::Direction::FORWARD ? "Forward" : "Reverse");
    }

    void onLocoFunctionChanged(const ModelRail::LocoHandle& loco, int fIndex, bool isActive) override {
        Serial.print("Function changed for loco: ");
        Serial.print(loco.address);
        Serial.print(", F");
        Serial.print(fIndex);
        Serial.print(": ");
        Serial.println(isActive ? "ON" : "OFF");
    }

    // Minimal implementation for other required virtual functions
    void onLocoFunctionAnalogValue(const ModelRail::LocoHandle& loco, int fIndex, uint8_t value) override {}
    void onLocoDispatchStateChanged(const ModelRail::LocoHandle& loco, bool isAcquired, std::string ownerId) override {}
    void onConsistLink(const ModelRail::LocoHandle& master, const ModelRail::LocoHandle& slave, ModelRail::ConsistType type, bool inverted) override {}
    void onConsistUnlink(const ModelRail::LocoHandle& slave) override {}
    void onTurnoutChanged(uint16_t address, bool isThrown, bool isFeedback) override {}
    void onSignalAspectChanged(uint16_t address, uint8_t aspectId, bool isFeedback) override {}
    void onAccessoryAnalogValue(uint16_t address, float value0to1) override {}
    void onAccessoryError(uint16_t address, uint8_t errorId, std::string errorMsg) override {}
    void onSensorStateChanged(uint32_t sensorId, bool isActive) override {}
    void onTrackPowerChanged(ModelRail::PowerState state) override {}
    void onFastClockUpdated(int64_t modelTimeUnix, float factor) override {}
    void onHardwareNodeAttached(std::string nodeUid, std::string productName, bool booster) override {}
    void onHardwareNodeLost(std::string nodeUid) override {}
    void onSystemMessage(std::string source, std::string message) override {}
    void onLocoDetectedOnBlock(uint32_t sensorId, const ModelRail::LocoHandle& loco, ModelRail::DecoderOrientation orientation) override {}
    void onLocoTelemetryData(const ModelRail::LocoHandle& loco, ModelRail::TelemetryType type, float value) override {}
    void onLocoExternalStateChanged(const ModelRail::LocoHandle& loco, ModelRail::ExternalState state) override {}
    void onLocoRailComRawData(const ModelRail::LocoHandle& loco, uint8_t appId, const std::vector<uint8_t>& data) override {}
    void onNewLocoDiscovered(const ModelRail::LocoHandle& loco, const std::string& name, const std::string& icon) override {}
    void onCvReadResult(const ModelRail::LocoHandle& loco, int cvNumber, uint8_t value, bool success) override {}
    void onSusiConfigRead(const ModelRail::LocoHandle& loco, uint8_t bankIndex, uint8_t susiIndex, uint8_t value) override {}
    void onConfigBlockLoaded(const ModelRail::LocoHandle& loco, std::string domain, const std::vector<uint8_t>& data) override {}
    void onProgressUpdate(std::string operation, float percent) override {}
};

DccDecoderListener dccListener;

// Callback from NmraDcc library for speed and direction packets
void notifyDccSpeed(uint16_t Addr, DCC_CONSIST_DIRECTION Dir, uint8_t Speed, DCC_SPEED_STEPS SpeedSteps) {
    if (Addr != DCC_ADDRESS) return;

    ModelRail::LocoHandle handle = {Addr, ModelRail::Protocol::DCC, 0};
    ModelRail::Direction direction = (Dir == DCC_CONSIST_DIRECTION_FWD) ? ModelRail::Direction::FORWARD : ModelRail::Direction::REVERSE;
    float speedPercent = (Speed / (float)((SpeedSteps == DCC_SPEED_STEPS_128) ? 126.0 : 28.0)) * 100.0;

    dccListener.onLocoSpeedChanged(handle, speedPercent, direction, SpeedSteps);
}

// Callback from NmraDcc library for function packets
void notifyDccFunc(uint16_t Addr, FN_GROUP FuncGrp, uint8_t FuncState) {
    if (Addr != DCC_ADDRESS) return;

    ModelRail::LocoHandle handle = {Addr, ModelRail::Protocol::DCC, 0};

    if (FuncGrp == FN_GROUP_0_4) {
        for (int i = 0; i <= 4; ++i) {
            dccListener.onLocoFunctionChanged(handle, i, (FuncState >> i) & 0x01);
        }
    }
    // Add other function groups as needed
}

void setup() {
    Serial.begin(115200);
    Serial.println("DCC Decoder Example using xTrainAPI");

    // Configure the DCC library
    dcc.pin(DCC_PIN, 0); // Requires DCC_PIN to be defined by your board
    dcc.init(MAN_ID_DIY, 1, FLAGS_OUTPUT_ENABLE | FLAGS_AUTO_ACK_ENABLE, 0);

    // Register DCC callbacks
    dcc.setCV(CV_MULTIFUNCTION_PRIMARY_ADDRESS, DCC_ADDRESS);
    dcc.registerSpeedPacketCallback(notifyDccSpeed, true);
    dcc.registerFunctionPacketCallback(notifyDccFunc, true);
}

void loop() {
    dcc.process();
}
