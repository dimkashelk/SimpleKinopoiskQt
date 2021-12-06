#include "filmcard.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QPixmap>
#include <QTextEdit>

FilmCard::FilmCard(QWidget *parent) : QWidget(parent)
{

}

FilmCard::FilmCard(QString film_name, QString film_description, QImage image) {
    this->setMinimumHeight(500);
    this->film_name = film_name;
    this->description = film_description;
    this->image = image;
    this->setStyleSheet("background-color: rgba(255, 255, 255, 0);"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-radius: 10px;"
                        "border-color: white;");

    QVBoxLayout *main_layout = new QVBoxLayout(this);

    QLabel *film_name_label = new QLabel(film_name);
    film_name_label->setStyleSheet("padding-left: 10px;"
                                   "font: 18px \"Segoe UI\";"
                                   "color: white;"
                                   "background-color: rgba(255, 255, 255, 0);");
    main_layout->addWidget(film_name_label);

    QHBoxLayout *dop_layout = new QHBoxLayout(this);
    QPixmap pixmap_image;
    pixmap_image.fromImage(image);
    QLabel *film_image = new QLabel();
    film_image->setPixmap(pixmap_image);
//    film_image->setStyleSheet("width: 150px;"
//                              "min-width: 50px;"
//                              "height: 150px;"
//                              "min-height: 50px;"
//                              "border-radius: 10px;");
    dop_layout->addWidget(film_image);

// TODO
    QTextEdit description;
    description.setText(film_description);
    film_name_label->setStyleSheet("padding-left: 10px;"
                                   "font: \"Segoe UI\" 18px white"
                                   "background-color: rgba(255, 255, 255, 0);");
    dop_layout->addWidget(new QLabel(film_description));
// TODO

    main_layout->addLayout(dop_layout);

    this->setLayout(main_layout);
}
