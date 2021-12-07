#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newscard.h"
#include <Qt>
#include <QSqlDatabase>
#include <QImage>
#include <QAction>
#include <QSqlQuery>
#include <QBuffer>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->ui->stackedWidget->setCurrentIndex(0);

    db = QSqlDatabase::addDatabase("QSQLITE", "db");
    db.setDatabaseName("db.db");
    db.open();

    QSqlQuery test("SELECT image, title, description, text FROM news WHERE id = 1", db);
    test.next();
    QImage t;
    t.loadFromData(test.value(0).toByteArray());
    t = t.scaledToWidth(250);
    NewsCard *news_card = new NewsCard(this, test.value(1).toString(), test.value(3).toString(), test.value(2).toString(), t);
    this->ui->popular_scroll->addWidget(news_card);

    connect(news_card, &NewsCard::clicked, this, &MainWindow::change_widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::change_widget() {
    NewsCard *send = dynamic_cast<NewsCard*>(sender());
    if (this->ui->stackedWidget->currentIndex() == 0) {
        set_info_news_show(send);
        this->ui->stackedWidget->setCurrentIndex(1);
    } else {
        this->ui->stackedWidget->setCurrentIndex(0);
    }
}


void MainWindow::set_info_news_show(NewsCard *card) {

    QLayoutItem* item;
    while ((item = this->ui->news_scroll->takeAt(0)) != NULL) {
        delete item->widget();
        delete item;
    }

    news_title = new QTextEdit(this);
    news_title->setText(card->get_title());
    news_title->setReadOnly(true);
    news_title->setAlignment(Qt::AlignHCenter);
    this->ui->news_scroll->addWidget(news_title);

    QImage image = card->get_image();
    image = image.scaledToHeight(this->width()*1.0 / 100 * 50);
    news_image_label = new QLabel(this);
    news_image_label->setPixmap(QPixmap::fromImage(image, Qt::AutoColor));
    news_image_label->setAlignment(Qt::AlignHCenter);
    this->ui->news_scroll->addWidget(news_image_label);

    news_text = new QTextEdit(this);
    news_text->setText(card->get_text());
    news_text->setReadOnly(true);
    this->ui->news_scroll->addWidget(news_text);

}

