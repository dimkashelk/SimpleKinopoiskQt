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

    this->ui->tabWidget->setCurrentIndex(0);

    this->ui->stackedWidget->setCurrentIndex(0);

    this->ui->cinema_stacked->setCurrentIndex(0);

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
    CinemaGenreCard *card = dynamic_cast<CinemaGenreCard*>(sender());
    if (card->get_id_film() == "-1") {
        QSet<QString> films;
        QSqlQuery get_all_films("SELECT film FROM genre_film WHERE genre = " + card->get_id_genre(), db);
        qDebug() << get_all_films.isActive();
        while (get_all_films.next()) {
            films.insert(get_all_films.value(0).toString());
        }
        qDebug() << card->get_id_genre();
        QSqlQuery get_name("SELECT genre FROM genres WHERE id = " + card->get_id_genre(), db);
        qDebug() << get_name.isActive();
        get_name.next();
        this->ui->name_genre->setText(get_name.value(0).toString());
        int count = 0;
        for (auto i: films) {
            QSqlQuery get_film("SELECT image, title FROM films WHERE id = " + i, db);
            get_film.next();
            CinemaCard *new_card = new CinemaCard(QImage::fromData(get_film.value(0).toByteArray()), get_all_films.value(0).toString(), this);
            this->ui->genre_layout->addWidget(new_card, count / 3, count % 3, Qt::AlignCenter);
            count++;
        }
        this->ui->cinema_stacked->setCurrentIndex(1);
    } else {
        QSqlQuery get_film("SELECT title, " // 0 название
                           "description, "  // 1 описание
                           "image, "        // 2 постер
                           "year, "         // 3 год производства
                           "slogan, "       // 4 слоган
                           "country, "      // 5 страна производства
                           "director, "     // 6 режиссер
                           "screenwriter, " // 7 сценарий
                           "producer, "     // 8 продюсер
                           "operator, "     // 9 оператор
                           "composer, "     // 10 композитор
                           "artist, "       // 11 художник
                           "mounting, "     // 12 монтаж
                           "money_usa, "    // 13 сбора в США
                           "money_world, "  // 14 сборы в мире
                           "money_ru, "     // 15 сборы в России
                           "premier_ru, "   // 16 премьера в России
                           "premier_world, "// 17 премьера в мире
                           "age, "          // 18 возрастное ограничение минкульт
                           "mpaa, "         // 19 рейтинг MPAA
                           "time "          // 20 продолжительность
                           "FROM films WHERE id = " + card->get_id_film(), db);
        get_film.next();
        this->ui->film_name->setText(get_film.value(0).toString());
        this->ui->film_poster->setPixmap(QPixmap::fromImage(QImage::fromData(get_film.value(2).toByteArray())));
        this->ui->film_description->setText(get_film.value(1).toString());

        this->ui->film_form->addRow(new QLabel("Год производства"), new QLabel(get_film.value(3).toString()));
        this->ui->film_form->addRow(new QLabel("Слоган"), new QLabel(get_film.value(4).toString()));
        this->ui->film_form->addRow(new QLabel("Страна"), new QLabel(get_film.value(5).toString()));
        this->ui->film_form->addRow(new QLabel("Режиссёр"), new QLabel(get_film.value(6).toString()));
        this->ui->film_form->addRow(new QLabel("Сценарий"), new QLabel(get_film.value(7).toString()));
        this->ui->film_form->addRow(new QLabel("Продюсер"), new QLabel(get_film.value(8).toString()));
        this->ui->film_form->addRow(new QLabel("Оператор"), new QLabel(get_film.value(9).toString()));
        this->ui->film_form->addRow(new QLabel("Композитор"), new QLabel(get_film.value(10).toString()));
        this->ui->film_form->addRow(new QLabel("Художник"), new QLabel(get_film.value(11).toString()));
        this->ui->film_form->addRow(new QLabel("Монтаж"), new QLabel(get_film.value(12).toString()));
        this->ui->film_form->addRow(new QLabel("Сборы в США"), new QLabel(get_film.value(13).toString()));
        this->ui->film_form->addRow(new QLabel("Сборы в мире"), new QLabel(get_film.value(14).toString()));
        this->ui->film_form->addRow(new QLabel("Сборы в России"), new QLabel(get_film.value(15).toString()));
        this->ui->film_form->addRow(new QLabel("Премьера в России"), new QLabel(get_film.value(16).toString()));
        this->ui->film_form->addRow(new QLabel("Премьера в мире"), new QLabel(get_film.value(17).toString()));
        this->ui->film_form->addRow(new QLabel("Возрастное ограничение"), new QLabel(get_film.value(18).toString()));
        this->ui->film_form->addRow(new QLabel("Рейтинг MPAA"), new QLabel(get_film.value(19).toString()));
        this->ui->film_form->addRow(new QLabel("Продолжительность"), new QLabel(get_film.value(20).toString()));

        this->ui->tabWidget->setCurrentIndex(2);
    }
}
