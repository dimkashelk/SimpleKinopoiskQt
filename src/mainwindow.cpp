#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newscard.h"
#include "cinemacard.h"
#include "cinemagenrecard.h"
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

    init_cinema();
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
    this->ui->title->setText("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
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
    QRect textRect = m.boundingRect(QRect(0, 0, 0, 0),Qt::TextWordWrap,s);
    int x = 10;
    ui->text->setMinimumHeight(textRect.height() + x);
}


void MainWindow::on_title_textChanged()
{
    QString s = ui->title->toPlainText();
    QFontMetrics m(ui->title->font());
    QRect widgetRect = ui->title->rect();
    QRect textRect = m.boundingRect(QRect(0,0,0,0), Qt::TextWordWrap, s);
    int x = 10;
    ui->title->setMinimumHeight(textRect.height() + x);
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

void MainWindow::init_cinema()
{
    QSqlQuery genres_query("SELECT genre FROM genres", db);
    QList<QString> genres;
    if (genres_query.isActive()) {
        while (genres_query.next()) {
            genres.append(genres_query.value(0).toString());
        }
    }
    QSet<QString> five_genres;
    while (five_genres.size() < 5) {
        five_genres.insert(genres[rand() % genres.size()]);
    }

    for (auto i: five_genres) {
        CinemaGenreCard *new_card = new CinemaGenreCard(db, this, i);
        this->ui->collection_cinema->addWidget(new_card);
        connect(new_card, &CinemaGenreCard::clicked, this, &MainWindow::change_cinema_widget);
    }
}


void MainWindow::change_cinema_widget() {
    qDebug() << "ILOVE!";
    CinemaGenreCard *card = dynamic_cast<CinemaGenreCard*>(sender());
    if (card->get_id_film() == "-1") {
        QSqlQuery get_all_films("SELECT film FROM genre_film WHERE genre = " + card->get_id_genre(), db);
        QSqlQuery get_name("SELECT genre FROM genres WHERE id = " + card->get_id_genre(), db);
        get_name.next();
        this->ui->name_genre->setText(get_name.value(0).toString());
        if (get_all_films.isActive()) {
            int count = 0;
            while (get_all_films.next()) {
                QSqlQuery get_film("SELECT image, title FROM films WHERE id = " + get_all_films.value(0).toString(), db);
                get_film.next();
                CinemaCard *new_card = new CinemaCard(QImage::fromData(get_film.value(0).toByteArray()), get_all_films.value(0).toString(), this);
                this->ui->genre_layout->addWidget(new_card, count / 3, count % 3, Qt::AlignCenter);
                count++;
            }
        }
        this->ui->cinema_stacked->setCurrentIndex(1);
    }
}
