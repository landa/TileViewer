#include "lcmthread.h"

LCMThread::LCMThread(QObject *parent) :
  QThread(parent)
{
}

void LCMThread::setLCM(lcm::LCM* lcmInstance) {
  lcm = lcmInstance;
}

void LCMThread::run() {
  while(0 == lcm->handle());
}
