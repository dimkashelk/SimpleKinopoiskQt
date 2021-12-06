#include "newscard.h"
#include "ui_newscard.h"

NewsCard::NewsCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewsCard)
{
    ui->setupUi(this);

    this->ui->news_text->setText("TEST");
}

NewsCard::~NewsCard()
{
    delete ui;
}
