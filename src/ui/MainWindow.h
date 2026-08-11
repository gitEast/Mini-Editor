/**
 * @file MainWindow.h
 * @author Alligator
 * @brief 界面结构及交互
 * @version 0.1
 * @date 2026-08-11
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <QMainWindow>

class QPlainTextEdit;
class QTextBrowser;
class QTimer;

namespace MiniEditor::ui {
class MainWindow final : public QMainWindow {
 public:
  explicit MainWindow(QWidget* parent = nullptr);

 private:
  void renderPreview();

  QPlainTextEdit* editor_ = nullptr;
  QTextBrowser* preview_ = nullptr;
  QTimer* renderTimer_ = nullptr;
};
}  // namespace MiniEditor::ui
