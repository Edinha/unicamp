#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLINE 4096
#define MAX_COMMAND_SIZE 1000
#define EXIT_CMD "exit"

int main(int argc, char **argv) {
    char command[MAX_COMMAND_SIZE];
    int sockfd, n;
    char recvline[MAXLINE + 1];
    char error[MAXLINE + 1];
    struct sockaddr_in servaddr;
    struct sockaddr_in socket_info;

    if (argc != 3) { // Se IP e porta do server não fornecido
        strcpy(error, "uso: ");
        strcat(error, argv[0]);
        strcat(error, " <IPaddress> <Port>");
        perror(error);
        exit(1); //encerre
    }

    //cria o socket TCP do cliente associado a conexão

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }

    //inicializa com 0 a struct que representa o socket servidor.
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    //associa o IP do servidor à conexão
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        perror("inet_pton error");
        exit(1);
    }
    //performa a conexão
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("connect error");
        exit(1);
    }

    for (;;) {
        fgets(command, MAX_COMMAND_SIZE, stdin);
        int cmd_len = strlen(command);
        if (cmd_len > 0 && command[cmd_len - 1] == '\n') {
            command[cmd_len - 1] = '\0';
        }
        write(sockfd, command, strlen(command));

        //enquanto há mensagens enviadas do servidor
        if ((n = read(sockfd, recvline, MAXLINE)) > 0) {
            //coloca um final para a string
            recvline[n] = 0;
            if (strcmp(recvline, EXIT_CMD) == 0) {
                close(sockfd);
                exit(0);
            }
        }

        //inicializa com 0 a struct que representa a informação do socket local
        bzero(&socket_info, sizeof(socket_info));
        // associa a len o tamanho da struct que descreve o socket
        int len = sizeof(socket_info);
        //recupera as informações do socket do cliente
        if (getsockname(sockfd, (struct sockaddr *) &socket_info, (socklen_t *) &len) < 0) {
            perror("getsockname error");
            exit(1);
        }
        
        printf("\n\n=================== NEW SERVER RESPONSE =================== \n");
        printf("Client command sent: %s \n", command);
        printf("Client command received: %s \n", recvline);
        printf("Client socket (IP: %s, Port: %u) \n", inet_ntoa(socket_info.sin_addr), socket_info.sin_port);
        
        // Reinicia socket info para usar mesma referência para informações do server
        bzero(&socket_info, len);
        if (getpeername(sockfd, (struct sockaddr *) &socket_info, (socklen_t *) &len) < 0) {
            perror("getsockname error");
            exit(1);
        }

        printf("Server socket (IP: %s, Port: %u) \n", inet_ntoa(socket_info.sin_addr), socket_info.sin_port);
        printf("=========================================================== \n");

        if (n < 0) {
            perror("read error");
            exit(1);
        }
    }

    exit(0);
}
