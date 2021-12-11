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

    this->db = db;

    QSqlQuery get_id("SELECT id FROM genres WHERE genre = " + genre, db);
    get_id.next();

    this->ui->label->setText(genre);

    QSqlQuery cinema_query;
    cinema_query.prepare("SELECT image FROM cinema WHERE genre = (:genreId)");
    cinema_query.bindValue(":genreId", get_id.value(0).toString());
    cinema_query.exec();

//    QList<QByteArray> cinemas;
//    if (cinema_query.isActive()) {
//        while (cinema_query.next()) {
//            cinemas.append(cinema_query.value(0).toByteArray());
//        }
//    }

//    QSet<QByteArray> five_cinema;
//    while (five_cinema.size() < 5) {
//        five_cinema.insert(cinemas[rand() % cinemas.size()]);
//    }

//    ClickableQLabel *label = new ClickableQLabel(name_genre, this);
//    this->ui->qMain->addWidget(label);

//    QScrollArea *scrollArea = new QScrollArea(this);
//    QWidget *scrollAreaWidget = new QWidget(this);
//    QHBoxLayout *cinema = new QHBoxLayout(this);

//    for (auto i: five_cinema) {
//        QImage dop;
//        dop.loadFromData(i);
//        CinemaCard *card = new CinemaCard(this);

//    }

//    scrollAreaWidget->setLayout(cinema);
//    scrollArea->addScrollBarWidget(scrollAreaWidget, Qt::AlignCenter);
}
