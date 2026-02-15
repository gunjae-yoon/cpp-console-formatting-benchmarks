#include "tester.h"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <vector>

namespace gunjae {
Tester::Tester(const std::string& filename) : filename_(filename), file_(nullptr) {}

void Tester::Test() {
  PrepareTest();
  Run();
  StoreResult();
}

void Tester::PrintResults() const {
  // Create a sorted copy of test_infos_
  std::vector<TestInfo> sorted_tests(test_infos_.begin(), test_infos_.end());
  std::sort(sorted_tests.begin(), sorted_tests.end(), [](const TestInfo& a, const TestInfo& b) { return a.duration < b.duration; });

  std::cout << "\nPerformance Results (fastest to slowest):\n";
  std::cout << "==========================================\n";
  for (size_t i = 0; i < sorted_tests.size(); ++i) {
    std::cout << (i + 1) << ". " << sorted_tests[i].name << ": " << sorted_tests[i].duration.count() << " ns" << std::endl;
  }
}

void Tester::PrepareTest() {
  // Check if file exists
  bool file_exists = std::filesystem::exists(filename_);

  if (file_exists) {
    // File exists, open in append mode
    file_ = std::fopen(filename_.c_str(), "a");
  } else {
    // File doesn't exist, create it and write CSV header
    file_ = std::fopen(filename_.c_str(), "w");
    if (file_) {
      // Write header with test names
      bool first = true;
      for (const auto& test_info : test_infos_) {
        if (!first) {
          std::fprintf(file_, ",");
        }
        std::fprintf(file_, "%s", test_info.name.c_str());
        first = false;
      }
      std::fprintf(file_, "\n");
    }
  }

  if (!file_) {
    std::cerr << "Failed to open file: " << filename_ << std::endl;
    return;
  }
}

void Tester::StoreResult() {
  if (file_) {
    // Write test results (durations) as CSV row
    bool first = true;
    for (const TestInfo& test_info : test_infos_) {
      if (!first) {
        std::fprintf(file_, ",");
      }
      std::fprintf(file_, "%ld", test_info.duration.count());
      first = false;
    }
    std::fprintf(file_, "\n");

    std::fclose(file_);
    file_ = nullptr;
  }
}
}  // namespace gunjae