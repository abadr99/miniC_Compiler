#include <iostream>
#include <string>
#include "compiler_options.h"

using namespace minic::options;

CompilerOptions::CompilerOptions()
    : verbose_(false),
      emit_LLVM_(false),
      emit_ASM_(false),
      use_JIT_(false),
      input_file_(""),
      output_file_(""),
      optimization_level_(0) { /* EMPTY */ }

void CompilerOptions::ParseCommandLine(int argc, char** argv) {
    // Simple command-line parsing logic
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--verbose") {
            verbose_ = true;
        } else if (arg == "--emit-llvm") {
            emit_LLVM_ = true;
        } else if (arg == "--emit-asm") {
            emit_ASM_ = true;
        } else if (arg == "--use-jit") {
            use_JIT_ = true;
        } else if (arg == "--input" && i + 1 < argc) {
            input_file_ = argv[++i];
        } else if (arg == "--output" && i + 1 < argc) {
            output_file_ = argv[++i];
        } else if (arg == "--opt-level" && i + 1 < argc) {
            optimization_level_ = std::stoi(argv[++i]);
        } else {
            // todo: suggest "Do you mean" for unknown options
            std::cerr << "Unknown option: " << arg << std::endl;
        }
    }
}

bool CompilerOptions::IsVerbose() const {
    return verbose_;
}

bool CompilerOptions::ShouldEmitLLVM() const {
    return emit_LLVM_;
}

bool CompilerOptions::ShouldEmitASM() const {
    return emit_ASM_;
}

bool CompilerOptions::UseJIT() const {
    return use_JIT_;
}

std::string CompilerOptions::GetInputFile() const {
    return input_file_;
}

std::string CompilerOptions::GetOutputFile() const {
    return output_file_;
}

int CompilerOptions::GetOptimizationLevel() const {
    return optimization_level_;
}


