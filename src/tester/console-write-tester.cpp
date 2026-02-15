#include "console-write-tester.h"

#include <unistd.h>

#include <cstring>
#include <iostream>

namespace gunjae {
ConsoleWriteTester::ConsoleWriteTester(const std::string& filename) : Tester(filename) {
  test_infos_ = {{"std::cout", std::bind(&ConsoleWriteTester::CoutWrite, this, std::placeholders::_1)},
                 {"std::printf", std::bind(&ConsoleWriteTester::PrintfWrite, this, std::placeholders::_1)},
                 {"std::fprintf", std::bind(&ConsoleWriteTester::FprintfWrite, this, std::placeholders::_1)},
                 {"std::fputs", std::bind(&ConsoleWriteTester::FputsWrite, this, std::placeholders::_1)},
                 {"write()", std::bind(&ConsoleWriteTester::WriteSystemCall, this, std::placeholders::_1)}};
}

void ConsoleWriteTester::CoutWrite(uint64_t& count) { std::cout << text_; }

void ConsoleWriteTester::PrintfWrite(uint64_t& count) { std::printf("%s", text_.c_str()); }

void ConsoleWriteTester::FprintfWrite(uint64_t& count) { std::fprintf(stdout, "%s", text_.c_str()); }

void ConsoleWriteTester::FputsWrite(uint64_t& count) { std::fputs(text_.c_str(), stdout); }

void ConsoleWriteTester::WriteSystemCall(uint64_t& count) { write(STDOUT_FILENO, text_.c_str(), text_.length()); }

void ConsoleWriteTester::Run() {
  const uint64_t limit = 10000;
  for (TestInfo& test_info : test_infos_) {
    std::chrono::system_clock::time_point time_start = std::chrono::system_clock::now();
    for (uint64_t i = 0; i < limit; ++i) {
      test_info.func(i);
    }
    std::chrono::system_clock::time_point time_end = std::chrono::system_clock::now();
    test_info.duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start);
  }
}
}  // namespace gunjae
