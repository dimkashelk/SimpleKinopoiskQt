#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newscard.h"
#include <Qt>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->ui->popular_scroll->addWidget(new NewsCard(this));
    this->ui->popular_scroll->addWidget(new NewsCard(this));
    this->ui->popular_scroll->addWidget(new NewsCard(this));
    this->ui->popular_scroll->addWidget(new NewsCard(this));
    this->ui->popular_scroll->addWidget(new NewsCard(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

