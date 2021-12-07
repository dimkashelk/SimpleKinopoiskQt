#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newscard.h"
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

    db = QSqlDatabase::addDatabase("QSQLITE", "db");
    db.setDatabaseName("db.db");
    db.open();

    QPixmap image("image.jpg");
    QByteArray inByteArray;
    QBuffer inBuffer(&inByteArray);
    inBuffer.open(QIODevice::WriteOnly);
    image.save(&inBuffer, "JPG");

    QSqlQuery query = QSqlQuery(db);
    query.prepare("UPDATE news SET image = :imageData WHERE id = 1");
    query.bindValue(":imageData", inByteArray);
    query.exec();

    QSqlQuery test("SELECT image, title, description FROM news WHERE id = 1", db);
    test.next();
    QImage t;
    t.loadFromData(test.value(0).toByteArray());
    t = t.scaledToWidth(250);
    this->ui->popular_scroll->addWidget(new NewsCard(this, test.value(1).toString(), test.value(2).toString(), t));
}

MainWindow::~MainWindow()
{
    delete ui;
}

