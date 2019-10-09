#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAXLINE 4096
#define LISTENQ 10
#define MAXDATASIZE 100
#define CLOSE_CON "closecon"

int main(int argc, char **argv) {
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buf[MAXDATASIZE];


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
    servaddr.sin_port = htons(22123);


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
            exit(1);
        }

        //printa as informações de data e hora
//      ticks = time(NULL);
//      snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));

        while (read(connfd, recvline, MAXLINE) > 0) {
            bzero(buf, strlen(buf));
            strcpy(buf, recvline);
            write(connfd, buf, strlen(buf));
            if (strcmp(CLOSE_CON, recvline) == 0) {
                break;
            }
        }


        //inicializa a estrutura que será usada para obter informações da conexão
//      bzero(&socket_info, sizeof(socket_info));
//      int len = sizeof(socket_info);
//      //recupera as informações do socket do cliente na conexão
//      if (getpeername(connfd, (struct sockaddr *) &socket_info, (socklen_t *) &len) < 0) {
//         perror("getsockname error");
//         exit(1);
//      }

        //imprime as informações do socket do cliente
//      printf("\nClient Socket Family %u", socket_info.sin_family);
//      printf("\nClient Socket Port %u", socket_info.sin_port);
//      printf("\nClient Socket Address %s\n", inet_ntoa(socket_info.sin_addr));

        close(connfd);
        break;
    }
    return (0);
}
