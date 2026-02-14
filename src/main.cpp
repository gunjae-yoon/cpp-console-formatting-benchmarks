#include <algorithm>
#include <chrono>
#include <cstdint>
#include <format>
#include <functional>
#include <iostream>
#include <sstream>

struct TestInfo {
  std::string name;
  std::function<void(uint64_t&)> func;
  std::chrono::nanoseconds duration;
};

void PureStringGeneration(uint64_t& count) { std::string text = "alpha" + std::to_string(count) + "\n"; }

void FormatGeneration(uint64_t& count) { std::string text = std::format("alpha{}\n", count); }

void SprintfStringGeneration(uint64_t& count) {
  char buffer[32];
  std::sprintf(buffer, "alpha%lu\n", count);
  std::string text(buffer);
}

void IntegratedStringStreamGeneration(uint64_t& count) {
  std::stringstream ss;
  ss << "alpha" << count << std::endl;
  std::string text = ss.str();
}

void AppendingStringStreamGeneration(uint64_t& count) {
  std::stringstream ss;
  ss << "alpha";
  ss << count;
  ss << std::endl;
  std::string text = ss.str();
}

void StringGenerationBenchmark() {
  const uint64_t limit = 1000000;
  std::array<TestInfo, 5> test_infos = {{{"Pure String Generation", PureStringGeneration},
                                         {"Format Generation", FormatGeneration},
                                         {"sprintf String Generation", SprintfStringGeneration},
                                         {"Integrated String Stream Generation", IntegratedStringStreamGeneration},
                                         {"Appending String Stream Generation", AppendingStringStreamGeneration}}};
  for (TestInfo& test_info : test_infos) {
    std::chrono::system_clock::time_point time_start = std::chrono::system_clock::now();
    for (uint64_t i = 0; i < limit; ++i) {
      test_info.func(i);
    }
    std::chrono::system_clock::time_point time_end = std::chrono::system_clock::now();
    test_info.duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start);
  }

  // Sort by duration (fastest first)
  std::sort(test_infos.begin(), test_infos.end(), [](const TestInfo& a, const TestInfo& b) { return a.duration < b.duration; });

  std::cout << "\nPerformance Results (fastest to slowest):\n";
  std::cout << "==========================================\n";
  for (size_t i = 0; i < test_infos.size(); ++i) {
    std::cout << (i + 1) << ". " << test_infos[i].name << ": " << test_infos[i].duration.count() << " ns" << std::endl;
  }
}

int main() {
  StringGenerationBenchmark();
  return 0;
}