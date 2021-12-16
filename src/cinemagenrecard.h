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

    CinemaGenreCard(QSqlDatabase db, QWidget *parent = nullptr, QString id_genre = "1");

    ~CinemaGenreCard();

signals:

    void clicked();

private:
    Ui::CinemaGenreCard *ui;

    QSqlDatabase db;

    QString id_genre = "-1";
    QString id_film = "-1";

    void clicked_on_label();

    void clicked_on_card();
};

#endif // CINEMAGENRECARD_H
