    cmake_minimum_required(VERSION 3.10)

    # Project definition
    project(json LANGUAGES CXX)

    # C++ standard settings
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # Define include and source directories
    set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
    set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

    # Collect source files
    set(SOURCES
        # Types
        ${SRC_DIR}/types/json_value.cpp
        ${SRC_DIR}/types/json_null.cpp
        ${SRC_DIR}/types/json_boolean.cpp
        ${SRC_DIR}/types/json_number.cpp
        ${SRC_DIR}/types/json_string.cpp
        ${SRC_DIR}/types/json_array.cpp
        ${SRC_DIR}/types/json_object.cpp
        # Parser
        ${SRC_DIR}/parser/lexer.cpp
        ${SRC_DIR}/parser/parser.cpp
        # Core
        ${SRC_DIR}/json.cpp
    )

    # Create a static library target
    add_library(jsonlib STATIC ${SOURCES})

    # Specify public include directories
    target_include_directories(jsonlib PUBLIC ${INCLUDE_DIR})

    # Enable compiler warnings
    target_compile_options(jsonlib PRIVATE -Wall -Wextra)
