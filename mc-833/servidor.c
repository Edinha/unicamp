#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

#define CHILD_PROCESS 0
#define MAXLINE 4096
#define EXIT_CMD "exit"
#define LISTENQ 10
#define MAXDATASIZE 100

void print_new_connect_client_socket_info(struct sockaddr_storage addr) {
    char ipstr[MAXLINE + 1], time_buffer[MAXLINE + 1];
    struct sockaddr_in *s = (struct sockaddr_in *) &addr;
    inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
    
    time_t ticks = time(NULL);
    snprintf(time_buffer, sizeof(time_buffer), "%.24s", ctime(&ticks));

    printf("\n\n=================== NEW CLIENT CONNECTION =================== \n");
    printf("Client Address (IP: %s, Port: %d) \n", ipstr, s->sin_port);
    printf("Connection time: %s \n", time_buffer);
    printf("============================================================= \n");
}

int main(int argc, char **argv) {

    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char recvline[MAXLINE + 1];
    char error[MAXLINE + 1];
    pid_t procPid;
    struct sockaddr_storage client_addr;

    if (argc != 2) { // Se IP do server não fornecido
        strcpy(error, "uso: ");
        strcat(error, argv[0]);
        strcat(error, " <port>");
        perror(error);
        exit(1); //encerre
    }

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
    servaddr.sin_port = htons(atoi(argv[1]));

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

    /*loop para aceitar a conexão dos filhos*/
    for (;;) {
        /*forka ao aceitar uma conexao, se o PID nao for o do pai, da break*/
        int len = sizeof client_addr;
        if ((connfd = accept(listenfd, (struct sockaddr *)&client_addr, (socklen_t *)&len)) == -1) {
            perror("accept");
            exit(1);
        }

        procPid = fork();
        if (procPid == CHILD_PROCESS)
            break;
    }

    print_new_connect_client_socket_info(client_addr);

    // filhos
    for (;;) {

        //so faz essa comunicação no filho (daqui para baixo)
        //printa as informações que chegaram do filho
        int n;
        if ((n = read(connfd, recvline, MAXLINE)) > 0) {
            //coloca um final para a string
            recvline[n] = 0;
            //escreve no saída padrão a mensagem recebida
            if (fputs(recvline, stdout) == EOF) {
                perror("fputs error");
                exit(1);
            }

            write(connfd, recvline, strlen(recvline));
            /*fecha a conexão com o cliente*/
            if (strcmp(recvline, EXIT_CMD) == 0) {
                close(connfd);
                exit(0);
            }
        }

        if (n < 0) {
            perror("read error");
            exit(1);
        }
    }

    return (0);
}
