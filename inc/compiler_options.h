#ifndef  INC_COMPILEROPTION_H
#define  INC_COMPILEROPTION_H

namespace minic {
namespace options{

  class CompilerOptions {
    public:
      CompilerOptions();
      void ParseCommandLine(int argc, char** argv);
      bool IsVerbose() const;
      bool ShouldEmitLLVM() const;
      bool ShouldEmitASM() const;
      bool UseJIT() const;
      std::string GetInputFile() const;
      std::string GetOutputFile() const;
      int GetOptimizationLevel() const;
    private:
      bool verbose_;
      bool emit_LLVM_;
      bool emit_ASM_;
      bool use_JIT_;
      std::string input_file_;
      std::string output_file_;
      int optimization_level_;
  };
}
}

#endif  // INC_COMPILEROPTION_H