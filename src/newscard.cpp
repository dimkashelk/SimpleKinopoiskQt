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

NewsCard::NewsCard(QWidget *parent, QString title, QString descpription, QString text, QImage image) :
    QFrame(parent),
    ui(new Ui::NewsCard)
{
    ui->setupUi(this);
    original_image = new QImage(image);
    this->text = descpription;

    image = image.scaledToWidth(250);

    this->setMinimumWidth(150);
    this->setMaximumHeight(250);

    news_label = new ClickableQLabel("text", this);
    this->ui->verticalLayout->addWidget(news_label);

    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);

    news_image = new ClickableQLabel("text", this);
    horizontalLayout->addWidget(news_image);

    news_description = new ClickableQTextEdit("text", this);
    horizontalLayout->addWidget(news_description);
    news_description->setReadOnly(true);
    news_description->setCursor(Qt::PointingHandCursor);

    this->ui->verticalLayout->addLayout(horizontalLayout);

    news_label->setText(title);

    news_description->setText(text);

    news_image->setPixmap(QPixmap::fromImage(image, Qt::AutoColor));

    connect(news_label, &ClickableQLabel::clicked, this, &NewsCard::send_signal_clicked);
    connect(news_description, &ClickableQTextEdit::clicked, this, &NewsCard::send_signal_clicked);
    connect(news_image, &ClickableQLabel::clicked, this, &NewsCard::send_signal_clicked);
}

NewsCard::~NewsCard()
{
    delete ui;
}


void NewsCard::send_signal_clicked() {
    emit clicked();
}


void NewsCard::mousePressEvent(QMouseEvent *event) {
    emit clicked();
}


QString NewsCard::get_title() {
    return news_label->text();
}

QString NewsCard::get_text() {
    return this->text;
}

QImage NewsCard::get_image() {
    return *original_image;
}
