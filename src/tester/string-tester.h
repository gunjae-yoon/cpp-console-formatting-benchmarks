#include "tester.h"

namespace gunjae {
class StringTester : public Tester {
 public:
  StringTester(const std::string& filename);

  static void PureStringGeneration(uint64_t& count);
  static void FormatGeneration(uint64_t& count);
  static void SprintfStringGeneration(uint64_t& count);
  static void IntegratedStringStreamGeneration(uint64_t& count);
  static void AppendingStringStreamGeneration(uint64_t& count);

 private:
  void Run() override;
};
}  // namespace gunjae