#ifndef CINEMACARD_H
#define CINEMACARD_H

#include <QFrame>

namespace Ui {
class CinemaCard;
}

class CinemaCard : public QFrame
{
    Q_OBJECT

public:
    explicit CinemaCard(QWidget *parent = nullptr);

    CinemaCard(QImage image, QString title, QWidget *parent = nullptr);

    ~CinemaCard();

    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *mouseEvent);

    QString get_id_film();

signals:

    void clicked();

private:
    Ui::CinemaCard *ui;

    QPixmap background;

    QString id_film;
};

#endif // CINEMACARD_H
