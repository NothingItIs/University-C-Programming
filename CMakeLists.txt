cmake_minimum_required(VERSION 3.16)

get_filename_component(REPO_NAME "${CMAKE_SOURCE_DIR}" NAME)

string(MAKE_C_IDENTIFIER "${REPO_NAME}" PROJECT_NAME_SAFE)

project(${PROJECT_NAME_SAFE} LANGUAGES C CXX)


# ------------------------------------------------------------
# The currently open source file is passed in from tasks.json:
#
#     -DACTIVE_SOURCE=${file}
#
# Example:
#
#     C:/Users/.../TBG-2-C/tests/test.c
# ------------------------------------------------------------

if(NOT DEFINED ACTIVE_SOURCE)
    message(FATAL_ERROR
        "ACTIVE_SOURCE was not supplied. "
        "Run the project through the VS Code task."
    )
endif()


# Convert Windows-style paths to normal CMake-style paths.
file(TO_CMAKE_PATH "${ACTIVE_SOURCE}" ACTIVE_SOURCE)


# Make sure the selected file actually exists.
if(NOT EXISTS "${ACTIVE_SOURCE}")
    message(FATAL_ERROR
        "The selected source file does not exist: ${ACTIVE_SOURCE}"
    )
endif()


# ------------------------------------------------------------
# Get the filename of the active source file.
#
# Example:
#
#     test.c
#
# becomes:
#
#     ACTIVE_OUTPUT_NAME = test
# ------------------------------------------------------------

get_filename_component(
    ACTIVE_OUTPUT_NAME
    "${ACTIVE_SOURCE}"
    NAME_WE
)


# CMake target names need to be safe identifiers.
string(
    MAKE_C_IDENTIFIER
    "${ACTIVE_OUTPUT_NAME}"
    TARGET_NAME
)


# ------------------------------------------------------------
# Find all C and C++ source files in the project.
# ------------------------------------------------------------

file(
    GLOB_RECURSE
    ALL_SOURCES
    CONFIGURE_DEPENDS

    "${CMAKE_SOURCE_DIR}/*.c"
    "${CMAKE_SOURCE_DIR}/*.cc"
    "${CMAKE_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/*.cxx"
)


# ------------------------------------------------------------
# Find all header files.
# ------------------------------------------------------------

file(
    GLOB_RECURSE
    ALL_HEADERS
    CONFIGURE_DEPENDS

    "${CMAKE_SOURCE_DIR}/*.h"
    "${CMAKE_SOURCE_DIR}/*.hh"
    "${CMAKE_SOURCE_DIR}/*.hpp"
    "${CMAKE_SOURCE_DIR}/*.hxx"
)


# ------------------------------------------------------------
# Do not include generated files inside build/ or compiled/.
# ------------------------------------------------------------

list(
    FILTER
    ALL_SOURCES
    EXCLUDE
    REGEX "/build/|/compiled/"
)

list(
    FILTER
    ALL_HEADERS
    EXCLUDE
    REGEX "/build/|/compiled/"
)


# ------------------------------------------------------------
# Start the target with the currently selected source file.
# ------------------------------------------------------------

set(
    TARGET_SOURCES
    "${ACTIVE_SOURCE}"
)


# ------------------------------------------------------------
# Add supporting source files automatically.
#
# Any other source file containing a REAL main() is NOT added,
# because that would create multiple main() definitions.
#
# Commented-out main() functions are ignored.
#
# Example:
#
#     // int main(void) { ... }
#
# does NOT count as a real main().
# ------------------------------------------------------------

foreach(SRC IN LISTS ALL_SOURCES)

    # The active source is already included.
    if("${SRC}" STREQUAL "${ACTIVE_SOURCE}")
        continue()
    endif()


    # Read the source file as text.
    file(
        READ
        "${SRC}"
        SOURCE_CONTENT
    )


    # Make a separate copy used only for detecting main().
    set(
        SOURCE_FOR_MAIN_CHECK
        "${SOURCE_CONTENT}"
    )


    # --------------------------------------------------------
    # Remove /* ... */ block comments.
    # --------------------------------------------------------

    string(
        REGEX REPLACE
        "/\\*([^*]|\\*+[^*/])*\\*+/"
        ""
        SOURCE_FOR_MAIN_CHECK
        "${SOURCE_FOR_MAIN_CHECK}"
    )


    # --------------------------------------------------------
    # Remove // single-line comments.
    # --------------------------------------------------------

    string(
        REGEX REPLACE
        "//[^\r\n]*"
        ""
        SOURCE_FOR_MAIN_CHECK
        "${SOURCE_FOR_MAIN_CHECK}"
    )


    # --------------------------------------------------------
    # Look for a real:
    #
    #     int main(
    #
    # after comments have been removed.
    # --------------------------------------------------------

    string(
        REGEX MATCH
        "(^|[\r\n])[ \t]*int[ \t\r\n]+main[ \t\r\n]*\\("
        SOURCE_HAS_MAIN
        "${SOURCE_FOR_MAIN_CHECK}"
    )


    # --------------------------------------------------------
    # If there is no real main(), treat the file as a
    # supporting implementation file.
    # --------------------------------------------------------

    if(NOT SOURCE_HAS_MAIN)

        list(
            APPEND
            TARGET_SOURCES
            "${SRC}"
        )

    endif()

endforeach()


# ------------------------------------------------------------
# Build one executable from:
#
#     active source file
#
# plus:
#
#     supporting source files without a real main()
# ------------------------------------------------------------

add_executable(
    ${TARGET_NAME}
    ${TARGET_SOURCES}
)


# ------------------------------------------------------------
# Link the C math library on Linux.
# ------------------------------------------------------------

if(UNIX AND NOT APPLE)

    target_link_libraries(
        ${TARGET_NAME}
        PRIVATE
        m
    )

endif()


# ------------------------------------------------------------
# GCC warnings, debugging and static analysis.
#
# This DOES NOT change your compiler.
#
# Your existing MSYS2 UCRT64 GCC remains unchanged.
# ------------------------------------------------------------

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")

    target_compile_options(
        ${TARGET_NAME}
        PRIVATE

        # Useful warnings
        -Wall
        -Wextra
        -Wpedantic

        # Debug information for GDB
        -g

        # Debug-friendly optimisation
        -Og

        # GCC static analyser
        -fanalyzer
    )

endif()


# ------------------------------------------------------------
# Build include-directory list automatically.
#
# Includes:
#
#     project root
#     every source directory
#     every header directory
# ------------------------------------------------------------

set(
    INCLUDE_DIRS
    "${CMAKE_SOURCE_DIR}"
)


foreach(SRC IN LISTS ALL_SOURCES)

    get_filename_component(
        SRC_DIR
        "${SRC}"
        DIRECTORY
    )

    list(
        APPEND
        INCLUDE_DIRS
        "${SRC_DIR}"
    )

endforeach()


foreach(HEADER IN LISTS ALL_HEADERS)

    get_filename_component(
        HEADER_DIR
        "${HEADER}"
        DIRECTORY
    )

    list(
        APPEND
        INCLUDE_DIRS
        "${HEADER_DIR}"
    )

endforeach()


list(
    REMOVE_DUPLICATES
    INCLUDE_DIRS
)


target_include_directories(
    ${TARGET_NAME}
    PRIVATE
    ${INCLUDE_DIRS}
)


# ------------------------------------------------------------
# All final executables go into:
#
#     ./compiled/
#
# CMake's internal build files remain in:
#
#     ./build/
# ------------------------------------------------------------

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


# ------------------------------------------------------------
# Also force the same output location for
# multi-configuration generators.
# ------------------------------------------------------------

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