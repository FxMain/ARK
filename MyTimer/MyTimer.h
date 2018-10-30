#ifndef _MYTIMER_H
#define _MYTIMER_H
#include <QObject>
 
class MyTimer : public QObject
{
	Q_OBJECT
 
public:
	MyTimer(QObject* parent = NULL);
	~MyTimer();
	void  handleTimeout();  //超时处理函数
	virtual void timerEvent( QTimerEvent *event);
private:
	int m_nTimerID;
};
 
#endif //_MYTIMER_H
