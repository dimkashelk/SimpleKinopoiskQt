#ifndef NEWSCARD_H
#define NEWSCARD_H

#include "clickedqlabel.h"
#include "clickableqtextedit.h"
#include <QFrame>

namespace Ui {
class NewsCard;
}

class NewsCard : public QFrame
{
    Q_OBJECT

public:
    explicit NewsCard(QWidget *parent = nullptr);

    NewsCard(QWidget *parent, QString title, QString descpription, QString text, QImage image);

    ~NewsCard();

    QString get_title();

    QString get_text();

    QImage get_image();

signals:

    void clicked();

protected:

    void mousePressEvent(QMouseEvent* event);

private:
    Ui::NewsCard *ui;

    QImage original_image;
    QString text;
    ClickableQLabel *news_image, *news_label;
    ClickableQTextEdit *news_description;

    void send_signal_clicked();
};

#endif // NEWSCARD_H
