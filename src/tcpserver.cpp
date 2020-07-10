#include "tcpserver.h"
#include <QDebug>
#include <QDataStream>
MyTcpServer::MyTcpServer(quint16 serverPort, QObject *parent) : QObject(parent)
{
    _tcpServer = new QTcpServer();
    connect(_tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!_tcpServer->listen(QHostAddress::Any, serverPort))
        qDebug() << "> ERROR: TCP Server is not started";
    else
    {
        qDebug().noquote() << QString("> TCP Server is started on %1 port")
                              .arg(serverPort);
        qDebug() << "===> Server is working...";
    }

}

MyTcpServer::~MyTcpServer()
{
    delete _tcpServer;
}

void MyTcpServer::newConnection()
{
    QTcpSocket * newTcpSocket(_tcpServer->nextPendingConnection());

    // Выводим информацию о новом подключении
    QHostAddress clientIP(newTcpSocket->peerAddress().toIPv4Address());
    qDebug().noquote() <<"> "  + clientIP.toString() + " connected";

    _tcpClients.append(newTcpSocket);

    connect(newTcpSocket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    connect(newTcpSocket, SIGNAL(readyRead()), this, SLOT(serverRead()));
}

void MyTcpServer::serverRead()
{
    QTcpSocket* tcpSocket = static_cast<QTcpSocket*>(sender());
    while( (tcpSocket->bytesAvailable()) > 0)
    {
        QByteArray array = tcpSocket->readAll();
        QHostAddress clientIP(tcpSocket->peerAddress().toIPv4Address());
        qDebug().noquote() <<QString("> Recieve message:") + QString(array.toHex()) + QString("; from %1").arg(clientIP.toString());
        tcpSocket->write(array);
    }
}

void MyTcpServer::clientDisconnected()
{
    QTcpSocket* tcpSocket = static_cast<QTcpSocket*>(sender());
    QHostAddress clientIP(tcpSocket->peerAddress().toIPv4Address());
    qDebug().noquote() <<"> "  + clientIP.toString() + " disconnected";
    tcpSocket->close();
    _tcpClients.removeAt(_tcpClients.indexOf(tcpSocket));
}

void MyTcpServer::broadcast(const QByteArray& packet)
{
    if (0 == _tcpClients.size())
    {
        return;
    }

    foreach (QTcpSocket * socket, _tcpClients)
    {
        socket->write(packet);
    }
}





