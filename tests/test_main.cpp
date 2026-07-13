#include <cassert>
#include <iostream>
#include <string>

// 模拟一个简单的解析函数：传入"# Hello"，返回 "<h1>Hello</h1>"
std::string simulate_parse_heading(const std::string& line) {
  if (line.rfind("# ", 0) == 0) {
    return "<h1>" + line.substr(2) + "</h1>";
  }
  return line;
}

int main() {
  std::cout << "Running MiniEditor Tests...\n";
  // 测试用例 1：验证最基础的标题解析逻辑
  std::string input = "# Hello";
  std::string expected = "<h1>Hello</h1>";

  // assert 如果断言失败，程序直接崩溃并报错
  assert(simulate_parse_heading(input) == expected);

  std::cout << "All tests passed successfully! 🎉\n";

  return 0;
}
