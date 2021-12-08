#include "clickableqtextedit.h"

ClickableQTextEdit::ClickableQTextEdit(QString text, QWidget *parent): QTextEdit(parent) {
    setText(text);
}

ClickableQTextEdit::~ClickableQTextEdit() { }

void ClickableQTextEdit::mousePressEvent(QMouseEvent* event) {
   emit clicked();
}
