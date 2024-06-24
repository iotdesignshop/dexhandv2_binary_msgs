/***
 * @file dexhand_msg_types.h
 * @brief This file contains the message IDs for the dexhandv2_binary_msgs package.
 * @copyright Copyright (c) 2024 IoT Design Shop Inc.
*/

#pragma once

namespace dexhand {

enum DexhandMsgID {
    SERVO_FULL_STATUS_MSG = 0x01,            // Full status for an individual servo
    SERVO_DYNAMICS_LIST_MSG = 0x02,          // High frequency dynamics data for all servos
    SERVO_POSITION_UPDATE_CMD = 0x03,        // Update the position of one or more servos
    SERVO_VARS_LIST_MSG = 0x04,              // List of variables for all servos
    SERVO_VARS_UPDATE_CMD = 0x05,            // Update the variables for one or more servos
    FIRMWARE_VERSION_MSG = 0x06,             // Firmware version
    SAVE_FIRMWARE_TUNING_CMD = 0x07,         // Save firmware tuning values
    RESET_HAND_CMD = 0x08,                   // Reset the hand
    SERVO_REGISTER_WRITE_CMD = 0x09,         // Write a servo register
    HAND_PARAMS_WRITE_CMD = 0x0A,            // Write a hand parameter
    AUTO_TUNE_THUMB_CMD = 0x0B,              // Auto tune the thumb dynamics
    NUM_MSGS
};


} // namespace dexhand

