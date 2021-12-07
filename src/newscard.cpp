#include "newscard.h"
#include "ui_newscard.h"
#include "clickedqlabel.h"
#include "clickableqtextedit.h"
#include <QHBoxLayout>

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

    ClickableQLabel *news_label = new ClickableQLabel("text", this);
    this->ui->verticalLayout->addWidget(news_label);

    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);

    ClickableQLabel *news_image = new ClickableQLabel("text", this);
    horizontalLayout->addWidget(news_image);

    ClickableQTextEdit *news_text = new ClickableQTextEdit("text", this);
    horizontalLayout->addWidget(news_text);
    news_text->setReadOnly(true);
    news_text->setCursor(Qt::PointingHandCursor);

    this->ui->verticalLayout->addLayout(horizontalLayout);

    news_label->setText(title);

    news_text->setText(text);

    news_image->setPixmap(QPixmap::fromImage(image, Qt::AutoColor));

    connect(news_label, &ClickableQLabel::clicked, this, &NewsCard::send_signal_clicked);
}

NewsCard::~NewsCard()
{
    delete ui;
}


void NewsCard::send_signal_clicked() {
    emit clicked();
}
