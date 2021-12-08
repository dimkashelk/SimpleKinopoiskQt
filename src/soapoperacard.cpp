#include "soapoperacard.h"
#include "ui_soapoperacard.h"

SoapOperaCard::SoapOperaCard(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SoapOperaCard)
{
    ui->setupUi(this);
}

SoapOperaCard::~SoapOperaCard()
{
    delete ui;
}
