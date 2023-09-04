#include <unistd.h>

#include <iostream>
#include <memory>

#include "tscpp/base/core.h"
#include "tscpp/parser/parser.h"
#include "tscpp/typechecker/compiler.h"
#include "tscpp/typechecker/debug.h"
#include "tscpp/typechecker/module.h"
#include "tscpp/typechecker/vm.h"
#include "tscpp/utils/fs.h"

using namespace tscpp;

void run(const string& bytecode, const string& code, const string& fileName) {
  ZoneScoped;
  auto module = std::make_shared<vm::Module>(bytecode, fileName, code);
  bench(1, [&] {
    vm::run(module);
    module->printErrors();
  });
}

void compileAndRun(const string& code, const string& file,
                   const string& fileName) {
  ZoneScoped;
  auto bytecodePath = file + ".tsb";
  auto buffer = fileRead(file);
  checker::Compiler compiler;
  Parser parser;
  auto result = parser.parseSourceFile(
      file, buffer, types::ScriptTarget::Latest, false, ScriptKind::TS, {});
  auto program = compiler.compileSourceFile(result);
  auto bin = program.build();
  fileWrite(bytecodePath, bin);
  std::filesystem::last_write_time(bytecodePath,
                                   std::filesystem::last_write_time(file));
  checker::printBin(bin);
  auto module = make_shared<vm::Module>(bin, fileName, code);
  vm::run(module);
  module->printErrors();
}

int main(int argc, char* argv[]) {
  ZoneScoped;
  std::string file;
  auto cwd = std::filesystem::current_path();

  if (argc > 1) {
    file = cwd.string() + "/" + argv[1];
  } else {
    file = cwd.string() + "/../tests/basic.ts";
  }

  if (!fileExists(file)) {
    std::cout << "File not found " << file << "\n";
    return 4;
  }
  auto code = fileRead(file);
  auto bytecode = file + ".tsb";
  auto relative = std::filesystem::relative(file, cwd);

  if (fileExists(bytecode) && std::filesystem::last_write_time(bytecode) ==
                                  std::filesystem::last_write_time(file)) {
    run(fileRead(bytecode), code, relative.string());
  } else {
    compileAndRun(code, file, relative.string());
  }
  return 0;
}
