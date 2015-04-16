#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QObject>
#include <QString>

class QProcess;

class WebServer : public QObject
{
    Q_OBJECT
public:
    WebServer();
    virtual ~WebServer();

    void setPath(const QString &path);
    QString path() const;

    void setPort(int port);
    int port() const;

    void start();
    void stop();

signals:
    void started();

private:
    QString m_path;
    int m_port;

    QProcess *m_process;
};

#endif
