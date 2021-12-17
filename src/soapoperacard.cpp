#include "soapoperacard.h"
#include "ui_soapoperacard.h"

SoapOperaCard::SoapOperaCard(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SoapOperaCard)
{
    ui->setupUi(this);

    this->setMaximumSize(355, 200);
}

SoapOperaCard::~SoapOperaCard()
{
    delete ui;
}
