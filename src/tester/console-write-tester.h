#ifndef __console_write_tester_h__
#define __console_write_tester_h__

#include "tester.h"

namespace gunjae {
class ConsoleWriteTester : public Tester {
 public:
  ConsoleWriteTester(const std::string& filename);

  void FputsWrite(uint64_t& count);
  void FprintfWrite(uint64_t& count);
  void CoutWrite(uint64_t& count);
  void PrintfWrite(uint64_t& count);
  void WriteSystemCall(uint64_t& count);

 private:
  void Run() override;

 private:
  std::string text_ = "this is the plain text for console write test\n";
};
}  // namespace gunjae

#endif  // __console_write_tester_h__