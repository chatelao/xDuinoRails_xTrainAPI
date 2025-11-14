# xDuinoRails_xTrainAPI Arduino Library

This Arduino library provides an implementation of the xTrainAPI, a unified interface for model train control systems. It is designed to be extensible and support various protocols.

## Installation

1.  Download the latest release of this library from the [releases page](https://github.com/your-username/your-repo/releases).
2.  In the Arduino IDE, go to `Sketch > Include Library > Add .ZIP Library...` and select the downloaded file.
3.  The library will be available in the `Sketch > Include Library` menu.

## Getting Started

This library provides an abstract interface, `IUnifiedModelTrainListener`, which you can implement to handle events from a model train control system.

An example is provided in the `examples` directory to demonstrate how to use this library with the `NmraDcc` library to create a DCC decoder.

### DCC Decoder Example

The `DccDecoder` example shows how to create a simple DCC decoder that listens for speed and function commands.

To use the example:

1.  Open the Arduino IDE.
2.  Go to `File > Examples > xDuinoRails_xTrainAPI > DccDecoder`.
3.  Make sure you have the `NmraDcc` library installed.
4.  Define the `DCC_PIN` for your board.
5.  Upload the sketch to your Arduino board.
6.  Open the Serial Monitor to see the output.
