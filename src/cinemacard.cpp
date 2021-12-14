#include "cinemacard.h"
#include "ui_cinemacard.h"
#include "clickedqlabel.h"
#include <QVBoxLayout>

CinemaCard::CinemaCard(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CinemaCard)
{
    ui->setupUi(this);

    this->setMaximumSize(140, 250);
}

CinemaCard::~CinemaCard()
{
    delete ui;
}


CinemaCard::CinemaCard(QImage image, QString title, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CinemaCard)
{
    this->setMaximumSize(140, 250);

    image = image.scaled(140, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ClickableQLabel *image_label = new ClickableQLabel("", this);
    image_label->setPixmap(QPixmap::fromImage(image, Qt::AutoColor));

    this->ui->layout->addWidget(image_label);

    connect(image_label, &ClickableQLabel::clicked, this, &CinemaCard::on_image_clicked);
}


void CinemaCard::on_image_clicked() {
    emit clicked();
}


void CinemaCard::mousePressEvent(QMouseEvent *event) {
    emit clicked();
}
