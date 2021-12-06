#include "newscard.h"
#include "ui_newscard.h"

NewsCard::NewsCard(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::NewsCard)
{
    ui->setupUi(this);

    this->setMinimumWidth(150);

    this->ui->news_text->setText("TEST TEXT!");
}

NewsCard::~NewsCard()
{
    delete ui;
}
