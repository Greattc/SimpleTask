#include "mainwindow.h"

WaitInfoDlg::WaitInfoDlg(QWidget *parent)
    :  QDialog(parent), m_taskCore(NULL)
{
    QLabel *gifLabel = new QLabel;
    QMovie *movie = new QMovie(":/images/loading.gif", QByteArray(), this);
    movie->setScaledSize(QSize(40, 40));
    gifLabel->setMovie(movie);
    movie->start();
    gifLabel->setFixedSize(QSize(60, 60));

    QLabel *infoLabel = new QLabel(tr("Processing..."));
    QFont font("Times New Roman", 12, QFont::Bold);
    infoLabel->setFont(font);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(gifLabel);
    layout->addWidget(infoLabel);
    layout->addStretch();
    setLayout(layout);
    resize(200, 80);
}

WaitInfoDlg::~WaitInfoDlg()
{

}

void WaitInfoDlg::transferTaskOrder(int order)
{
    if(m_taskCore)
        delete m_taskCore;

    m_taskCore = new WorkTask;
    connect(this, SIGNAL(downTaskOrder(int)), m_taskCore, SLOT(doSomeWork(int)));
    connect(m_taskCore, SIGNAL(taskFinished()), this, SLOT(close()));
    emit downTaskOrder(order);
    exec();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_waitDlg = new WaitInfoDlg;
    QToolBar *toolBar = addToolBar("File");

    QAction *runAct = new QAction(QString("Run"), this);
    connect(runAct, SIGNAL(triggered(bool)), this, SLOT(runApp()));

    QAction *operAct = new QAction(QString("Operate"), this);
    connect(operAct, SIGNAL(triggered(bool)), this, SLOT(operApp()));

    toolBar->addAction(runAct);
    toolBar->addAction(operAct);
    resize(560, 420);
}

MainWindow::~MainWindow()
{

}

void MainWindow::runApp()
{
    m_waitDlg->transferTaskOrder(TASKONE);
}

void MainWindow::operApp()
{
    m_waitDlg->transferTaskOrder(TASKTWO);
}

WorkTask::WorkTask()
{
    QThread *thread = new QThread;
    moveToThread(thread);
    thread->start();
}

void WorkTask::work(int order)
{
    for(int i = 0; i < order; ++i)
        qDebug() << i;
}

void WorkTask::doSomeWork(int order)
{
    switch(order)
    {
    case TASKONE:
        qDebug() << "Execute task one...";
        work(100000);
        break;
    case TASKTWO:
        qDebug() << "Execute task two...";
        work(200000);
        break;
    default:
        break;
    }

    emit taskFinished();
}
