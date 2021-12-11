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
    
    NewsCard(QWidget *parent, QString id, QString title, QString description, QString text, QImage image);
    
    NewsCard(QWidget *parent, QString id, QString title, QString description, QString text, QImage image, QString count_views);

    ~NewsCard();

    QString get_title();

    QString get_text();

    QImage get_image();
    
    QString get_id_news();
    
    void set_count_views(int count);
    
    void increase_count_views();

signals:

    void clicked();

protected:

    void mousePressEvent(QMouseEvent* event);

private:
    Ui::NewsCard *ui;

    QImage *original_image;
    QString text, id_news;
    ClickableQLabel *news_image, *news_label;
    ClickableQTextEdit *news_description;
	
	int count_views;

    void send_signal_clicked();
};

#endif // NEWSCARD_H
