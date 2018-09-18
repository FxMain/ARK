#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

#include "serverthread.h"
#include "outbound.h"

class outbound;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    ~Server();

public:
    QList<int> socketList;

private:
    void incomingConnection(int socketDescriptor);

private slots:

private:
    outbound *dialog;

};

#endif // SERVER_H
