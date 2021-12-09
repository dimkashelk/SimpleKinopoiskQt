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
    ~CinemaCard();

private:
    Ui::CinemaCard *ui;
};

#endif // CINEMACARD_H
