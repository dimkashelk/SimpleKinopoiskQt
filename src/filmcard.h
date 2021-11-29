#ifndef FILMCARD_H
#define FILMCARD_H

#include <QWidget>

class FilmCard : public QWidget
{
    Q_OBJECT
public:
    explicit FilmCard(QWidget *parent = nullptr);

    FilmCard(QString film_name, QString film_description, QImage image);


private:
    QString film_name;
    QString description;
    QImage image;


signals:

};

#endif // FILMCARD_H
