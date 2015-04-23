#include "mainwindow.h"

#include "bucketlist.h"
#include "model.h"

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
#include <QStandardPaths>
#include <QFile>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *central = new QWidget;
    setCentralWidget(central);

    QBoxLayout *topLayout = new QHBoxLayout(central);

    QBoxLayout *sideLayout = new QVBoxLayout;
    topLayout->addLayout(sideLayout);

    m_model = new Model;

    BucketList *bucketList = new BucketList(m_model);
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

    initView();
    m_server.setPath(viewPath());

    m_dirWatcher = new QFileSystemWatcher(this);
    connect(m_dirWatcher, SIGNAL(fileChanged(QString)), SLOT(loadView()));

    setWatchedFiles();

    connect(&m_server, SIGNAL(started()), SLOT(delayedLoadView()));
    m_server.start();
}

MainWindow::~MainWindow()
{
    m_server.stop();

    delete m_model;
}

void MainWindow::showLoadingMessage()
{
    m_view->setHtml("Loading...");
}

void MainWindow::delayedLoadView()
{
    QTimer::singleShot(1000, this, SLOT(loadView()));
}

void MainWindow::initView()
{
    QDir dir;
    dir.mkpath(viewPath());

    QStringList files;
    files.append(viewFiles());
    files.append(viewDependenciesFiles());
    files.append("data.json");

    foreach(QString fileName, files) {
        QFile source(":/view/" + fileName);
        QFile target(viewPath() + fileName);

        source.copy(target.fileName());
        target.setPermissions(QFileDevice::ReadUser | QFileDevice::WriteUser |
                              QFileDevice::ReadGroup | QFileDevice::ReadOther);
    }
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
    foreach(QString file, viewFiles()) {
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

QString MainWindow::viewPath()
{
    QString viewPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    viewPath.append("/view/");
    return viewPath;
}

QStringList MainWindow::viewFiles()
{
    QStringList files;
    files << "index.html" << "chart.js" << "chart.css";
    return files;
}

QStringList MainWindow::viewDependenciesFiles()
{
    QStringList files;
    files << "d3.min.js" << "jquery-2.1.3.min.js";
    return files;
}
