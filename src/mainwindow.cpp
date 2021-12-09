#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newscard.h"
#include "cinemacard.h"
#include "soapoperacard.h"
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

    this->ui->tabWidget->setCurrentIndex(0);

    this->ui->stackedWidget->setCurrentIndex(0);

    db = QSqlDatabase::addDatabase("QSQLITE", "db");
    db.setDatabaseName("db.db");
    db.open();

    QSqlQuery test("SELECT image, title, description, text FROM news WHERE id = 5", db);
    test.next();
    QImage t;
    t.loadFromData(test.value(0).toByteArray());
    NewsCard *news_card = new NewsCard(this, test.value(1).toString(), test.value(3).toString(), test.value(2).toString(), t);
    this->ui->popular_scroll->addWidget(news_card);
    this->ui->popular_scroll->addWidget(new NewsCard(this, test.value(1).toString(), test.value(3).toString(), test.value(2).toString(), t));
    this->ui->popular_scroll->addWidget(new NewsCard(this, test.value(1).toString(), test.value(3).toString(), test.value(2).toString(), t));
    this->ui->popular_scroll->addWidget(new NewsCard(this, test.value(1).toString(), test.value(3).toString(), test.value(2).toString(), t));
    this->ui->popular_scroll->addWidget(new NewsCard(this, test.value(1).toString(), test.value(3).toString(), test.value(2).toString(), t));

    CinemaCard *cinema_test = new CinemaCard(this);
    this->ui->collection_cinema->addWidget(cinema_test);


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
        news_info = true;
    } else {
        this->ui->stackedWidget->setCurrentIndex(0);
    }
}


void MainWindow::set_info_news_show(NewsCard *card)
{
    this->ui->title->setText(card->get_title());
    this->ui->title->setAlignment(Qt::AlignHCenter);
    this->ui->image->setPixmap(QPixmap::fromImage(card->get_image().scaledToWidth(width() / 100 * 70), Qt::AutoColor));
    this->ui->image->setAlignment(Qt::AlignHCenter);
    this->ui->text->setText(card->get_text());
}


void MainWindow::on_text_textChanged()
{
    QString s = ui->text->toPlainText();
    QFontMetrics m(ui->text->font());
    QRect widgetRect = ui->text->rect();
    QRect textRect = m.boundingRect(QRect(0, 0, 0, 0), Qt::TextWordWrap,s);
    int x = 10;
    ui->text->setMinimumHeight(this->ui->news_scroll_area->geometry().height() * 1.2);
}


void MainWindow::on_title_textChanged()
{
    QString s = ui->title->toPlainText();
    QFontMetrics m(ui->title->font());
    QRect widgetRect = ui->title->rect();
    QRect textRect = m.boundingRect(QRect(0,0,0,0), Qt::TextWordWrap, s);
    int x = 10;
    ui->title->setMinimumHeight(textRect.height());
    ui->title->setMaximumHeight(textRect.height() * 1.2);
}


void MainWindow::on_back_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_forward_clicked()
{
    if (news_info) {
        this->ui->stackedWidget->setCurrentIndex(1);
    }
}

