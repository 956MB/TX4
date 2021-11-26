
//#include "tx4_worker.h"

//tx4_worker::tx4_worker (const unsigned long &duration, QObject *parent)
//    : QThread(parent)
//    , m_duration(duration) {
//    running = false;
//}
//
//tx4_worker::~tx4_worker() {}
//
//void tx4_worker::run() {
//    while (1) {
//        if (!running) { return; }
//
//        emit oneLoop();
//        msleep(m_duration);
//    }
//}
//
//void tx4_worker::startWorker() {
//    running = true;
//}
//void tx4_worker::stopWorker() {
//    running = false;
//}