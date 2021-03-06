#include "cinemagenrecard.h"
#include "ui_cinemagenrecard.h"
#include "clickedqlabel.h"
#include "cinemacard.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QScrollArea>

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

    this->setMinimumHeight(600);

    this->db = db;

    QSqlQuery get_id("SELECT id FROM genres WHERE genre = \"" + genre + "\"", db);
    get_id.next();

    this->id_genre = get_id.value(0).toString();

    ClickableQLabel *label = new ClickableQLabel(genre);
    label->setCursor(Qt::PointingHandCursor);
    this->ui->main->addWidget(label);

    QHBoxLayout *layout = new QHBoxLayout(this);

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

    for (auto i: films) {
        QSqlQuery get_film("SELECT image FROM films WHERE id = " + i, db);
        get_film.next();
        if (get_film.isActive()) {
            CinemaCard *new_card = new CinemaCard(QImage::fromData(get_film.value(0).toByteArray()), i, this);
            layout->addWidget(new_card);
            connect(new_card, &CinemaCard::clicked, this, &CinemaGenreCard::clicked_on_card);
        }
    }

    QWidget *p = new QWidget(this);
    p->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    p->setLayout(layout);

    QScrollArea *scroll_area = new QScrollArea(this);
    scroll_area->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    scroll_area->setMaximumHeight(500);
    scroll_area->setWidget(p);

    this->ui->main->addWidget(scroll_area);

    connect(label, &ClickableQLabel::clicked, this, &CinemaGenreCard::clicked_on_label);
}


void CinemaGenreCard::clicked_on_card()
{
    CinemaCard *card = dynamic_cast<CinemaCard*>(sender());
    this->last_film = card;
    emit clicked_on_film();
}


void CinemaGenreCard::clicked_on_label()
{
    emit clicked();
}


QString CinemaGenreCard::get_id_film()
{
    return this->id_film;
}


QString CinemaGenreCard::get_id_genre()
{
    return this->id_genre;
}


void CinemaGenreCard::mousePressEvent(QMouseEvent *mouse)
{
    emit clicked();
}


CinemaCard* CinemaGenreCard::get_last_film()
{
    return this->last_film;
}
