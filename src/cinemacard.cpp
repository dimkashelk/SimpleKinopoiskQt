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


CinemaCard::CinemaCard(QImage image, QString title, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CinemaCard)
{
    ui->setupUi(this);

    this->ui->label->setPixmap(QPixmap::fromImage(image));
}
