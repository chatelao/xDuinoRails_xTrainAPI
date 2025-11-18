# Arduino Examples

This directory contains a collection of Arduino sketches that demonstrate how to use the xTrainAPI with various model train control libraries.

## Monitors

These examples demonstrate how to monitor events on the model railroad and print them to the serial port.

### NmraDcc_monitor

This example demonstrates how to use the `NmraDcc` library to monitor DCC commands on the track and translate them into `xTrainAPI` events. The events are then printed to the serial port in a human-readable format.

### MotorolaMaerklin_monitor

This example is a **non-functional placeholder** that demonstrates how to use the `laserlight/MotorolaMaerklin` library to monitor Motorola/Maerklin commands. The sketch will not compile without the `MotorolaMaerklin` library installed. It is intended to serve as a template for users who have access to this library.

### print_monitor

This example demonstrates how to use the `CmdLinePrinter` utility to print a hardcoded sequence of `xTrainAPI` events to the serial port. This is useful for quickly generating test data or for verifying that the `CmdLinePrinter` is working correctly.

## Command-Line Interfaces (CLIs)

These examples provide command-line interfaces for interacting with the `xTrainAPI`.

### XmlCLI

This example provides a command-line interface for parsing XML-formatted `xTrainAPI` commands from the serial input. It uses the `XmlParser` to deserialize the commands and then uses the `XmlPrinter` to serialize the corresponding event back to the serial port.

### debug_cli

This example provides a human-readable command-line interface for debugging the `xTrainAPI`. It uses the `CmdLineParser` to parse commands and then prints a confirmation message to the serial output.

### motor_cli

This example demonstrates how to control a motor using the `xTrainAPI`. It uses the `CmdLineParser` to receive locomotive speed and direction commands from the serial port and then controls the motor using the `XDuinoRails_MotorDriver` library.

## Testing and Debugging

These examples are used for testing and debugging the `xTrainAPI`.

### e2e_test

This example performs an end-to-end test of the command serialization and deserialization process. It uses a `StringStream` to mock the serial port, a `CmdLinePrinter` to serialize commands, and a `CmdLineParser` to deserialize them. The `VerifyingListener` class is used to check that the deserialized command matches the original one. This example is useful for verifying the correctness of the `xTrainAPI` implementation without the need for any hardware.

## Usage

To use these examples, you will need to have the required libraries installed in your Arduino environment. You can install them from the Arduino Library Manager. Once the libraries are installed, you can open the sketches in the Arduino IDE, compile them, and upload them to your Arduino board.
