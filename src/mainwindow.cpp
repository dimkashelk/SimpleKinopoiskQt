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

    init_popular();
    
    init_new_news();

    CinemaCard *cinema_test = new CinemaCard(this);
    this->ui->collection_cinema->addWidget(cinema_test);
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
	card->increase_count_views();
	
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
    this->ui->text->setMinimumHeight(this->ui->news_scroll_area->geometry().height() * 1.2);
}


void MainWindow::on_title_textChanged()
{
    QString s = ui->title->toPlainText();
    QFontMetrics m(ui->title->font());
    QRect widgetRect = ui->title->rect();
    QRect textRect = m.boundingRect(QRect(0,0,0,0), Qt::TextWordWrap, s);
    int x = 100;
    this->ui->title->setMinimumHeight(textRect.height() * 0.2);
    this->ui->title->setMaximumHeight(textRect.height() * 1.5);
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


void MainWindow::init_popular() 
{	
	QSqlQuery get_10_news("SELECT id, title, description, text, image, count_views FROM news ORDER BY count_views DESC LIMIT 10", db);
	if (get_10_news.isActive()) {
        while (get_10_news.next()) {
            NewsCard *new_card = new NewsCard(this, get_10_news.value(0).toString(), get_10_news.value(1).toString(), get_10_news.value(3).toString(), get_10_news.value(2).toString(), QImage::fromData(get_10_news.value(4).toByteArray()), get_10_news.value(5).toString());
			this->ui->popular_scroll->addWidget(new_card);
            connect(new_card, &NewsCard::clicked, this, &MainWindow::change_widget);
		}
	}
}


void MainWindow::init_new_news() 
{
	QSqlQuery get_10_new_news("SELECT id, title, description, text, image, count_views FROM news LIMIT 10", db);
	if (get_10_new_news.isActive()) {
		while (get_10_new_news.next()) {
            NewsCard *new_card = new NewsCard(this, get_10_new_news.value(0).toString(), get_10_new_news.value(1).toString(), get_10_new_news.value(3).toString(), get_10_new_news.value(2).toString(), QImage::fromData(get_10_new_news.value(4).toByteArray()), get_10_new_news.value(5).toString());
            this->ui->new_scroll->addWidget(new_card);
            connect(new_card, &NewsCard::clicked, this, &MainWindow::change_widget);
		}
	}
}















