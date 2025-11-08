#include <gtest/gtest.h>

#include "compiler_options.h"

using namespace minic::utils;

// Test default constructor values
TEST(CompilerOptionsTest, DefaultConstructor) {
    CompilerOptions options;
    EXPECT_FALSE(options.IsVerbose());
    EXPECT_FALSE(options.ShouldEmitLLVM());
    EXPECT_FALSE(options.ShouldEmitASM());
    EXPECT_FALSE(options.UseJIT());
    EXPECT_EQ(options.GetInputFile(), "");
    EXPECT_EQ(options.GetOutputFile(), "");
    EXPECT_EQ(options.GetOptimizationLevel(), 0);
}

// Test JIT mode
TEST(CompilerOptionsTest, JITMode) {
    const char* argv[] = {"./miniC", "--jit", "--input", "test.mc"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    
    CompilerOptions options;
    options.ParseCommandLine(argc, const_cast<char**>(argv));
    
    EXPECT_TRUE(options.UseJIT());
    EXPECT_EQ(options.GetInputFile(), "test.mc");
}

// Test ASM output
TEST(CompilerOptionsTest, ASMOutput) {
    const char* argv[] = {"./miniC", "--emit-asm", "--input", "test.mc", "--output", "test.s"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    
    CompilerOptions options;
    options.ParseCommandLine(argc, const_cast<char**>(argv));
    
    EXPECT_TRUE(options.ShouldEmitASM());
    EXPECT_FALSE(options.ShouldEmitLLVM());
    EXPECT_EQ(options.GetOutputFile(), "test.s");
}

// Test optimization levels
TEST(CompilerOptionsTest, OptimizationLevels) {
    struct TestCase {
        const char* opt_level;
        int expected;
    };

    TestCase test_cases[] = {
        {"0", 0},
        {"1", 1},
        {"2", 2},
        {"3", 3}
    };

    for (const auto& test : test_cases) {
        const char* argv[] = {"./miniC", "--opt-level", test.opt_level, "--input", "test.mc"};
        int argc = sizeof(argv) / sizeof(argv[0]);
        
        CompilerOptions options;
        options.ParseCommandLine(argc, const_cast<char**>(argv));
        
        EXPECT_EQ(options.GetOptimizationLevel(), test.expected)
            << "Failed for optimization level " << test.opt_level;
    }
}

// Test multiple flags together
TEST(CompilerOptionsTest, MultipleFlagsCombination) {
    const char* argv[] = {
        "./miniC",
        "--verbose",
        "--emit-llvm",
        "--opt-level", "2",
        "--input", "source.mc",
        "--output", "out.ll"
    };
    int argc = sizeof(argv) / sizeof(argv[0]);
    
    CompilerOptions options;
    options.ParseCommandLine(argc, const_cast<char**>(argv));
    
    EXPECT_TRUE(options.IsVerbose());
    EXPECT_TRUE(options.ShouldEmitLLVM());
    EXPECT_FALSE(options.ShouldEmitASM());
    EXPECT_FALSE(options.UseJIT());
    EXPECT_EQ(options.GetOptimizationLevel(), 2);
    EXPECT_EQ(options.GetInputFile(), "source.mc");
    EXPECT_EQ(options.GetOutputFile(), "out.ll");
}