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

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;
    QTextEdit *news_title = new QTextEdit(this), *news_text = new QTextEdit(this);
    QLabel *news_image_label = new QLabel(this);

    void change_widget();

    void set_info_news_show(NewsCard *card);

    bool news_info = false;

    void init_cinema();
};
#endif // MAINWINDOW_H
