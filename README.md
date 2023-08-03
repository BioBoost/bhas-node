# BHAS - Node

This project contains the bare-metal firmware for a basic generic BHAS node.

Examples of such nodes include:

- Four Switch Node
- Master node

Currently this is still a work in progress and this firmware is more of a demo/test.

This firmware is part of the Bio Home Automation System - BHAS (pronounced BeeHas) and is currently designed for the Nucleo L467RG.

## Dependencies

* [bhas](https://github.com/BioBoost/mbed-bhas): The BHAS library
* [commander](https://github.com/BioBoost/mbed-commander): Serial commander library (special thanks @ [sillevl](https://github.com/sillevl))

## Device Configuration

Connect the device via the serial port with a baudrate of `115200` and double tap the reset button to get it into command mode.

In command mode the following commands are supported:

| Command | Description |
| --- | --- |
| `VERSION` | Get the firmware version and build timestamp |
| `NODEID` | Get the current Node ID |
| `NODEID=xx` | Set the Node ID |
| `GWID` | Get the current Gateway ID |
| `GWID=xx` | Set the Gateway ID |
| `RESET!` | Reboot the device |
| `FACTORYRESET!` | Reset the device to its factory defaults |
