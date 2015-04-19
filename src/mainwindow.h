#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "webserver.h"

#include <QMainWindow>

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

    void getServerPath();
    void setWatchedFiles();

    void showLoadingMessage();

public slots:
    void loadView();
    void delayedLoadView();

private:
    QWebView *m_view;
    WebServer m_server;
    QFileSystemWatcher *m_dirWatcher;
};

#endif
