Hier ist das vollständige **Data Dictionary** der `UnifiedTrainAPI` als GitHub-optimierte Markdown-Tabelle. Du kannst diesen Block direkt in deine `README.md` oder Wiki-Seite kopieren.

# UnifiedTrainAPI Data Dictionary

Diese Tabelle beschreibt alle Felder, Parameter und Datentypen, die in der `UnifiedTrainAPI` verwendet werden.

| Kategorie | Feld / Parameter | Datentyp | Beschreibung | Gültiger Bereich / Werte | Anmerkungen |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Core** | `LocoHandle.address` | `uint16_t` | Die digitale Adresse des Decoders. | `1` - `10239` (DCC)<br>`1` - `255` (MM)<br>`1` - `127` (SX) | Wird ignoriert, falls `mfxUid` gesetzt ist. |
| **Core** | `LocoHandle.protocol` | `enum` | Das verwendete Kommunikationsprotokoll. | `DCC`, `MM_I`, `MM_II`, `MFX`, `SELECTRIX`, `SX2`, `LOCONET`, `BIDIB`, `XPRESSNET`, `CAN_GENERIC` | Bestimmt den zu verwendenden Treiber. |
| **Core** | `LocoHandle.mfxUid` | `uint32_t` | Eindeutige Hardware-ID (UID) für mfx/BiDiB. | `0` = Inaktiv<br>`>0` = Gültige UID | Hat Vorrang vor der Adresse (Routing-Priorität). |
| **Core** | `Protocol` | `enum` | Liste aller unterstützten Protokolle. | Siehe `LocoHandle.protocol`. | Definiert im `Protocol` Enum. |
| **Core** | `Direction` | `enum` | Logische Fahrtrichtung. | `REVERSE` (0)<br>`FORWARD` (1)<br>`UNKNOWN` (2) | Genutzt für Befehle und Rückmeldung. |
| **Traffic** | `speedPercent` | `float` | Zielgeschwindigkeit der Lokomotive. | `0.0` (Stop) bis `100.0` (Vmax) | Muss vom Treiber in Fahrstufen (14/28/128) umgerechnet werden. |
| **Traffic** | `speedSteps` | `int` | Auflösung der Fahrstufen für den Befehl. | `14`, `28`, `128` | Wichtig für korrekte DCC-Paket-Generierung. |
| **Traffic** | `fIndex` | `int` | Index der Funktionstaste. | `0` (Licht)<br>`1` - `32767` (Aux) | RCN-227 definiert bis F68, `int` ist zukunftssicher. |
| **Traffic** | `isActive` | `bool` | Status einer binären Funktion (Schalter). | `true` = AN<br>`false` = AUS | Standard für F-Tasten. |
| **Traffic** | `value` (Analog) | `uint8_t` | Wert einer analogen Funktion (Druck/Intensität). | `0` bis `255` | Für `onLocoFunctionAnalogValue` (z.B. WiThrottle). |
| **Traffic** | `isAcquired` | `bool` | Status der Slot-Verwaltung (Dispatching). | `true` = Von Regler übernommen<br>`false` = Freigegeben | Relevant für LocoNet/XpressNet Arbitrierung. |
| **Traffic** | `ownerId` | `string` | ID des Geräts, das die Lok steuert. | z.B. "Throttle \#54", "JMRI" | Debug-Info. |
| **Traffic** | `ConsistType` | `enum` | Methode der Mehrfachtraktion. | `ADVANCED_DCC` (CV19)<br>`UNIVERSAL_HOST` (Software)<br>`MU_LOCONET` | Bestimmt die Art der Verlinkung/Adressierung. |
| **Traffic** | `inverted` | `bool` | Orientierung im Verbund. | `true` = Slave fährt entgegengesetzt<br>`false` = Gleiche Richtung | Für `onConsistLink`. |
| **Accessory** | `address` | `uint16_t` | Adresse des Zubehör-Decoders. | Protokollabhängig (meist `1`-`2048`) | Für Weichen und Signale. |
| **Accessory** | `isThrown` | `bool` | Zustand einer Standard-Weiche. | `true` = Abzweig/Rot<br>`false` = Gerade/Grün | Basisfunktion. |
| **Accessory** | `isFeedback` | `bool` | Quelle des Events. | `true` = Echte Rückmeldung (RailCom)<br>`false` = Befehlsecho | Wichtig für Automatik-Validierung (Sicherheit). |
| **Accessory** | `aspectId` | `uint8_t` | Signalbegriff (Aspect). | `0` bis `255` | Für komplexe Signale (Hp0, Hp1, Sh1...). |
| **Accessory** | `value0to1` | `float` | Analoger Zubehörwert (Servo/Dimmer). | `0.0` bis `1.0` | Normalisierter Float. |
| **Accessory** | `errorId` | `uint8_t` | Diagnose-Fehlercode. | `1`=OpenLoad<br>`2`=Overload/Short<br>`3`=Stall | Hardware-Diagnose (BiDiB/RailCom Port Status). |
| **Accessory** | `errorMsg` | `string` | Lesbare Fehlerbeschreibung. | Text | Für UI-Anzeige. |
| **System** | `PowerState` | `enum` | Globaler Stromstatus. | `OFF` (0)<br>`ON` (1)<br>`EMERGENCY_STOP` (2)<br>`SHORT_CIRCUIT` (3) | Unterscheidet logischen Nothalt von physischem Kurzschluss. |
| **System** | `modelTimeUnix` | `int64_t` | Aktuelle Modellzeit (RCN-211). | Unix Timestamp (Sekunden seit 1970) | Enthält Jahr, Monat, Tag, Zeit für DCC Time/Date Pakete. |
| **System** | `factor` | `float` | Zeitbeschleunigungsfaktor. | z.B. `1.0` (Echtzeit), `4.0` (Schnell) | Sync für Handregler-Uhren (LocoNet/XpressNet). |
| **System** | `nodeUid` | `string` | Unique Hardware ID eines Bus-Knotens. | z.B. "05:00:AB:C1" | Identifiziert Booster/Melder eindeutig im Bus-Baum. |
| **System** | `productName` | `string` | Produktname der Hardware. | z.B. "GBM16T", "Z21" | UI-Anzeige der Topologie. |
| **System** | `booster` | `bool` | Fähigkeit zur Stromversorgung. | `true` = Ist Booster<br>`false` = Nur Logik | Filter für UI (Power Management). |
| **System** | `message` | `string` | Systemweite Textnachricht. | Text | Chat, Logs oder LISSY-Text. |
| **Telemetry** | `sensorId` | `uint32_t` | ID eines Rückmelders/Blocks. | Systemabhängige 32-Bit ID | Mappt auf S88 Port, LNet Sensor, BiDiB Input. |
| **Telemetry** | `DecoderOrientation`| `enum` | Aufgleisrichtung der Lok (RCN-217). | `NORMAL` (Kamin vor)<br>`INVERTED` (Tender vor)<br>`UNKNOWN` | Kritisch für Pendelzugsteuerung und Automatik. |
| **Telemetry** | `ExternalState` | `enum` | Externe Beeinflussung. | `FREE_RUN`<br>`STOPPED_BY_ABC`<br>`STOPPED_BY_DC`<br>`STOPPED_BY_HLU` | Zeigt an, ob Strecke die Lok bremst (trotz Throttle \> 0). |
| **Telemetry** | `TelemetryType` | `enum` | Art des Messwertes. | `SPEED`, `LOAD`, `VOLTAGE`, `CURRENT`, `FUEL`, `TEMP`, `QOS`, `ODOMETER` | Definiert Einheit von `value`. |
| **Telemetry** | `value` (Telemetry)| `float` | Der Messwert. | KM/H, %, Volt, Ampere, °C | Abhängig von `TelemetryType`. |
| **Telemetry** | `appId` | `uint8_t` | RailCom Applikations-ID. | `0` bis `255` | Für proprietäre Rohdaten (Hersteller-Spezifisch). |
| **Telemetry** | `data` (Raw) | `vector<u8>`| Rohdaten-Payload. | Byte Array | Für RailCom Raw oder Config Blocks. |
| **Config** | `cvNumber` | `int` | Index der Konfigurationsvariable. | `1` bis `1024` (DCC)<br>`1` bis `65535` (Index) | Adresse im Decoder-Speicher. |
| **Config** | `bankIndex` | `uint8_t` | Sound-Bank für SUSI. | `0` bis `3` | Meist via CV 1024/897 gemappt. |
| **Config** | `susiIndex` | `uint8_t` | Parameter innerhalb der SUSI-Bank. | `0` bis `255` | Die "CV" im SUSI-Modul. |
| **Config** | `domain` | `string` | Typ des Massendaten-Blocks. | "ICON", "FIRMWARE", "MFX\_CONFIG" | Kontext für `onConfigBlockLoaded`. |
| **Config** | `operation` | `string` | Name des laufenden Vorgangs. | z.B. "Reading CV List" | Für Ladebalken/UI. |
| **Config** | `percent` | `float` | Fortschritt. | `0.0` bis `100.0` | UI Feedback. |
| **Config** | `success` | `bool` | Ergebnis einer Operation. | `true` = ACK empfangen<br>`false` = Timeout/NACK | Erfolgskontrolle für CV-Reads. |
