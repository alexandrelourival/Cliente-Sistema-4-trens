#ifndef CLIENTE4TRENS_H
#define CLIENTE4TRENS_H

#include <QMainWindow>
#include <QMessageBox>
#include <QThread>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


QT_BEGIN_NAMESPACE
namespace Ui { class cliente4trens; }
QT_END_NAMESPACE

class cliente4trens : public QMainWindow
{
    Q_OBJECT

public:
    cliente4trens(QWidget *parent = nullptr);
    ~cliente4trens();

private slots:
    void on_actionStart_triggered();

    void on_actionQuit_triggered();

private:
    Ui::cliente4trens *ui;

    int res;

    pthread_t thread_painel, thread_cliente;

    void *thread_result;
};
#endif // CLIENTE4TRENS_H
