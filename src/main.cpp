#include "tester/string-tester.h"

int main() {
  for (size_t i = 0; i < 5; ++i) {
    gunjae::StringTester tester("string_test_results.csv");
    tester.Test();
    tester.PrintResults();
  }
  return 0;
}