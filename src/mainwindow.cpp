#include "mainwindow.h"

#include "bucketlist.h"

#include <QLabel>
#include <QBoxLayout>
#include <QWebView>
#include <QSettings>
#include <QInputDialog>
#include <QFileSystemWatcher>
#include <QDebug>
#include <QPushButton>
#include <QTimer>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *central = new QWidget;
    setCentralWidget(central);

    QBoxLayout *topLayout = new QHBoxLayout(central);

    QBoxLayout *sideLayout = new QVBoxLayout;
    topLayout->addLayout(sideLayout);

    BucketList *bucketList = new BucketList;
    sideLayout->addWidget(bucketList);

    QPushButton *button = new QPushButton("Reload View");
    sideLayout->addWidget(button);
    connect(button, SIGNAL(clicked(bool)), SLOT(loadView()));

    button = new QPushButton("Close Window");
    sideLayout->addWidget(button);
    connect(button, SIGNAL(clicked(bool)), SLOT(close()));

    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+Q"), this);
    QObject::connect(shortcut, SIGNAL(activated()), SLOT(close()));

    m_view = new QWebView;
    topLayout->addWidget(m_view, 1);
    m_view->setMinimumSize(1080, 600);
    showLoadingMessage();

    getServerPath();

    m_dirWatcher = new QFileSystemWatcher(this);
    connect(m_dirWatcher, SIGNAL(fileChanged(QString)), SLOT(loadView()));

    setWatchedFiles();

    connect(&m_server, SIGNAL(started()), SLOT(delayedLoadView()));
    m_server.start();
}

MainWindow::~MainWindow()
{
    m_server.stop();
}

void MainWindow::showLoadingMessage()
{
    m_view->setHtml("Loading...");
}

void MainWindow::getServerPath()
{
    QSettings settings;

    QString path = settings.value("view/path").toString();
    if (path.isEmpty()) {
        path = QInputDialog::getText(this, "View path", "Enter base path of view for web server");
    }
    settings.setValue("view/path", path);

    m_server.setPath(path);
}

void MainWindow::delayedLoadView()
{
    QTimer::singleShot(1000, this, SLOT(loadView()));
}

void MainWindow::loadView()
{
    QUrl url("http://localhost");
    url.setPort(m_server.port());
    m_view->setUrl(url);

    setWatchedFiles();
}

void MainWindow::setWatchedFiles()
{
    QStringList files;
    files << "index.html" << "chart.js" << "chart.css";

    foreach(QString file, files) {
        QString path = m_server.path();
        if(!path.endsWith("/")) {
            path += "/";
        }
        path += file;
        if(!m_dirWatcher->files().contains(path)) {
            m_dirWatcher->addPath(path);
        }
    }
}
