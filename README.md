# dexhandv2_binary_msgs
DexHand V2 Binary Message Structures for Exchanging Data Between Hardware and Client Libraries

## Google Protocol Buffers
The DexHand V2 Binary Message package usess Google Protocol Buffers internally to describe the message formats and to ensure cross-platform, cross-language, cross architecture support for the exchange of the messages across the USB connection to the DexHand. The RP2040 Microcontroller on the DexHand has the message definitions compiled into the C++-based firmware, and these messages can be interpreted by the C++ and Python clients on a variety of host architectures that connect with and exchange messages with the firmware

### Installing the Protocol Buffer compiler
```sudo apt install protobuf-compiler libprotobuf-dev```

