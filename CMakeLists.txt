cmake_minimum_required(VERSION 3.16)
project(MiniC LANGUAGES CXX)

# --- Options ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- ALIASES ---
set(DEV_MAIN_DIR ${CMAKE_SOURCE_DIR})
set(BUILD_DIR ${CMAKE_BINARY_DIR})

# -- Set Variables --- 
set(LINTER_PATH ${DEV_MAIN_DIR}/tools/lint.py)
set(ANTLR_JAR ${DEV_MAIN_DIR}/antlr/antlr-4.13.1-complete.jar)
set(ANTLR4_RUNTIME /usr/include/antlr4-runtime)
set(GRAMMAR_FILE ${DEV_MAIN_DIR}/grammar/MiniC.g4)
set(ANTLR4_INCLUDE_DIR /usr/include/antlr4-runtime/)
set(GENERATED_ANTLR_SRC_DIR ${BUILD_DIR}/generated)
set(GTEST_MAIN_DIR ${DEV_MAIN_DIR}/tests/gtests)

# --- ANTLR4 setup ---
# You must download antlr-4.13.1-complete.jar manually

find_package(Java REQUIRED)
include(ExternalProject)

# Generate ANTLR files at build time
add_custom_command(
    OUTPUT ${GENERATED_ANTLR_SRC_DIR}/MiniCParser.cpp ${GENERATED_ANTLR_SRC_DIR}/MiniCParser.cpp ${GENERATED_ANTLR_SRC_DIR}/MiniCLexer.cpp ${GENERATED_ANTLR_SRC_DIR}/MiniCLexer.h ${GENERATED_ANTLR_SRC_DIR}/MiniCVisitor.h
    COMMAND java -jar ${ANTLR_JAR} -Dlanguage=Cpp -visitor -o ${GENERATED_ANTLR_SRC_DIR} ${GRAMMAR_FILE}
    DEPENDS ${GRAMMAR_FILE}
    COMMENT "Generating ANTLR4 parser files..."
)

# --- LLVM setup ---
find_package(LLVM REQUIRED CONFIG)
find_package(ZLIB REQUIRED)
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVM from ${LLVM_DIR}")
add_definitions(${LLVM_DEFINITIONS})

# --- Sources ---
file(GLOB_RECURSE SRC_FILES
    ${DEV_MAIN_DIR}/src/backend/*.cc
    ${DEV_MAIN_DIR}/src/frontend/*.cc
    ${DEV_MAIN_DIR}/src/optimisation/*.cc
    ${DEV_MAIN_DIR}/src/utils/*.cc
    ${GENERATED_ANTLR_SRC_DIR}/*.cpp
    )
    
include_directories(
    ${DEV_MAIN_DIR}/inc
    ${GENERATED_ANTLR_SRC_DIR}
    ${ANTLR4_RUNTIME}
    ${ANTLR4_INCLUDE_DIR}
    ${LLVM_INCLUDE_DIRS}
    )

add_executable(miniC ${SRC_FILES} ${DEV_MAIN_DIR}/src/main.cc)

# --- Link LLVM ---
llvm_map_components_to_libnames(llvm_libs
    core
    orcjit
    native
    irreader
    support
    )
    
target_link_libraries(miniC ${llvm_libs} ZLIB::ZLIB)

# --------------------------------------------------------------- TESTING SETUP ---------------------------------------------------------------
# --- Google Test setup ---
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Adds the gtest and gtest_main targets to build system.
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE TEST_FILES "tests/gtests/*.cc")

add_executable(miniCtests ${TEST_FILES} ${SRC_FILES} ${GTEST_MAIN_DIR}/main.cc)
target_link_libraries(miniCtests PRIVATE gtest gtest_main ${llvm_libs} ZLIB::ZLIB)

# --- Printing Some Info ---
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

macro(color_msg COLOR TEXT)
    message("${BoldYellow}>> [Info]:${COLOR} ${TEXT}${RESET}")
endmacro()

color_msg(${Green}    "MiniC compiler build configuration complete!")
color_msg(${BoldCyan} "[Linter] linter path: ${LINTER_PATH}")
color_msg(${BoldCyan} "[ANTLR4] Grammar: ${GRAMMAR_FILE} Includes: ${ANTLR4_INCLUDE_DIR} ANTLR_JAR: ${ANTLR_JAR} ANTLR4_RUNTIME: ${ANTLR4_RUNTIME} Output: ${GENERATED_ANTLR_SRC_DIR}")
color_msg(${BoldCyan} "[gTest]  main dir:${GTEST_MAIN_DIR}")

color_msg(${BoldBlue} "Source files: ${SRC_FILES}")
color_msg(${BoldBlue} "Test files: ${TEST_FILES}")
