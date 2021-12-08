#include "cinemacard.h"
#include "ui_cinemacard.h"

CinemaCard::CinemaCard(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CinemaCard)
{
    ui->setupUi(this);

    this->setMaximumSize(355, 200);
}

CinemaCard::~CinemaCard()
{
    delete ui;
}
