
cmake_minimum_required(VERSION 3.16)

get_filename_component(REPO_NAME "${CMAKE_SOURCE_DIR}" NAME)
string(MAKE_C_IDENTIFIER "${REPO_NAME}" PROJECT_NAME_SAFE)

project(${PROJECT_NAME_SAFE} LANGUAGES C CXX)

# ============================================================
# ACTIVE SOURCE
# ============================================================

if(NOT DEFINED ACTIVE_SOURCE OR ACTIVE_SOURCE STREQUAL "")
    message(FATAL_ERROR
        "ACTIVE_SOURCE was not supplied. "
        "Run the project through the VS Code task."
    )
endif()

file(TO_CMAKE_PATH "${ACTIVE_SOURCE}" ACTIVE_SOURCE)

get_filename_component(
    ACTIVE_SOURCE
    "${ACTIVE_SOURCE}"
    ABSOLUTE
)

if(NOT EXISTS "${ACTIVE_SOURCE}")
    message(FATAL_ERROR
        "The selected source file does not exist: ${ACTIVE_SOURCE}"
    )
endif()

get_filename_component(
    ACTIVE_OUTPUT_NAME
    "${ACTIVE_SOURCE}"
    NAME_WE
)

string(
    MAKE_C_IDENTIFIER
    "${ACTIVE_OUTPUT_NAME}"
    TARGET_NAME
)

# ============================================================
# SOURCE DEPENDENCY COLLECTION
#
# Start with the active source file.
#
# Follow local includes:
#     #include "player.h"
#
# Add matching implementation files:
#     player.c
#     player.cc
#     player.cpp
#     player.cxx
#
# Search ONLY:
#     - The including file's directory
#     - The project root
#
# Do not scan unrelated folders.
# ============================================================

set_property(
    GLOBAL PROPERTY COLLECTED_SOURCES ""
)

set_property(
    GLOBAL PROPERTY COLLECTED_HEADERS ""
)

set_property(
    GLOBAL PROPERTY VISITED_FILES ""
)

function(collect_dependencies CURRENT_FILE)

    get_filename_component(
        CURRENT_FILE
        "${CURRENT_FILE}"
        ABSOLUTE
    )

    get_property(
        VISITED
        GLOBAL PROPERTY VISITED_FILES
    )

    if(CURRENT_FILE IN_LIST VISITED)
        return()
    endif()

    set_property(
        GLOBAL APPEND PROPERTY VISITED_FILES
        "${CURRENT_FILE}"
    )

    get_filename_component(
        FILE_EXT
        "${CURRENT_FILE}"
        EXT
    )

    string(TOLOWER "${FILE_EXT}" FILE_EXT)

    if(FILE_EXT MATCHES "^\\.(c|cc|cpp|cxx)$")

        set_property(
            GLOBAL APPEND PROPERTY COLLECTED_SOURCES
            "${CURRENT_FILE}"
        )

    else()

        set_property(
            GLOBAL APPEND PROPERTY COLLECTED_HEADERS
            "${CURRENT_FILE}"
        )

    endif()

    get_filename_component(
        CURRENT_DIR
        "${CURRENT_FILE}"
        DIRECTORY
    )

    # Detect local includes only.
    # System includes such as <stdio.h> are ignored.

    file(
        STRINGS
        "${CURRENT_FILE}"
        INCLUDE_LINES
        REGEX "^[ \t]*#[ \t]*include[ \t]*\"[^\"]+\""
    )

    foreach(LINE IN LISTS INCLUDE_LINES)

        string(
            REGEX REPLACE
            "^[ \t]*#[ \t]*include[ \t]*\"([^\"]+)\".*"
            "\\1"
            INCLUDED_FILE
            "${LINE}"
        )

        set(
            HEADER_PATH
            "${CURRENT_DIR}/${INCLUDED_FILE}"
        )

        if(NOT EXISTS "${HEADER_PATH}")

            set(
                HEADER_PATH
                "${CMAKE_SOURCE_DIR}/${INCLUDED_FILE}"
            )

        endif()

        if(NOT EXISTS "${HEADER_PATH}")
            continue()
        endif()

        get_filename_component(
            HEADER_PATH
            "${HEADER_PATH}"
            ABSOLUTE
        )

        # Follow includes inside the header, too.

        collect_dependencies("${HEADER_PATH}")

        get_filename_component(
            HEADER_DIR
            "${HEADER_PATH}"
            DIRECTORY
        )

        get_filename_component(
            HEADER_NAME
            "${HEADER_PATH}"
            NAME_WE
        )

        # Add implementation files matching the header.

        foreach(SOURCE_EXT c cc cpp cxx)

            set(
                RELATED_SOURCE
                "${HEADER_DIR}/${HEADER_NAME}.${SOURCE_EXT}"
            )

            if(EXISTS "${RELATED_SOURCE}")
                collect_dependencies("${RELATED_SOURCE}")
            endif()

        endforeach()

    endforeach()

