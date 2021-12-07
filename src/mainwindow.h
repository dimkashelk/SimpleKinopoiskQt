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

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;

    void change_widget();

    void set_info_news_show(NewsCard *card);
};
#endif // MAINWINDOW_H
