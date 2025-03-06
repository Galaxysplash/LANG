# pragma once


#include <initializer_list>
#include <string>
#include <unordered_map>
#include <functional>

#include "framework/code.h"

struct program {
    static void run(
      int argc,
      const char** argv,
      code& code_ref
    );

    ///Runs the code.
    static void analyze_and_exec(
        bool in_terminal,
        const code& code_in,
        const std::unordered_map<std::string_view, std::function<void()>>& one_word_commands_in
    );

    ///Pulls the code from the file and formats it.
    static void get_code(
        int argc, const char **argv, code &ret
    );
};