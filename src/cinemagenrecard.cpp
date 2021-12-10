#include "cinemagenrecard.h"
#include "ui_cinemagenrecard.h"
#include <QSqlQuery>

CinemaGenreCard::CinemaGenreCard(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CinemaGenreCard)
{
    ui->setupUi(this);
}

CinemaGenreCard::~CinemaGenreCard()
{
    delete ui;
}


CinemaGenreCard::CinemaGenreCard(QWidget *parent, QString id_genre) :
    QFrame(parent),
    ui(new Ui::CinemaGenreCard)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE", "db");
    db.setDatabaseName("db.db");
    db.open();

    QSqlQuery cinema_query;
    cinema_query.prepare("SELECT image FROM cinema WHERE genre = (:genreId)");
    cinema_query.bindValue(":genreId", id_genre);
    cinema_query.exec();

    QList<QString> cinemas;
    if (cinema_query.isActive()) {
        while (cinema_query.next()) {
            cinemas.append(cinema_query.value(0).toString());
        }
    }

    QSet<QString> five_cinema;
    while (five_cinema.size() < 5) {
        five_cinema.insert(cinemas[rand() % cinemas.size()]);
    }


}
