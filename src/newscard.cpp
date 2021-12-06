#include "newscard.h"
#include "ui_newscard.h"

NewsCard::NewsCard(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::NewsCard)
{
    ui->setupUi(this);
}

NewsCard::~NewsCard()
{
    delete ui;
}
