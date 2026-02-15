#include "string-tester.h"

#include <sstream>

namespace gunjae {
StringTester::StringTester(const std::string& filename) : Tester(filename) {
  test_infos_ = {{"std::string", StringTester::PureStringGeneration},
                 {"std::format", StringTester::FormatGeneration},
                 {"sprintf", StringTester::SprintfStringGeneration},
                 {"std::stringstream(integrated)", StringTester::IntegratedStringStreamGeneration},
                 {"std::stringstream(appended)", StringTester::AppendingStringStreamGeneration}};
}

void StringTester::PureStringGeneration(uint64_t& count) { std::string text = "alpha" + std::to_string(count) + "\n"; }

void StringTester::FormatGeneration(uint64_t& count) { std::string text = std::format("alpha{}\n", count); }

void StringTester::SprintfStringGeneration(uint64_t& count) {
  char buffer[32];
  std::sprintf(buffer, "alpha%lu\n", count);
  std::string text(buffer);
}

void StringTester::IntegratedStringStreamGeneration(uint64_t& count) {
  std::stringstream ss;
  ss << "alpha" << count << std::endl;
  std::string text = ss.str();
}

void StringTester::AppendingStringStreamGeneration(uint64_t& count) {
  std::stringstream ss;
  ss << "alpha";
  ss << count;
  ss << std::endl;
  std::string text = ss.str();
}

void StringTester::Run() {
  const uint64_t limit = 1000000;
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