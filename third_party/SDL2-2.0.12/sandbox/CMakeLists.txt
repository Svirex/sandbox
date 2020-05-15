cmake_minimum_required(VERSION 3.10)
project(sdl2 C)

# This is necessary on Windows, so the sdl2.dll lives next to the sample apps that use it
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FILAMENT_SAMPLES_BINARY_DIR})

set(OUR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(TARGET              sdl2)
set(SRC_DIR             ${OUR_DIR}/src)
set(PUBLIC_HDR_DIR      ${OUR_DIR}/include)


# General source files
file(GLOB SRCS
    ${SRC_DIR}/*.c
    ${SRC_DIR}/atomic/*.c
    ${SRC_DIR}/audio/*.c
    ${SRC_DIR}/audio/disk/*.c
    ${SRC_DIR}/audio/dsp/*.c
    ${SRC_DIR}/audio/dummy/*.c
    ${SRC_DIR}/cpuinfo/*.c
    ${SRC_DIR}/dynapi/*.c
    ${SRC_DIR}/events/*.c
    ${SRC_DIR}/file/*.c
    ${SRC_DIR}/joystick/*.c
    ${SRC_DIR}/joystick/steam/*.c
    ${SRC_DIR}/haptic/*.c
    ${SRC_DIR}/libm/*.c
    ${SRC_DIR}/power/*.c
    ${SRC_DIR}/render/*.c
    ${SRC_DIR}/render/*/*.c
    ${SRC_DIR}/stdlib/*.c
    ${SRC_DIR}/thread/*.c
    ${SRC_DIR}/timer/*.c
    ${SRC_DIR}/video/*.c
    ${SRC_DIR}/video/yuv2rgb/*.c
    ${SRC_DIR}/video/dummy/*.c
)

###################################################################################################
# Linux specific files
if (LINUX)
    file(GLOB SRCS_LINUX
            ${SRC_DIR}/core/unix/*.c
            ${SRC_DIR}/video/x11/*.c
            ${SRC_DIR}/thread/pthread/*.c
            ${SRC_DIR}/power/linux/*.c
            ${SRC_DIR}/filesystem/unix/*.c
            ${SRC_DIR}/timer/unix/*.c
            ${SRC_DIR}/joystick/linux/*.c
            ${SRC_DIR}/haptic/linux/*.c
            ${SRC_DIR}/loadso/dlopen/*.c
    )
    set(SRCS ${SRCS} ${SRCS_LINUX})
endif()
###################################################################################################

###################################################################################################

# include directories...
include_directories(
    ${PUBLIC_HDR_DIR}
)

add_definitions(-D_THREAD_SAFE)

# we're building a library
add_library(${TARGET} SHARED ${SRCS})

# libraries we're linking against
target_link_libraries(${TARGET} ${EXTRA_LIBS})

if(NOT MSVC)
    target_compile_options(${TARGET}
        PRIVATE -msse2
        PRIVATE -msse
        PRIVATE -mmmx
        PRIVATE -Wno-unused-variable
        PRIVATE -Wno-deprecated-declarations
        PRIVATE -Wno-switch
        PRIVATE -Wno-tautological-pointer-compare
        PRIVATE -Wno-parentheses-equality
    )
endif()

# specify where the public headers of this library are
target_include_directories(${TARGET} PUBLIC ${PUBLIC_HDR_DIR})

target_compile_options(${TARGET} PRIVATE -fvisibility=hidden)
