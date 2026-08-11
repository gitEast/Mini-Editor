/**
 * @file MainWindow.cpp
 * @author Alligator
 * @brief 实现窗口 & 即时渲染
 * @version 0.1
 * @date 2026-08-11
 * @copyright Copyright (c) 2026
 */

#include "ui/MainWindow.h"

#include <QByteArray>
#include <QFontDatabase>
#include <QPlainTextEdit>
#include <QSplitter>
#include <QString>
#include <QTextBrowser>
#include <QTimer>
#include <exception>
#include <string>

#include "parser/lexer/Lexer.h"
#include "parser/parser/Parser.h"
#include "parser/visitor/HtmlRenderVisitor.h"

namespace MiniEditor::ui {
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  setWindowTitle("MiniEditor");
  resize(1100, 700);

  auto* splitter = new QSplitter{this};  // 最小且可调整的双栏布局

  editor_ = new QPlainTextEdit{splitter};
  preview_ = new QTextBrowser{splitter};
  renderTimer_ = new QTimer{this};

  editor_->setPlaceholderText("在这里输入 Markdown...");
  editor_->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));

  preview_->setOpenExternalLinks(true);

  splitter->addWidget(editor_);
  splitter->addWidget(preview_);
  // 设置两个区域初始宽度相等，并允许窗口扩大时，双方共同获得空间
  splitter->setStretchFactor(0, 1);
  splitter->setStretchFactor(1, 1);
  splitter->setSizes({550, 550});

  setCentralWidget(
      splitter);  // 转移所有权：窗口负责管理 splitter；编辑器和预览器是
                  // splitter 的字对象，跟随 splitter 的销毁而销毁

  // 防抖：单次定时器触发一次后停止；若尚未触发时再次调用
  // start()，重新开始倒计时
  renderTimer_->setSingleShot(true);
  renderTimer_->setInterval(180);

  connect(editor_, &QPlainTextEdit::textChanged, this,
          [this] { renderTimer_->start(); });
  connect(renderTimer_, &QTimer::timeout, this, [this] { renderPreview(); });

  editor_->setPlainText(
      "# MiniEditor\n"
      "\n"
      "在左侧编辑 Markdown，在右侧查看即时预览。\n"
      "\n"
      "## Current pipeline\n"
      "Lexer → Parser → AST → HtmlRenderVisitor");

  renderPreview();
}

void MainWindow::renderPreview() {
  const QByteArray utf8Source =
      editor_->toPlainText().toUtf8();  // QString 使用 Unicode
  const std::string source{utf8Source.constData(),
                           static_cast<std::size_t>(utf8Source.size())};

  try {
    parser::Lexer lexer{source};
    parser::Parser parser{lexer.tokenize()};
    const parser::DocumentNode document = parser.parse();

    parser::HtmlRenderVisitor renderer;
    document.accept(renderer);

    const std::string& html = renderer.result();
    preview_->setHtml(
        QString::fromUtf8(html.data(), static_cast<qsizetype>(html.size())));
  } catch (const std::exception& error) {
    // 解析失败时，只做提示，不退出 GUI
    const QString message = QString::fromUtf8(error.what()).toHtmlEscaped();
    preview_->setHtml(
        "<p style=\"color: #b00020;\"><strong>Render error:</strong> " +
        message + "</p>");
  }
}
}  // namespace MiniEditor::ui
