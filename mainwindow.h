#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

#define TASKONE   1
#define TASKTWO   2

class WorkTask : public QObject
{
    Q_OBJECT

public:
    WorkTask();
    ~WorkTask(){}
private:
    void work(int order);

signals:
    void taskFinished();

public slots:
    void doSomeWork(int order);
};

class WaitInfoDlg : public QDialog
{
    Q_OBJECT

public:
    WaitInfoDlg(QWidget *parent = 0);
    ~WaitInfoDlg();
    void transferTaskOrder(int order);

signals:
    void downTaskOrder(int id);

private:
    WorkTask *m_taskCore;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    WorkTask    *m_taskCore;
    WaitInfoDlg *m_waitDlg;

public slots:
    void runApp();
    void operApp();
};

#endif // MAINWINDOW_H
