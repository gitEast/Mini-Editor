# 🏷️ Topic: 面向对象与多态（Virtual & Override）

## 🫯 为什么会有这个东西（Pain Point）

```c++
// parent
class Shape {
 public:
  std::string getArea() { return "area of shape"; }
}

// child
class Circle: public Shape {
 public:
  std::string getArea() { return "area of circle"; }
}

int main() {
  Shape circle = Circle();
  circle.getArea(); // "area of shape"
}
```

- 出现的问题：`circle` 作为 `Circle` 类对象，调用 `getArea` 后，实际输出的却是 `Shape` 的 `getArea()` 方法
- 原因解析：静态绑定 **Static Binding**
  - 对于普通成员函数，在编译阶段就确定调用对应函数。
- 所以需要一个机制，在运行阶段再绑定对应的函数。

## 💡 核心思想（Design Philosophy）

动态绑定(Dynamic Dispatch) / 运行时多态(Runtime Polymorphism)

- `virtual` 语法规定，在运行时，根据对象的真实类型，决定调用的函数。
  - `override`: 起一个严格对应的作用（防止粗心写错）

## 🛠 实现原理（Under the Hood）

- `virtual` 使得类中多了一个指针 `virtual ptr`，指向 `virtual table`
- `virtual table` 中存放的是类中所有 virtual function 的真实地址。
  - child 类 override 时，会把表中对应的函数地址替换成自己的实现。

## 🧩 常用 API（How to Use）

```c++
// parent
class Shape {
 public:
  virtual std::string getArea() { return "area of shape." }
  virtual ~Shape() = default; // 当存在 virtual 函数时，destructor 必须声明为 `virtual`
}
// child
class Circle: public Shape {
 public:
  std::string getArea() override { return "area of circle." }
}

int main() {
  Shape circle = Circle();
  circle.getArea(); // "area of circle."
}


//  ，
```

- 纯虚函数 `virtual std::string getArea() = 0;`
  1. 无法再 `new Shape()`
  2. 强制 child 类重写虚函数

## ⚠️ 工程避坑（Pitfalls）

## 🚀 项目中的应用（Project Practice）

## 🎯 总结（Takeaway）

多态的实现。
