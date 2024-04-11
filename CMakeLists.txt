cmake_minimum_required(VERSION 3.0.0)
project(dexhand_connect VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# Is this a RP2040 Build or a Client Build? Look for a RP2040_BUILD variable
if (DEFINED RP2040_BUILD)
    message(STATUS "Configuring dexhandv2_binary_msgs for RP2040 Build")

    set(PROTO_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/generated/rp2040-cpp)
else()
    message(STATUS "Configuring dexhandv2_binary_msgs for Client Build")
    
    #Find the required protobuf package
    find_package(Protobuf REQUIRED)

    # Include protobuf directories
    include_directories(${Protobuf_INCLUDE_DIRS})

    set(PROTO_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/generated/client-cpp)
endif()

file(MAKE_DIRECTORY ${PROTO_OUTPUT_DIR})

# Define files
file(GLOB_RECURSE PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto")

# Create generated file names
foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(PROTO_FILE_NAME ${PROTO_FILE} NAME)
    string(REPLACE ".proto" ".pb" PROTO_FILE_NAME ${PROTO_FILE_NAME})
    list(APPEND PROTO_SRCS "${PROTO_OUTPUT_DIR}/${PROTO_FILE_NAME}.cc")
    list(APPEND PROTO_HDRS "${PROTO_OUTPUT_DIR}/${PROTO_FILE_NAME}.h")
endforeach()

# Include the generated files in the project
include_directories(${PROTO_OUTPUT_DIR})

# Generate C++ sources from the Proto files
if (DEFINED RP2040_BUILD)
    # Custom command to use nanopb to generate the C files for the RP2040
    add_custom_command(
        OUTPUT ${PROTO_SRCS} ${PROTO_HDRS}
        COMMAND python3
        ARGS ${CMAKE_CURRENT_SOURCE_DIR}/nanopb/generator/nanopb_generator.py ${PROTO_FILES} -D ${PROTO_OUTPUT_DIR} -I ${CMAKE_CURRENT_SOURCE_DIR}/proto -S .cc
        DEPENDS ${PROTO_FILES}
    )
else()
    # Custom command to run protoc into custom output directory
    add_custom_command(
        OUTPUT ${PROTO_SRCS} ${PROTO_HDRS}
        COMMAND ${Protobuf_PROTOC_EXECUTABLE}
        ARGS --cpp_out=${PROTO_OUTPUT_DIR} -I ${CMAKE_CURRENT_SOURCE_DIR}/proto ${PROTO_FILES}
        DEPENDS ${PROTO_FILES}
    )
endif()

# RP2040 build also needs to compile in some source from nanopb
if (DEFINED RP2040_BUILD)
    file(GLOB_RECURSE NANOPB_FILES "${CMAKE_CURRENT_SOURCE_DIR}/nanopb/pb_*.c")
endif()

add_library(dexhandv2_binary_msgs STATIC 
    ${PROTO_SRCS}
    ${PROTO_HDRS}
    ${NANOPB_FILES})




message(STATUS "PROTO_SRC_DIR: ${PROTO_SRC_DIR}")
target_include_directories(dexhandv2_binary_msgs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${PROTO_OUTPUT_DIR})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
