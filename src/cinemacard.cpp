#include "cinemacard.h"
#include "ui_cinemacard.h"

CinemaCard::CinemaCard(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CinemaCard)
{
    ui->setupUi(this);
}

CinemaCard::~CinemaCard()
{
    delete ui;
}
