#include "cinemagenrecard.h"
#include "ui_cinemagenrecard.h"
#include "clickedqlabel.h"
#include "cinemacard.h"
#include <QSqlQuery>
#include <QSqlError>

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


CinemaGenreCard::CinemaGenreCard(QSqlDatabase db, QWidget *parent, QString genre) :
    QFrame(parent),
    ui(new Ui::CinemaGenreCard)
{
    ui->setupUi(this);

    this->setMinimumHeight(400);

    this->db = db;

    QSqlQuery get_id("SELECT id FROM genres WHERE genre = \"" + genre + "\"", db);
    get_id.next();
    this->ui->label->setText(genre);

    QSqlQuery cinema_id_query("SELECT film FROM genre_film WHERE genre = " + get_id.value(0).toString(), db);
    cinema_id_query.next();

    QList<QString> all_cinema;
    if (cinema_id_query.isActive()) {
        while (cinema_id_query.next()) {
            all_cinema.append(cinema_id_query.value(0).toString());
        }
    }

    QSet<QString> films;
    while (films.size() < 5) {
        films.insert(all_cinema[rand() % all_cinema.size()]);
    }

    for (int i = 0; i < 5; i++) {
        QSqlQuery get_film("SELECT title, image FROM films WHERE id = " + *films.begin(), db);
        get_film.next();
        if (get_film.isActive()) {
            CinemaCard *new_card = new CinemaCard(this);
            this->ui->layout->addWidget(new_card);
        }
    }

    QLabel *label = new QLabel("TESTING");
    label->setMaximumHeight(150);

    this->ui->layout->addWidget(label);

//    for (auto i: films) {
//        QSqlQuery get_film("SELECT title, image FROM films WHERE id = " + i, db);
//        get_film.next();
//        if (get_film.isActive()) {
//            CinemaCard *new_card = new CinemaCard(QImage::fromData(get_film.value(1).toByteArray()), get_film.value(0).toString(), this);
//            this->ui->layout->addWidget(new_card);
//        }
//    }
}
