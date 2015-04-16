#include "mainwindow.h"

#include "bucketlist.h"

#include <QLabel>
#include <QBoxLayout>
#include <QtWebKit>
#include <QSettings>
#include <QInputDialog>
#include <QFileSystemWatcher>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *central = new QWidget;
    setCentralWidget(central);

    QBoxLayout *topLayout = new QHBoxLayout(central);

    BucketList *bucketList = new BucketList;
    topLayout->addWidget(bucketList);

    m_view = new QWebView;
    topLayout->addWidget(m_view, 1);
    m_view->setMinimumSize(1080, 600);

    getServerPath();

    m_dirWatcher = new QFileSystemWatcher(this);
    connect(m_dirWatcher, SIGNAL(fileChanged(QString)), SLOT(loadView()));

    setWatchedFiles();

    connect(&m_server, SIGNAL(started()), SLOT(loadView()));
    m_server.start();
}

MainWindow::~MainWindow()
{
    m_server.stop();
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

void MainWindow::loadView()
{
    QUrl url("http://localhost");
    url.setPort(m_server.port());
    m_view->setUrl(url);
    m_view->show();

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
