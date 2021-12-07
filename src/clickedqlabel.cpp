#include "clickedqlabel.h"

ClickableQLabel::ClickableQLabel(QString text, QWidget *parent): QLabel(parent) {
    setText(text);
}

ClickableQLabel::~ClickableQLabel() { }

void ClickableQLabel::mousePressEvent(QMouseEvent* event) {
   emit clicked();
}
