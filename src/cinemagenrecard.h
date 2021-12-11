#ifndef CINEMAGENRECARD_H
#define CINEMAGENRECARD_H

#include <QFrame>
#include <QSqlDatabase>

namespace Ui {
class CinemaGenreCard;
}

class CinemaGenreCard : public QFrame
{
    Q_OBJECT

public:

    explicit CinemaGenreCard(QWidget *parent = nullptr);

    CinemaGenreCard(QSqlDatabase db, QWidget *parent = nullptr, QString id_genre = "1", QString name_genre = "Фэнтези");

    ~CinemaGenreCard();

private:
    Ui::CinemaGenreCard *ui;

    QSqlDatabase db;
};

#endif // CINEMAGENRECARD_H
