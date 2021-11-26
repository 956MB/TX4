#ifndef TX4_WORKER_H
#define TX4_WORKER_H

#include <QThread>
#include <QTimer>
#include <qdebug.h>

//class tx4_worker : public QThread {
//    Q_OBJECT
//
//    public:
//        tx4_worker(const unsigned long &duration) : m_duration(duration), running(false) {}
//        ~tx4_worker(){}
//
//        void startWorker() {
//            running = true;
//        }
//        void stopWorker() {
//            running = false;
//        }
//
//    protected:
//        virtual void run() {
//            while (1) {
//                if (!running) { qDebug() << "return::here"; return; }
//
//                emit oneLoop();
//                msleep(m_duration);
//            }
//        }
//
//    signals:
//        void oneLoop();
//
//    private:
//        bool running;
//        unsigned long m_duration;
//};




//class worker : public QObject {
//	Q_OBJECT
//
//	public:
//		explicit worker(QObject *parent = 0);
//
//	signals:
//		void SignalToObj_mainThreadGUI();
//		void _running();
//		void _stopped();
//
//	public:
//		void StopWork();
//		void StartWork();
//
//	private slots:
//		void do_Work();
//
//	private:
//		bool running , stopped;
//
//};





//class worker : public QObject {
//    Q_OBJECT
//
//    public:
//        bool running;
//
//    public slots:
//        void loop() {
//            emit oneLoop();
//            QTimer::singleShot(500, this, SLOT(loop()));
//        }
//
//    signals:
//        void oneLoop();
//
//};
//
//class tx4_worker : public QObject {
//    Q_OBJECT
//    QThread workerThread;
//
//    public:
//        tx4_worker() {
//            worker *_worker = new worker(false);
//            _worker->moveToThread(&workerThread);
//            connect(&workerThread, &QThread::finished, _worker, &QObject::deleteLater);
//            connect(this, &tx4_worker::operate, _worker, &worker::loop);
//            //connect(_worker, &worker::oneLoop, this, &tx4_worker::handleResults);
//            connect(_worker, &worker::oneLoop, this, [=]{ emit waitDone(); });
//            workerThread.start();
//        }
//        ~tx4_worker() {
//            workerThread.quit();
//            workerThread.wait();
//        }
//
//        //void startWorker() {
//        //    workerThread.start();
//        //}
//        //void stopWorker() {
//        //    workerThread.quit();
//        //    workerThread.wait();
//        //}
//
//    public slots:
//        void startWorker() {
//        
//        }
//        void stopWorker() {
//        
//        }
//
//    signals:
//        void operate();
//        void waitDone();
//};

#endif // TX4_WORKER_H