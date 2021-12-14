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

signals:

    void clicked();

protected:

    void mousePressEvent(QMouseEvent *event);

private:

    Ui::CinemaCard *ui;

    void on_image_clicked();
};

#endif // CINEMACARD_H
