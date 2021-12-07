#include "newscard.h"
#include "ui_newscard.h"

NewsCard::NewsCard(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::NewsCard)
{
    ui->setupUi(this);

    this->setMinimumWidth(150);
}

NewsCard::NewsCard(QWidget *parent, QString title, QString text, QImage image) :
    QFrame(parent),
    ui(new Ui::NewsCard)
{
    ui->setupUi(this);

    this->setMinimumWidth(150);
    this->setMaximumHeight(250);

    this->ui->news_label->setText(title);

    this->ui->news_text->setText(text);

    this->ui->news_image->setPixmap(QPixmap::fromImage(image, Qt::AutoColor));
}

NewsCard::~NewsCard()
{
    delete ui;
}
