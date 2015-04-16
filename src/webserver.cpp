#include "webserver.h"

#include <QProcess>

WebServer::WebServer()
    : m_port(8765), m_process(0)
{
}

WebServer::~WebServer()
{
    stop();
}

void WebServer::setPath(const QString &path)
{
    m_path = path;
}

void WebServer::setPort(int port)
{
    m_port = port;
}

int WebServer::port() const
{
    return m_port;
}

void WebServer::start()
{
    if(!m_process) {
        m_process = new QProcess;
        connect(m_process, SIGNAL(started()), SIGNAL(started()));
    } else {
        stop();
    }

    m_process->setWorkingDirectory(m_path);

    QString program = "python";
    QStringList arguments;
    arguments << "-m" << "SimpleHTTPServer" << QString::number(m_port);

    m_process->start(program, arguments);
}

void WebServer::stop()
{
    if (m_process) {
        m_process->kill();
    }
}
