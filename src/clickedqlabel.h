#ifndef CLICKEDQLABEL_H
#define CLICKEDQLABEL_H

#include <QLabel>

class ClickableQLabel : public QLabel
{
    Q_OBJECT

public:

    explicit ClickableQLabel(QString text="", QWidget* parent=nullptr);

    ~ClickableQLabel();

private:

protected:

    void mousePressEvent(QMouseEvent* event);

signals:

    void clicked();

};

#endif // CLICKEDQLABEL_H
