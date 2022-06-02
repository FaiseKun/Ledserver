#include "ledserver.h"
#include <QDebug>

LedServer::LedServer(quint16 port, QObject *parent) : QObject(parent), m_port(port)
{
    m_server = new QTcpServer(this);

    connect(m_server, &QTcpServer::newConnection, this, &LedServer::myNewConnection);
}

void LedServer::start()
{
    if (!m_server->listen(QHostAddress::Any, m_port))
           throw m_server->errorString();
}

// Client hat Verbindung zum Server aufgebaut
void LedServer::myNewConnection()
{
    m_gpio = new Gpio(this);
    m_socket = m_server->nextPendingConnection();
    m_socket->write("Bitte Zahl von 0 bis 15 eingeben:\n");
    connect(m_socket, &QTcpSocket::disconnected, this, &LedServer::myClientDisconnect);
    connect(m_socket, &QTcpSocket::readyRead, this, &LedServer::myServerRead);
}

// Client hat Verbindung zum Server getrennt
void LedServer::myClientDisconnect()
{
    m_socket->close();
    m_gpio->~Gpio();
}

// Client hat eine Zahl (0...15) zum Server gesendet
void LedServer::myServerRead()
{
    QString msg = m_socket->readAll();

    int m = msg.toInt();

    if(m <= 15 && m >= 0)
    {
        m_socket->write("Ok\n");
        m_gpio->set(m);
    }
    m_socket->write("Bitte Zahl von 0 bis 15 eingeben:\n");
}
