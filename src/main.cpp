#include "summary/program.h"

#include <chrono>
#include <string>
#include <thread>
#include <vector>

static constexpr std::string_view EXIT_INSTRUCTION = "exit";

int main(const int argc, const char **argv) {
    const bool in_terminal = argc <= 1;
    bool first_time = true;
    std::vector<std::string> code;

    // ReSharper disable once CppDFALoopConditionNotUpdated
     do {
         if (in_terminal) {
             if (first_time) {
                 printf(std::format(
                     "type in code, or '{}' if you want to (pay attention to upper and lower case):\n",
                     EXIT_INSTRUCTION.data()
                ).c_str());

                 first_time = false;
             }

             printf(">>>");
         }

        run(argc, argv, in_terminal, EXIT_INSTRUCTION, code);

        if (in_terminal) {
            code.clear();

            std::this_thread::sleep_for(std::chrono::seconds(1));

            printf("\n");
        }
    } while (in_terminal);
}
