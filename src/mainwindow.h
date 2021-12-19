#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "newscard.h"
#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_text_textChanged();

    void on_title_textChanged();

    void on_back_clicked();

    void on_forward_clicked();

    void on_to_genre_card_clicked();

    void on_to_collection_clicked();

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;
    QString id_news;
    QTextEdit *news_title = new QTextEdit(this), *news_text = new QTextEdit(this);
    QLabel *news_image_label = new QLabel(this);

    void change_widget();

    void change_cinema_widget();

    void change_film_widget();

    void set_film_info(QString id_film);

    void clicked_on_card_film();

    void set_info_news_show(NewsCard *card);
    
    void init_popular();
    
    void init_new_news();

    bool news_info = false;

    void init_cinema();

    QString get_string_to_insert(QList<QString> values);
};
#endif // MAINWINDOW_H
