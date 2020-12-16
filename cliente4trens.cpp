#include "cliente4trens.h"
#include "ui_cliente4trens.h"

void* thread_functionPainel(void*);
void* thread_functionCliente(void*);

int vetor_int[4];

Ui::cliente4trens ui_aux;

cliente4trens::cliente4trens(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cliente4trens)
{
    ui->setupUi(this);

    ui_aux = *ui;

    vetor_int[0] = vetor_int[1] = vetor_int[2] = vetor_int[3] = 5;

    ui->centralwidget->setVisible(false);

}

cliente4trens::~cliente4trens()
{
    delete ui;
}


void cliente4trens::on_actionStart_triggered()
{
    ui->centralwidget->setVisible(true);

    res = pthread_create(&thread_cliente, NULL, thread_functionCliente, NULL);
    if (res != 0){
        QMessageBox::warning(this,"ERRO", "Criação da Thread Painel falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&thread_painel, NULL, thread_functionPainel, NULL);
    if (res != 0){
        QMessageBox::warning(this,"ERRO", "Criação da Thread Interface falhou.");
        exit(EXIT_FAILURE);
    }
}

void cliente4trens::on_actionQuit_triggered()
{
    res = pthread_join(thread_painel, &thread_result);
    if (res != 0) {
        QMessageBox::warning(this,"ERRO", "Junção da Thread Trem 1 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_join(thread_cliente, &thread_result);
    if (res != 0) {
        QMessageBox::warning(this,"ERRO", "Junção da Thread Trem 2 falhou.");
        exit(EXIT_FAILURE);
    }

    QApplication::quit();
}

void* thread_functionPainel(void*)
{
    while(1)
    {
            vetor_int[0] = 6 - ui_aux.verticalSlider_trem1->value(); // Pega a velocidade do trem 1 e transforma em segundos
            ui_aux.lcdNumber_trem1->display(ui_aux.verticalSlider_trem1->value()); // Mostra a velocidade do trem 1 no lcd

            vetor_int[1] = 6 - ui_aux.verticalSlider_trem2->value(); // Pega a velocidade do trem 2 e transforma em segundos
            ui_aux.lcdNumber_trem2->display(ui_aux.verticalSlider_trem2->value()); // Mostra a velocidade do trem 2 no lcd

            vetor_int[2] = 6 - ui_aux.verticalSlider_trem3->value(); // Pega a velocidade do trem 3 e transforma em segundos
            ui_aux.lcdNumber_trem3->display(ui_aux.verticalSlider_trem3->value()); // Mostra a velocidade do trem 3 no lcd

            vetor_int[3] = 6 - ui_aux.verticalSlider_trem4->value(); // Pega a velocidade do trem 4 e transforma em segundos
            ui_aux.lcdNumber_trem4->display(ui_aux.verticalSlider_trem4->value()); // Mostra a velocidade do trem 4 no lcd

            usleep(100000); // A thread_painel dorme por 0,1 segundo
     }
}

void* thread_functionCliente(void*)
{
    int sockfd;
        int len;
        socklen_t len_recv;
        struct sockaddr_in address;

        unsigned short porta = 9734;

        sockfd  = socket(AF_INET, SOCK_DGRAM,0);  // criacao do socket

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr("127.0.0.1");
        address.sin_port = htons(porta);

        len = sizeof(address);
        len_recv = sizeof(address);

        while(1)
        {
            sendto(sockfd,  vetor_int,sizeof(vetor_int),0,(struct sockaddr *) &address, len);
        }

        close(sockfd);
        exit(0);
}
