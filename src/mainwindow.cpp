#include "mainwindow.h"

#include "bucketlist.h"

#include <QLabel>
#include <QBoxLayout>
#include <QtWebKit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *central = new QWidget;
    setCentralWidget(central);

    QBoxLayout *topLayout = new QHBoxLayout(central);

    BucketList *bucketList = new BucketList;
    topLayout->addWidget(bucketList);

    QWebView *view = new QWebView;
    topLayout->addWidget(view);
    view->setHtml("<h1>Project MySelf</h1><p>This will be a diagram</p>");
    view->show();
}

MainWindow::~MainWindow()
{
}
