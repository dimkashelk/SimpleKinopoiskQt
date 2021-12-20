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

    init_popular();
    
    init_new_news();

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
        id_news = send->get_id_news();
    } else {
        this->ui->stackedWidget->setCurrentIndex(0);
    }
}


void MainWindow::set_info_news_show(NewsCard *card)
{
    if (id_news != card->get_id_news()) {
        card->increase_count_views();

        this->ui->title->setText(card->get_title());
        this->ui->title->setAlignment(Qt::AlignHCenter);
        this->ui->image->setPixmap(QPixmap::fromImage(card->get_image().scaledToWidth(width() / 100 * 70), Qt::AutoColor));
        this->ui->image->setAlignment(Qt::AlignHCenter);
        this->ui->text->setText(card->get_text());
    }
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
            NewsCard *new_card = new NewsCard(db, this, get_10_news.value(0).toString(), get_10_news.value(1).toString(), get_10_news.value(3).toString(), get_10_news.value(2).toString(), QImage::fromData(get_10_news.value(4).toByteArray()), get_10_news.value(5).toString());
			this->ui->popular_scroll->addWidget(new_card);
            connect(new_card, &NewsCard::clicked, this, &MainWindow::change_widget);
		}
	}

    this->ui->back->setMinimumHeight(this->height());
    this->ui->forward->setMinimumHeight(this->height());
}


