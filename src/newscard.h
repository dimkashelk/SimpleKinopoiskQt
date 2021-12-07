#ifndef NEWSCARD_H
#define NEWSCARD_H

#include <QFrame>

namespace Ui {
class NewsCard;
}

class NewsCard : public QFrame
{
    Q_OBJECT

public:
    explicit NewsCard(QWidget *parent = nullptr);

    NewsCard(QWidget *parent, QString title, QString text, QImage image);

    ~NewsCard();

signals:

    void clicked();

protected:

    void mousePressEvent(QMouseEvent* event);

private:
    Ui::NewsCard *ui;

    QImage original_image;

    void send_signal_clicked();
};

#endif // NEWSCARD_H
