#ifndef CLICKABLEQTEXTEDIT_H
#define CLICKABLEQTEXTEDIT_H

#include <QAbstractItemModel>
#include <QTextEdit>

class ClickableQTextEdit : public QTextEdit
{
    Q_OBJECT

public:

    explicit ClickableQTextEdit(QString text="", QWidget *parent=nullptr);

    ~ClickableQTextEdit();

protected:

    void mousePressEvent(QMouseEvent* event);

signals:

    void clicked();

private:
};

#endif // CLICKABLEQTEXTEDIT_H
