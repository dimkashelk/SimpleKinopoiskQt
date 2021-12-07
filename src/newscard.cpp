#include "newscard.h"
#include "ui_newscard.h"
#include "clickedqlabel.h"

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
    original_image = image;

    this->setMinimumWidth(150);
    this->setMaximumHeight(250);

    delete this->ui->news_label;
    delete this->ui->news_text;
    delete this->ui->news_image;

    ClickableQLabel *news_label = new ClickableQLabel("text", this);
    this->ui->verticalLayout->addWidget(news_label);

    ClickableQLabel *news_image = new ClickableQLabel("text", this);
    this->ui->horizontalLayout->addWidget(news_image);



    this->ui->news_label->setText(title);

    //this->ui->news_text->setText(text);

    this->ui->news_image->setPixmap(QPixmap::fromImage(image, Qt::AutoColor));
}

NewsCard::~NewsCard()
{
    delete ui;
}
