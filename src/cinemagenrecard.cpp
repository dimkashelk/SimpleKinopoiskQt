#include "cinemagenrecard.h"
#include "ui_cinemagenrecard.h"

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
