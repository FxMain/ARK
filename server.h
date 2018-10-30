#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

#include "serverthread.h"
#include "outbound.h"
#include "newdoc.h"
class outbound;
class newdoc;
class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    ~Server();

public:
    QList<int> socketList;
    QList<QString> socketLists;

private:
    void incomingConnection(int socketDescriptor);

private slots:

private:
    outbound *dialog;
    newdoc   *dialognewdoc;

};

#endif // SERVER_H
