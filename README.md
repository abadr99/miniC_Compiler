# **MiniC Compiler To-Do List**
---

# 🧩 **MiniC Compiler — Milestone Roadmap (Todo List)**

---

## 🧱 **Milestone 0 — Setup**

**🎯 Goal:** Environment ready, project builds cleanly

**✅ Tasks:**

* [ ] Install **LLVM** (`sudo apt install llvm-dev clang libclang-dev`)
* [ ] Install **ANTLR4** (`wget https://www.antlr.org/download/antlr-4.13.1-complete.jar`)
* [ ] Set aliases:

  ```bash
  alias antlr4='java -jar antlr-4.13.1-complete.jar'
  alias grun='java org.antlr.v4.gui.TestRig'
  ```
* [ ] Create project folders:

  ```
  minic/
   ├── src/
   ├── grammar/
   ├── build/
   ├── examples/
   └── CMakeLists.txt
  ```
* [ ] Add a simple `main.cpp` that prints “MiniC initialized!”
* [ ] CMake + LLVM linkage confirmed

🟢 **Checkpoint:** Run `./minic` → prints *MiniC initialized!*

---

## 📜 **Milestone 1 — ANTLR Grammar**

**🎯 Goal:** Parse MiniC source files into syntax trees

**✅ Tasks:**

* [ ] Create `grammar/MiniC.g4`
* [ ] Define rules for:

  * Functions (`int main() { ... }`)
  * Statements (`let`, `if`, `while`, `return`)
  * Expressions (`+ - * /`, identifiers, literals)
  * Print statement
* [ ] Generate C++ parser:

  ```bash
  antlr4 -Dlanguage=Cpp MiniC.g4 -o generated
  ```
* [ ] Write a small test file `test.mc`
* [ ] Use ANTLR runtime to print parse tree

🟢 **Checkpoint:** Running `./minic test.mc` prints tree successfully.

---

## 🌳 **Milestone 2 — AST Construction**

**🎯 Goal:** Convert ANTLR parse tree → your own AST

**✅ Tasks:**

* [ ] Define AST node classes:

  * `Expr`, `BinaryExpr`, `IntExpr`, `VarExpr`
  * `Stmt`, `PrintStmt`, `VarDecl`, `AssignStmt`
* [ ] Implement a `MiniCVisitor` subclass to construct AST
* [ ] Add debug print of AST

🟢 **Checkpoint:** Input prints an AST tree with correct structure.

---

## 🧮 **Milestone 3 — SSA IR**

**🎯 Goal:** Generate your custom SSA IR from AST

**✅ Tasks:**

* [ ] Define IR structures:

  * `Value`, `Instruction`, `BasicBlock`, `FunctionIR`
* [ ] Add enum `Opcode { Add, Sub, Mul, Div, Const, Load, Store, Print, Ret }`
* [ ] Write AST → SSA builder class:

  * Generate `%1`, `%2` variable names
  * Create basic blocks
  * Each expression returns a `Value*`
* [ ] Implement `--dump-ssa` CLI flag

🟢 **Checkpoint:** Running `--dump-ssa` prints:

```
%1 = const 5
%2 = const 2
%3 = mul %1, %2
print %3
```

---

## ⚙️ **Milestone 4 — LLVM IR Generation**

**🎯 Goal:** Lower SSA to LLVM IR

**✅ Tasks:**

* [ ] Initialize LLVM: `InitializeNativeTarget()`, etc.
* [ ] Create `llvm::Module` and `llvm::IRBuilder`
* [ ] Map SSA opcodes → LLVM IR instructions
* [ ] Add `print` as an external function in LLVM
* [ ] Add `--dump-llvm` flag

🟢 **Checkpoint:** `--dump-llvm` prints valid IR like:

```llvm
define i32 @main() {
entry:
  %1 = mul i32 5, 2
  %2 = add i32 %1, 3
  call void @print(i32 %2)
  ret i32 0
}
```

---

## ⚡ **Milestone 5 — JIT Execution**

**🎯 Goal:** Run MiniC code directly

**✅ Tasks:**

* [ ] Integrate LLVM **ORC JIT**
* [ ] Compile and execute `main()` function at runtime
* [ ] Connect to your host `print` function
* [ ] Run example program and print output

🟢 **Checkpoint:**
Input:

```c
int main() {
  int x = 5;
  int y = x * 2 + 3;
  print(y);
  return 0;
}
```

Output:

```
13
```

---

## 🧠 **Milestone 6 — Optimizations**

**🎯 Goal:** Add real compiler smarts

**✅ Tasks:**

* [ ] Implement **constant folding**
* [ ] Implement **dead code elimination**
* [ ] (Optional) integrate LLVM passes via `FunctionPassManager`
* [ ] Add optimization flags:

  ```
  --opt-level=0 (none)
  --opt-level=1 (basic)
  --opt-level=2 (full)
  ```

🟢 **Checkpoint:** SSA/LLVM IR show reduced instructions.

---

## 💻 **Milestone 7 — REPL & Extras**

**🎯 Goal:** Make it user-friendly and impressive

**✅ Tasks:**

* [ ] Implement REPL mode (`minic --repl`)
* [ ] Add `examples/` folder with demo programs
* [ ] Add SSA visualization (Graphviz)
* [ ] Add documentation (`docs/architecture.md`)
* [ ] Add GitHub Actions CI
* [ ] Polish README with screenshots and IR examples

🟢 **Checkpoint:** Your repo looks professional and runnable by anyone.

---

# 🌟 **Final Deliverables**

✅ `MiniC` executable
✅ ANTLR grammar + SSA + LLVM IR pipeline
✅ JIT execution
✅ Optimizations
✅ Docs + examples
✅ Ready-to-show GitHub portfolio project

---
## TODOS
-[ ] Allow compiling with `clang`