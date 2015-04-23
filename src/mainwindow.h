#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "webserver.h"

#include <QMainWindow>

class Model;

class QWebView;
class QFileSystemWatcher;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString viewPath();
    QStringList viewFiles();
    QStringList viewDependenciesFiles();

    void initView();
    void setWatchedFiles();

    void showLoadingMessage();

public slots:
    void loadView();
    void delayedLoadView();

private:
    Model *m_model;

    QWebView *m_view;
    WebServer m_server;
    QFileSystemWatcher *m_dirWatcher;
};

#endif
