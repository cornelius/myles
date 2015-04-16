#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "webserver.h"

#include <QMainWindow>

class QWebView;

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

public slots:
    void loadView();

private:
    QWebView *m_view;
    WebServer m_server;
};

#endif
