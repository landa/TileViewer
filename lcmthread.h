#ifndef LCMTHREAD_H
#define LCMTHREAD_H

#include <QThread>
#include <lcm/lcm-cpp.hpp>

class LCMThread : public QThread
{
  Q_OBJECT
public:
	explicit LCMThread(QObject *parent = 0);
	void run();
	void setLCM(lcm::LCM* lcmInstance);

  lcm::LCM* lcm;
  
signals:
  
public slots:
  
};

#endif // LCMTHREAD_H
