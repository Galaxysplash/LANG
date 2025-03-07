# pragma once

#include <string>
#include <unordered_map>
#include <functional>

#include "framework/classes/instruction.h"

struct jiter {
    static void run(
      int argc,
      const char** argv,
      instruction& code_ref
    );

    ///Runs the code.
    static void analyze_and_exec(
        bool in_terminal,
        const instruction& instruction_in,
        const std::unordered_map<std::string, std::function<void()>>& one_word_commands_in
    );

    ///Pulls the code from the file and formats it.
    static void get_code(
        int argc, const char **argv, instruction &ret
    );
};