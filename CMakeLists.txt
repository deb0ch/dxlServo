cmake_minimum_required(VERSION 2.8)

project(dxlservo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -Wall -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -Wextra")

set(HEADER_FILES
  dxl_sdk_usb2ax/include/dynamixel.h
  dxl_sdk_usb2ax/src/dxl_hal.h
  src/DxlServo.hh)

set(SOURCE_FILES
  dxl_sdk_usb2ax/src/dxl_hal.c
  dxl_sdk_usb2ax/src/dynamixel.c
  src/DxlServo.cpp)

include_directories(dxl_sdk_usb2ax/include)

add_library(dxlservo STATIC ${SOURCE_FILES} ${HEADER_FILES})
