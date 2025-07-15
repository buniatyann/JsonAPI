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
        ${SRC_DIR}/json_array.cpp
        ${SRC_DIR}/json_boolean.cpp
        ${SRC_DIR}/json_null.cpp
        ${SRC_DIR}/json_number.cpp
        ${SRC_DIR}/json_object.cpp
        ${SRC_DIR}/json_string.cpp
        ${SRC_DIR}/json_value.cpp
        ${SRC_DIR}/json.cpp
        ${SRC_DIR}/lexer.cpp
        ${SRC_DIR}/parser.cpp
    )

    # Create a static library target
    add_library(jsonlib STATIC ${SOURCES})

    # Specify public include directories
    target_include_directories(jsonlib PUBLIC ${INCLUDE_DIR})

    # Enable compiler warnings
    target_compile_options(jsonlib PRIVATE -Wall -Wextra)
