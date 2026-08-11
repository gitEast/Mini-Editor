/**
 * @file main.cpp
 * @author Alligator
 * @brief Qt 应用入口：只负责创建 QApplication 和启动窗口
 * @version 0.1
 * @date 2026-08-11
 * @copyright Copyright (c) 2026
 */
#include <QApplication>

#include "ui/MainWindow.h"

int main(int argc, char* argv[]) {
  QApplication application{argc, argv};

  MiniEditor::ui::MainWindow window;
  window.show();

  return application.exec();
}
