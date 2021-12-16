#include "cinemacard.h"
#include "ui_cinemacard.h"
#include <QPainter>

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


CinemaCard::CinemaCard(QImage image, QString id, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CinemaCard)
{
    setAttribute(Qt::WA_TranslucentBackground);

    setMinimumHeight(450);
    setMinimumWidth(300);

    ui->setupUi(this);

    background = QPixmap::fromImage(image);

    this->id_film = id;
}

void CinemaCard::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0, 0, width(), height(), background);
}


void CinemaCard::mousePressEvent(QMouseEvent *mouseEvent)
{
    emit clicked();
}


QString CinemaCard::get_id_film()
{
    return this->id_film;
}
