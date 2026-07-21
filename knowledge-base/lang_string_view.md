# 🏷️ Topic: std::string_view（C++现代语法）

## 🫯 为什么会有这个东西（Pain Point）

- 字符串历史进程
  1. `char` -> `char*`: 从单个字符到字符串
  2. `char*` -> `std::string`
     - Pain Point
       1. 生命周期和内存管理需要程序员手动负责；
       2. 没有记录长度，以 `'\0'` 为结束标识：需要从第一个字符串遍历；
       3. 需要程序员保证缓冲区大小，否则可能内存越界。
     - 解决：封装成对象
       - `char* data`
       - `std::size_t size`
       - `std::size_t capacity`
       - 利用对象析构自动释放资源（RAII）
       - 封装了其他一些好用的方法...
     - Ps: 这是从 C 到 C++ 了。

```c++
/** char* 与 std::string 的使用痛点案例：获取字符串长度 */
int getStrLen(char* str) {
  return strlen(str); // 需要从 str 的位置开始扫描字符，直至找到 '\0'
}
// 目的：不拷贝只传递引用，需要用 const 和 &
// 入参如果是字面量，则编译器解析为 const char[12]，运行时，先构造一个 std::string 类型对象，然后给函数的形参绑定引用
int getStrLen(const std::string& str) {
  return str.length();
}
```

痛点：

1. 当函数形参为 `std::string` 类型，而实参为字符串字面量或 `char*` 时，编译器通常需要构造一个临时的 `std::string`，产生一次额外的内存分配与字符复制。
2. 对字符串类型的参数，需要分别支持 `char*` 和 `std::string`。
3. 对于只读情况而言，没有必要对原有字符串进行复制，直接操作即可。

## 💡 核心思想（Design Philosophy）

- 目的：减少只读情况下，字符串使用的开销。
- 核心
  - 非拥有 Non-owning
  - 只读 Read-only
  - 零拷贝 Zero-copy
- 字符串的抽象视图，而不是一整个字符串

## 🛠 实现原理（Under the Hood）

- 封装一个对象，用于对原有字符串的只读操作
  - `const char* data`: 指向原字符串数据（不可通过 `std::string_view` 修改字符）
  - `std::size_t len`: 字符串长度

## 🧩 常用 API（How to Use）

```c++
#include <string>
#include <string_view>

std::string s = "Hello World";
std::string_view sv{s}; // 或者 std::string_view sv = s;
auto sub = sv.substr(6, 5); // "World"
sv.starts_with("Hello"); // true
sv.ends_with("World"); // true
sv.contains("ll"); // true
```

## ⚠️ 工程避坑（Pitfalls）

```c++
#include <string>
#include <string_view>

/** 注意：std::string_view 的生命周期，不能长于原字符串 */
std::string_view getTempName() {
  std::string localStr = "Very Long Temporary String";
  return localStr; // 💥 localStr 是局部变量，函数结束就销毁了。
}
int main() {
  std::string_view view = getTempName(); // view 指向一块已经被销毁的、不存在的内存
  std::cout << view << std::endl; // 触发未定义行为，程序崩溃或输出乱码
}
```

- `std::string_vie` 并不拥有字符串，只是借用原来的字符序列。

## 🚀 项目中的应用（Project Practice）

## 🎯 总结（Takeaway）

从 `char*` 到 `std::string`，C++ 解决了字符串的安全管理问题；从 `std::string` 到 `std::string_view`，C++ 又解决了只读场景下不必要的内存分配与复制问题。