endfunction()

# ============================================================
# COLLECT RELATED FILES
# ============================================================

collect_dependencies("${ACTIVE_SOURCE}")

get_property(
    TARGET_SOURCES
    GLOBAL PROPERTY COLLECTED_SOURCES
)

get_property(
    TARGET_HEADERS
    GLOBAL PROPERTY COLLECTED_HEADERS
)

list(REMOVE_DUPLICATES TARGET_SOURCES)
list(REMOVE_DUPLICATES TARGET_HEADERS)

# ============================================================
# BUILD EXECUTABLE
# ============================================================

add_executable(
    ${TARGET_NAME}
    ${TARGET_SOURCES}
)

# ============================================================
# INCLUDE DIRECTORIES
# ============================================================

set(
    INCLUDE_DIRS
    "${CMAKE_SOURCE_DIR}"
)

foreach(FILE_PATH IN LISTS TARGET_SOURCES TARGET_HEADERS)

    get_filename_component(
        FILE_DIR
        "${FILE_PATH}"
        DIRECTORY
    )

    list(
        APPEND
        INCLUDE_DIRS
        "${FILE_DIR}"
    )

endforeach()

list(REMOVE_DUPLICATES INCLUDE_DIRS)

target_include_directories(
    ${TARGET_NAME}
    PRIVATE
    ${INCLUDE_DIRS}
)

# ============================================================
# GCC WARNINGS, DEBUGGING AND STATIC ANALYSIS
#
# Original compiler flags preserved.
# NO compiler or toolchain paths are changed.
# ============================================================

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")

    target_compile_options(
        ${TARGET_NAME}
        PRIVATE

        -Wall
        -Wextra
        -Wpedantic

        -g
        -Og

        -fanalyzer
    )

endif()

# ============================================================
# LINUX MATH LIBRARY
# ============================================================

if(UNIX AND NOT APPLE)

    target_link_libraries(
        ${TARGET_NAME}
        PRIVATE
        m
    )

endif()

# ============================================================
# OUTPUT DIRECTORY
#
# Build system:
#     ./build/
#
# Executables:
#     ./compiled/
# ============================================================

file(
    MAKE_DIRECTORY
    "${CMAKE_SOURCE_DIR}/compiled"
)

set_target_properties(
    ${TARGET_NAME}
    PROPERTIES

    OUTPUT_NAME
    "${ACTIVE_OUTPUT_NAME}"

    RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/compiled"
)

foreach(
    CONFIG
    DEBUG
    RELEASE
    RELWITHDEBINFO
    MINSIZEREL
)

    set_target_properties(
        ${TARGET_NAME}
        PROPERTIES

        "RUNTIME_OUTPUT_DIRECTORY_${CONFIG}"
        "${CMAKE_SOURCE_DIR}/compiled"
    )

endforeach()

# ============================================================
# DISPLAY EXACTLY WHICH FILES ARE COMPILED
# ============================================================

message(STATUS "")
message(STATUS "========================================")
message(STATUS "ACTIVE SOURCE:")
message(STATUS "  ${ACTIVE_SOURCE}")
message(STATUS "")
message(STATUS "SOURCE FILES BEING COMPILED:")

foreach(SRC IN LISTS TARGET_SOURCES)
    message(STATUS "  ${SRC}")
endforeach()

message(STATUS "========================================")
message(STATUS "")
