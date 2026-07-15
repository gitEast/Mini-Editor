# 🏷️ Topic: C++ 智能指针 (Smart Pointers)

## 🫯 为什么会有这个东西（Pain Point）

C++ 将资源管理的责任交给程序员。
对于堆内存，需要手动申请和释放：

```c++
int* p = new int(2); // 申请内存
// ...
delete p; // 释放内存。
```

裸指针（raw pointer）本身并不负责资源生命周期。
程序员必须自行管理：

- 谁拥有（Ownership）这块资源
- 谁负责释放（Release）
- 什么时候释放（Lifetime）

如果管理不当，就会导致：

- Memory Leak
- Double Delete
- Exception Safety
- 生命周期难以推导

因而需要一种机制，将资源的生命周期自动化管理，而不是依赖程序员的手动操作。

## 💡 核心思想（Design Philosophy）

> RAII: Resource Acquisition Is Initialization.

核心理念：**把资源交给对象管理。**

- `constructor`: 申请资源
- `destructor`: 释放资源

因此，不论是 `return`、`throw` 还是 `exception`，对象离开作用域时，都能够自动释放资源。

## 🛠 实现原理（Under the Hood）

```c++
template <typename T>
class MyUniquePtr {
 public:
  explicit MyUniquePtr(T* p) : ptr_(p) {}  // 防止 = new int(10) 隐式转换
  ~MyUniquePtr() { delete ptr_; }

 private:
  T* ptr_;
};
```

## 🌟 实际情况（How to Use）

### 2.1 `std::unique_ptr`

- 特点：
  1. ownership 唯一
  2. 仅可通过 `auto p2 = std::move(p1);` 实现值转移
     - `std::move` 将左值 as 右值 使用
     - `MyUniquePtr(MyUniquePtr&&)` 转移函数
  3. 不允许隐式转换
  4. 不允许 copy

```c++
/** 基础实现 */
template <typename T>
class MyUniquePtr {
 public:
  explicit MyUniquePtr(T* p) : ptr_(p) {}  // 防止 = new int(10) 隐式转换
  ~MyUniquePtr() { delete ptr_; }

  /* ------------ ⬇ 支持指针写法 ⬇ ------------ */
  T& operator*() { return *ptr_; }
  T* operator->() { return ptr_; }
  /* ------------ ⬆ 支持指针写法 ⬆ ------------ */

  /* ------------ ⬇ 独占所有权，禁止复制 ⬇ ------------ */
  MyUniquePtr(const MyUniquePtr&) = delete;
  MyUniquePtr& operator=(const MyUniquePtr&) = delete;
  /* ------------ ⬆ 独占所有权，禁止复制 ⬆ ------------ */

  /* ------------ ⬇ 移动构造函数 ⬇ ------------ */
  MyUniquePtr(MyUniquePtr&& other) {  // T&& 右值引用
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }
  /* ------------ ⬆ 移动构造函数 ⬆ ------------ */

 private:
  T* ptr_;
};
```

### 2.2 `std::shared_ptr`

- 特点
  - ownership: 允许共享
  - 内部维护引用计数（Reference Count）
  - 比 `std::unique_ptr` 多一个控制块（Control Block）
    - `ref_count`
    - `weak_count`

## ⚠️ 工程避坑（Pitfalls）

- 目前已知
  - 默认优先使用 `std::unique_ptr`
  - 只有确实存在共享所有权时，才使用 `std::shared_ptr`
- 未来补充（TODO）
  - make_unique
  - make_shared
  - weak_ptr
  - 循环引用
  - Control Block

## 🚀 项目中的应用（Project Practice）

等待未来补充

## 🎯 总结（Takeaway）

智能指针不是新的指针，而是能够管理资源生命周期的对象。

|              | `std::unique_ptr` | `std::shared_ptr`     |
| ------------ | ----------------- | --------------------- |
| ownership    | unique            | shared                |
| 系统开销     | 近似于裸指针      | 裸指针 + 引用计数机制 |
| 是否允许复制 | ❌                | ✅                    |
| 是否允许移动 | ✅                | ✅                    |
| 使用场景     | 优先使用          | 必须要共享所有权      |
