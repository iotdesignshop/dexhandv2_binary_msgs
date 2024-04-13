/***
 * @file dexhand_msg_types.h
 * @brief This file contains the message IDs for the dexhandv2_binary_msgs package.
 * @copyright Copyright (c) 2024 IoT Design Shop Inc.
*/

#pragma once

namespace dexhand {

enum DexhandMsgID {
    SERVO_STATUS_MSG = 0x01,            // For individual servo status
    SERVO_STATUS_LIST_MSG = 0x02,       // For lists of servo status messages
    NUM_MSGS
};


} // namespace dexhand