void MainWindow::init_new_news() 
{
    QSqlQuery get_10_new_news("SELECT id, title, description, text, image, count_views FROM news ORDER BY date LIMIT 10", db);
	if (get_10_new_news.isActive()) {
		while (get_10_new_news.next()) {
            NewsCard *new_card = new NewsCard(db, this, get_10_new_news.value(0).toString(), get_10_new_news.value(1).toString(), get_10_new_news.value(3).toString(), get_10_new_news.value(2).toString(), QImage::fromData(get_10_new_news.value(4).toByteArray()), get_10_new_news.value(5).toString());
            this->ui->new_scroll->addWidget(new_card);
            connect(new_card, &NewsCard::clicked, this, &MainWindow::change_widget);
		}
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

    for (auto i: genres) {
        CinemaGenreCard *new_card = new CinemaGenreCard(db, this, i);
        this->ui->collection_cinema->addWidget(new_card);
        connect(new_card, &CinemaGenreCard::clicked, this, &MainWindow::change_cinema_widget);
        connect(new_card, &CinemaGenreCard::clicked_on_film, this, &MainWindow::change_film_widget);
    }

    this->ui->tabWidget->setTabEnabled(2, false);
    this->ui->to_genre_card->setEnabled(false);

    this->ui->to_collection->setMinimumHeight(this->height());
    this->ui->to_genre_card->setMinimumHeight(this->height());
}


void MainWindow::change_film_widget()
{
    CinemaGenreCard *card = dynamic_cast<CinemaGenreCard*>(sender());
    set_film_info(card->get_last_film()->get_id_film());

    this->ui->tabWidget->setCurrentIndex(2);
}


void MainWindow::change_cinema_widget() {
    CinemaGenreCard *card = dynamic_cast<CinemaGenreCard*>(sender());
    QSet<QString> films;
    QSqlQuery get_all_films("SELECT film FROM genre_film WHERE genre = " + card->get_id_genre(), db);
    while (get_all_films.next()) {
        films.insert(get_all_films.value(0).toString());
    }
    QSqlQuery get_name("SELECT genre FROM genres WHERE id = " + card->get_id_genre(), db);
    get_name.next();
    this->ui->name_genre->setText(get_name.value(0).toString());
    int count = 0;
    for (auto i: films) {
        QSqlQuery get_film("SELECT image FROM films WHERE id = " + i, db);
        get_film.next();
        CinemaCard *new_card = new CinemaCard(QImage::fromData(get_film.value(0).toByteArray()), i, this);
        this->ui->genre_layout->addWidget(new_card, count / 3, count % 3, Qt::AlignCenter);
        connect(new_card, &CinemaCard::clicked, this, &MainWindow::clicked_on_card_film);
        count++;
    }
    this->ui->cinema_stacked->setCurrentIndex(1);

    this->ui->to_genre_card->setEnabled(true);
}


void MainWindow::set_film_info(QString id_film)
{
    QLayoutItem *item;
    while((item = this->ui->film_form->takeAt(0))) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    this->ui->film_form->setVerticalSpacing(10);

    QSqlQuery get_film("SELECT title, " // 0 название
                       "description, "  // 1 описание
                       "image, "        // 2 постер
                       "year, "         // 3 год производства
                       "slogan, "       // 4 слоган
                       "money_usa, "    // 5 сбора в США
                       "money_world, "  // 6 сборы в мире
                       "money_ru, "     // 7 сборы в России
                       "premier_ru, "   // 8 премьера в России
                       "premier_world, "// 9 премьера в мире
                       "age, "          // 10 возрастное ограничение минкульт
                       "mpaa, "         // 11 рейтинг MPAA
                       "time "          // 12 продолжительность
                       "FROM films WHERE id = " + id_film, db);
    get_film.next();
    this->ui->film_name->setText(get_film.value(0).toString());
    this->ui->film_poster->setPixmap(QPixmap::fromImage(QImage::fromData(get_film.value(2).toByteArray())));
    this->ui->film_description->setText(get_film.value(1).toString());

    this->ui->film_form->addRow(new QLabel("Год производства"), new QLabel(get_film.value(3).toString()));
    this->ui->film_form->addRow(new QLabel("Слоган"), new QLabel(get_film.value(4).toString()));

    QSqlQuery get_countries("SELECT id_country FROM country_film WHERE id_film = " + id_film, db);
    QList<QString> countries;
    while (get_countries.next()) {
        countries.append(get_countries.value(0).toString());
    }
    QList<QString> country;
    for (auto i: countries) {
        QSqlQuery get_country("SELECT country FROM countries WHERE id = " + i, db);
        get_country.next();
        country.append(get_country.value(0).toString());
    }
    this->ui->film_form->addRow(new QLabel("Страна"), new QLabel(get_string_to_insert(country)));

    QSqlQuery get_involved("SELECT id_person FROM involved WHERE id_film = " + id_film, db);
    QList<QString> involved;
    while (get_involved.next()) {
        involved.append(get_involved.value(0).toString());
    }

    QList<QString> directors;
    QList<QString> screenwriters;
    QList<QString> producers;
    QList<QString> operators;
    QList<QString> composers;
    QList<QString> artists;
    QList<QString> mountings;
    for (auto i: involved) {
        QSqlQuery get_person("SELECT first_name, second_name, role FROM persons WHERE id = " + i, db);
        get_person.next();
        if (get_person.value(2).toString() == "1") {
            directors.append(get_person.value(0).toString() + " " + get_person.value(1).toString());
        } else if (get_person.value(2).toString() == "2") {
            screenwriters.append(get_person.value(0).toString() + " " + get_person.value(1).toString());
        } else if (get_person.value(2).toString() == "3") {
            producers.append(get_person.value(0).toString() + " " + get_person.value(1).toString());
        } else if (get_person.value(2).toString() == "4") {
            operators.append(get_person.value(0).toString() + " " + get_person.value(1).toString());
        } else if (get_person.value(2).toString() == "5") {
            composers.append(get_person.value(0).toString() + " " + get_person.value(1).toString());
        } else if (get_person.value(2).toString() == "6") {
            artists.append(get_person.value(0).toString() + " " + get_person.value(1).toString());
        } else if (get_person.value(2).toString() == "7") {
            mountings.append(get_person.value(0).toString() + " " + get_person.value(1).toString());
        }
    }

    this->ui->film_form->addRow(new QLabel("Режиссёр"), new QLabel(get_string_to_insert(directors)));
    this->ui->film_form->addRow(new QLabel("Сценарий"), new QLabel(get_string_to_insert(screenwriters)));
    this->ui->film_form->addRow(new QLabel("Продюсер"), new QLabel(get_string_to_insert(producers)));
    this->ui->film_form->addRow(new QLabel("Оператор"), new QLabel(get_string_to_insert(operators)));
    this->ui->film_form->addRow(new QLabel("Композитор"), new QLabel(get_string_to_insert(composers)));
    this->ui->film_form->addRow(new QLabel("Художник"), new QLabel(get_string_to_insert(artists)));
    this->ui->film_form->addRow(new QLabel("Монтаж"), new QLabel(get_string_to_insert(mountings)));

    this->ui->film_form->addRow(new QLabel("Сборы в США"), new QLabel(get_film.value(5).toString()));
    this->ui->film_form->addRow(new QLabel("Сборы в мире"), new QLabel(get_film.value(6).toString()));
    this->ui->film_form->addRow(new QLabel("Сборы в России"), new QLabel(get_film.value(7).toString()));
    this->ui->film_form->addRow(new QLabel("Премьера в России"), new QLabel(get_film.value(8).toString()));
    this->ui->film_form->addRow(new QLabel("Премьера в мире"), new QLabel(get_film.value(9).toString()));

    QSqlQuery get_film_age("SELECT age FROM age WHERE id = " + get_film.value(10).toString(), db);
    if (get_film_age.isActive()) {
        get_film_age.next();
        this->ui->film_form->addRow(new QLabel("Возрастное ограничение"), new QLabel(get_film_age.value(0).toString()));
    } else {
        this->ui->film_form->addRow(new QLabel("Возрастное ограничение"), new QLabel(get_film.value(10).toString()));
    }

    QSqlQuery get_film_mpaa("SELECT mpaa FROM mpaa WHERE id = " + get_film.value(11).toString(), db);
    if (get_film_mpaa.isActive()) {
        get_film_mpaa.next();
        this->ui->film_form->addRow(new QLabel("Рейтинг MPAA"), new QLabel(get_film_mpaa.value(0).toString()));
    } else {
        this->ui->film_form->addRow(new QLabel("Рейтинг MPAA"), new QLabel(get_film.value(11).toString()));
    }
    this->ui->film_form->addRow(new QLabel("Продолжительность"), new QLabel(get_film.value(12).toString()));

    this->ui->tabWidget->setTabEnabled(2, true);
}


void MainWindow::clicked_on_card_film()
{
    CinemaCard *card = dynamic_cast<CinemaCard*>(sender());
    set_film_info(card->get_id_film());

    this->ui->tabWidget->setCurrentIndex(2);
}


void MainWindow::on_to_genre_card_clicked()
{
    this->ui->cinema_stacked->setCurrentIndex(1);
}


void MainWindow::on_to_collection_clicked()
{
    this->ui->cinema_stacked->setCurrentIndex(0);
}


QString MainWindow::get_string_to_insert(QList<QString> values)
{
    QString to_ins_string;
    if (values.size() == 0) {
        to_ins_string = "—";
    } else {
        to_ins_string = values[0];
        values.removeFirst();
        for (auto i: values) {
            to_ins_string = to_ins_string + ", " + i;
        }
    }
    return to_ins_string;
}
