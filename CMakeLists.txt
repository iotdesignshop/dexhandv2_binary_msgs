cmake_minimum_required(VERSION 3.0.0)
project(dexhand_connect VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# Is this a RP2040 Build or a Client Build? Look for a RP2040_BUILD variable
if (DEFINED RP2040_BUILD)
    message(STATUS "Configuring dexhandv2_binary_msgs for RP2040 Build")
else()
    message(STATUS "Configuring dexhandv2_binary_msgs for Client Build")
    
    #Find the required protobuf package
    find_package(Protobuf REQUIRED)

    # Include protobuf directories
    include_directories(${Protobuf_INCLUDE_DIRS})
endif()

# Define files
set(PROTO_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR})
file(GLOB_RECURSE PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto")

# Include generated *.pb.h files
include_directories(${PROTO_SRC_DIR})

# Generate C++ sources from the Proto files
if (DEFINED RP2040_BUILD)
    message(STATUS "Generating protobuf sources for RP2040 Build")
else()
    protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
endif()

add_library(dexhandv2_binary_msgs STATIC 
    src/dexhand_bm.cpp
    ${PROTO_SRCS}
    ${PROTO_HDRS})


message(STATUS "PROTO_SRC_DIR: ${PROTO_SRC_DIR}")
target_include_directories(dexhandv2_binary_msgs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${PROTO_SRC_DIR})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
