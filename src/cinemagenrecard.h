#ifndef CINEMAGENRECARD_H
#define CINEMAGENRECARD_H

#include <QFrame>

namespace Ui {
class CinemaGenreCard;
}

class CinemaGenreCard : public QFrame
{
    Q_OBJECT

public:
    explicit CinemaGenreCard(QWidget *parent = nullptr);
    ~CinemaGenreCard();

private:
    Ui::CinemaGenreCard *ui;
};

#endif // CINEMAGENRECARD_H
