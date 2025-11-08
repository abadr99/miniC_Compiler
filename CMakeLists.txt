cmake_minimum_required(VERSION 3.16)
project(MiniC LANGUAGES CXX)

# --- Options ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- ANTLR4 setup ---
# You must download antlr-4.13.1-complete.jar manually
set(ANTLR_JAR ${CMAKE_SOURCE_DIR}/antlr/antlr-4.13.1-complete.jar)
set(ANTLR4_RUNTIME ${CMAKE_BINARY_DIR}/antlr4-runtime)

find_package(Java REQUIRED)
include(ExternalProject)

# Generate ANTLR files at build time
set(GRAMMAR_FILE ${CMAKE_SOURCE_DIR}/antlr/MiniC.g4)
set(GENERATED_SRC_DIR ${CMAKE_BINARY_DIR}/generated)

add_custom_command(
    OUTPUT ${GENERATED_SRC_DIR}/MiniCParser.cpp
    COMMAND java -jar ${ANTLR_JAR} -Dlanguage=Cpp -visitor -o ${GENERATED_SRC_DIR} ${GRAMMAR_FILE}
    DEPENDS ${GRAMMAR_FILE}
    COMMENT "Generating ANTLR4 parser files..."
)

# --- LLVM setup ---
find_package(LLVM REQUIRED CONFIG)
find_package(ZLIB REQUIRED)
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVM from ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# --- Sources ---
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${GENERATED_SRC_DIR}/*.cpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}/inc
    ${GENERATED_SRC_DIR}
)

# --- Executable ---
add_executable(MiniC ${SRC_FILES})

# --- Link LLVM ---
llvm_map_components_to_libnames(llvm_libs
    core
    orcjit
    native
    irreader
    support
)

target_link_libraries(MiniC ${llvm_libs} ZLIB::ZLIB)

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

color_msg(${Green} "MiniC compiler build configuration complete!")
color_msg(${Blue}  "Source files: ${SRC_FILES}")
color_msg(${Cyan}  "Linking against LLVM libraries: ${llvm_libs}")
color_msg(${Magenta} "Using ANTLR4 jar: ${ANTLR_JAR}")
color_msg(${Magenta} "Using build dir: ${CMAKE_BINARY_DIR}")
