#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define MAXLINE 4096
#define CLOSE_CON "closecon\0"

int max(int a, int b) {
    if (a > b) {
        return a;
    }

    return b;
}

int main(int argc, char **argv) {
    typedef enum {
        false, true
    } bool;

    int sockfd, maxsd;
    char recvline[MAXLINE + 1];
    char error[MAXLINE + 1];
    char input_line[MAXLINE + 1];
    struct sockaddr_in servaddr;


    fd_set readfds;

    if (argc != 2) { // Se IP do server não fornecido
        strcpy(error, "uso: ");
        strcat(error, argv[0]);
        strcat(error, " <IPaddress>");
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
    servaddr.sin_port = htons(22125);
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

    bzero(input_line, sizeof(input_line));
    bool end_read = false;
    FD_ZERO(&readfds);

    while (1) {
        FD_SET(fileno(stdin), &readfds);
        FD_SET(sockfd, &readfds);
        maxsd = max(fileno(stdin), sockfd) + 1;
        select(maxsd, &readfds, NULL, NULL, NULL);

        if (FD_ISSET(sockfd, &readfds)) {
            read(sockfd, recvline, MAXLINE);
            if (strcmp(recvline, CLOSE_CON) == 0) {
                if (!end_read) {
                    perror("server terminated suddenly");
                } else {
                    break;
                }
            } else {
                fputs(recvline, stdout);
                fputs("\n", stdout);
            }

            bzero(recvline, strlen(recvline));
        }
        
        if (FD_ISSET(fileno(stdin), &readfds) && !end_read) {
            bzero(input_line, strlen(input_line));
            if (fgets(input_line, MAXLINE, stdin) == NULL) {
                end_read = true;
                bzero(input_line, strlen(input_line));
                strcpy(input_line, CLOSE_CON);
            }

            write(sockfd, input_line, strlen(input_line));
        }
    }

    close(sockfd);
    exit(0);
}
