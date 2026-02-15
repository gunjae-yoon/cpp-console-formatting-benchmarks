#include "tester/console-write-tester.h"
#include "tester/string-tester.h"

int main() {
  for (size_t i = 0; i < 5; ++i) {
    gunjae::StringTester tester("string_test_results.csv");
    tester.Test();
    tester.PrintResults();

    gunjae::ConsoleWriteTester console_tester("console_write_test_results.csv");
    console_tester.Test();
    console_tester.PrintResults();
  }
  return 0;
}