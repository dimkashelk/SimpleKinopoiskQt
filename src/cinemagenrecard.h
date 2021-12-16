#ifndef CINEMAGENRECARD_H
#define CINEMAGENRECARD_H

#include "cinemacard.h"
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

    QString get_id_genre();

    QString get_id_film();

protected:

    void mousePressEvent(QMouseEvent *mouse);

signals:

    void clicked();

    void clicked_on_film();

private:
    Ui::CinemaGenreCard *ui;

    QSqlDatabase db;

    QString id_genre = "-1";
    QString id_film = "-1";
    CinemaCard *last_film;

    void clicked_on_label();

    void clicked_on_card();
};

#endif // CINEMAGENRECARD_H
