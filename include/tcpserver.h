#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>


class MyTcpServer : public QObject
{
    Q_OBJECT

public:
    explicit MyTcpServer(quint16 serverPort, QObject *parent = nullptr);
    virtual ~MyTcpServer();

    void broadcast(const QByteArray& packet);

public slots:
    void newConnection();
    void serverRead();
    void clientDisconnected();

private:
    QTcpServer*         _tcpServer = nullptr;
    QList<QTcpSocket*>  _tcpClients; // получатели данных
};

#endif // TCPSERVER_H
