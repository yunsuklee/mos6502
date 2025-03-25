cmake_minimum_required(VERSION 3.10)
project(MOS6502 VERSION 1.0.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Enable debug symbols
set(CMAKE_BUILD_TYPE Debug)

# Define source directories
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CORE_DIR ${SRC_DIR}/core)
set(UTIL_DIR ${SRC_DIR}/util)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SRC_DIR}
)

# Find all source files
file(GLOB CORE_SOURCES ${CORE_DIR}/*.c)
file(GLOB UTIL_SOURCES ${UTIL_DIR}/*.c)
set(MAIN_SOURCE ${SRC_DIR}/main.c)

# Create main executable
add_executable(mos6502 
    ${MAIN_SOURCE}
    ${CORE_SOURCES}
    ${UTIL_SOURCES}
)

# Set output directories
set_target_properties(mos6502 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Install target (optional)
install(TARGETS mos6502 DESTINATION bin)

# Add custom run target (equivalent to 'make run')
add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/bin/mos6502 examples/test_rom.bin -log output.log -ciclos 1000
    DEPENDS mos6502
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)