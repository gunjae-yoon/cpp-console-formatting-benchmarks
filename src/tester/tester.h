#include <chrono>
#include <functional>
#include <list>
#include <string>

namespace gunjae {

struct TestInfo {
  std::string name;
  std::function<void(uint64_t&)> func;
  std::chrono::nanoseconds duration = std::chrono::nanoseconds::zero();
};

class Tester {
 public:
  Tester(const std::string& filename);
  virtual ~Tester() = default;

  void Test();
  void PrintResults() const;

 protected:
  virtual void Run() = 0;
  void PrepareTest();
  void StoreResult();

 protected:
  std::FILE* file_;
  std::string filename_;
  std::list<TestInfo> test_infos_;
};
}  // namespace gunjae