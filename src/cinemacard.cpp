#include "cinemacard.h"
#include "ui_cinemacard.h"
#include "clickedqlabel.h"
#include <QVBoxLayout>

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


CinemaCard::CinemaCard(QImage image, QString title, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CinemaCard)
{
    QFrame *frame = new QFrame();

    frame->setMaximumSize(355, 200);

    QVBoxLayout *main = new QVBoxLayout(this);
    const QRect geo = QRect(0, 0, 355, 200);
    main->setGeometry(geo);

    ClickableQLabel *image_label = new ClickableQLabel("", this);
    image_label->setPixmap(QPixmap::fromImage(image, Qt::AutoColor));
    main->addWidget(image_label);

    frame->setLayout(main);

    this->ui->setupUi(frame);
}
