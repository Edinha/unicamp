#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAXLINE 65535
#define LISTENQ 10
#define MAXDATASIZE 100
#define CLOSE_CON "closecon\0"

int main(int argc, char **argv) {
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char recvline[MAXLINE + 1];

    //cria o socket TCP associado ao servidor
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    //inicializa com zero os campos da struct associada ao socket do servidor.
    bzero(&servaddr, sizeof(servaddr));
    //Comunicação IPV4
    servaddr.sin_family = AF_INET;
    //Receber a conexão de clientes rodandno em qualquer porta
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //seta a porta associada ao processo do servidor
    servaddr.sin_port = htons(22125);

    //associa a conexão às respectivas portas e IPs descritos na estrutura
    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    //verifica se o socket não está ouvindo
    if (listen(listenfd, LISTENQ) == -1) {
        perror("listen");
        exit(1);
    }

    for (;;) {
        /*erro ao obter os dados e retirar da fila a conexão concluída*/
        if ((connfd = accept(listenfd, (struct sockaddr *) NULL, NULL)) == -1) {
            perror("accept");
            // close(connfd);
            close(listenfd);
            exit(1);
        }

        // Leitura das mensagens do cliente
        while (1) {
            bzero(recvline, strlen(recvline));
            int n = read(connfd, recvline, MAXLINE);
            if (n == 0) {
                break;
            }
            write(connfd, recvline, strlen(recvline));
        }

        // Fecha a conexão com cliente
        close(connfd);
        break;
    }

    close(listenfd);
    return (0);
}
