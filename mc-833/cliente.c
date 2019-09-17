#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLINE 4096
#define MAX_COMMAND_SIZE 1000
#define EXIT_CMD "exit"
#define MAX_COMMAND_OUT 1000

//cria o socket TCP do cliente associado a conexão
int Socket(int family, int type, int flags) {
    int sockfd;
    if ((sockfd = socket(family, type, flags)) < 0) {
        perror("client socket");
        exit(1);
    } else {
        return sockfd;
    }
}

//inicializa a estrutura que representa as informações do socket
void init_socket_addr(struct sockaddr_in *addr, int port) {
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
}

//monta o descritor da conexão
void build_connection_descriptor(int family, char *ip, struct sockaddr_in *addr) {
    if (inet_pton(family, ip, &addr->sin_addr) <= 0) {
        perror("inet_pton error");
        exit(1);
    }
}

//performa a conexão
void perform_connection(int sockfd, struct sockaddr_in *serveraddr) {
    if (connect(sockfd, (struct sockaddr *) serveraddr, sizeof(*serveraddr)) < 0) {
        perror("connect error");
        exit(1);
    }
}

//lê a mensagem do servidor
int read_server_msg(int sockfd, char *buffer, int buffer_size) {
    return (read(sockfd, buffer, MAXLINE));
}

//retorna a informação do socket local
void get_info_local_socket(int sockfd, struct sockaddr_in *socket_info, int len) {
    if (getsockname(sockfd, (struct sockaddr *) socket_info, (socklen_t *) &len) < 0) {
        perror("getsockname error");
        exit(1);
    }
}

void get_info_server_socket(int sockfd, struct sockaddr_in *socket_info, int len) {
    if (getpeername(sockfd, (struct sockaddr *) socket_info, (socklen_t *) &len) < 0) {
        perror("getsockname error");
        exit(1);
    }
}

int main(int argc, char **argv) {
    char command[MAX_COMMAND_SIZE];
    char command_output[MAX_COMMAND_OUT + 1];
    int sockfd, n;
    char recvline[MAXLINE + 1];
    char error[MAXLINE + 1];
    struct sockaddr_in servaddr;
    struct sockaddr_in socket_info;

    // Se IP ou porta do server não forem fornecidos
    if (argc != 3) {
        strcpy(error, "uso: ");
        strcat(error, argv[0]);
        strcat(error, " <IPaddress> <Port>");
        perror(error);
        exit(1); //encerre
    }

    //cria o socket TCP do cliente associado a conexão
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    //inicializa com 0 a struct que representa o socket servidor.
    bzero(&servaddr, sizeof(servaddr));
    init_socket_addr(&servaddr, atoi(argv[2]));

    //monta o descritor da conexão
    build_connection_descriptor(AF_INET, argv[1], &servaddr);

    //performa a conexão
    perform_connection(sockfd, &servaddr);

    //loop para comunicação com servidor
    for (;;) {
        //le o comando
        fgets(command, MAX_COMMAND_SIZE, stdin);
        int cmd_len = strlen(command);

        //elimina o \n do fim da linha de entrada
        if (cmd_len > 0 && command[cmd_len - 1] == '\n') {
            command[cmd_len - 1] = '\0';
        }

        //envia o comando para o servidor
        write(sockfd, command, strlen(command));

        //se há mensagens do servidor
        if ((n = read_server_msg(sockfd, recvline, MAXLINE)) > 0) {
            //coloca um final para a string
            recvline[n] = 0;
            //se é comando para encerrar a conexão
            if (strcmp(recvline, EXIT_CMD) == 0) {
                close(sockfd);
                exit(0);
            }
        }

        if ((n = read_server_msg(sockfd, command_output, MAX_COMMAND_OUT)) > 0) {
            //coloca um final para a string
            command_output[n] = 0;
        }

        //inicializa com 0 a struct que representa a informação do socket local
        bzero(&socket_info, sizeof(socket_info));
        // associa a len o tamanho da struct que descreve o socket
        int len = sizeof(socket_info);

        //recupera as informações do socket do cliente
        get_info_local_socket(sockfd, &socket_info, len);

        printf("\n\n=================== NEW SERVER RESPONSE =================== \n");
        printf("Client command sent: %s \n", command);
        printf("Client command received: %s \n", recvline);
        printf("Client socket (IP: %s, Port: %u) \n", inet_ntoa(socket_info.sin_addr), socket_info.sin_port);

        // Reinicia socket info para usar mesma referência para informações do server
        bzero(&socket_info, len);
        //recupera as informações do socket do servidor
        get_info_server_socket(sockfd, &socket_info, len);

        printf("Server socket (IP: %s, Port: %u) \n", inet_ntoa(socket_info.sin_addr), socket_info.sin_port);
        printf("%s", command_output);
        printf("=========================================================== \n");


        if (n < 0) {
            perror("read error");
            exit(1);
        }
    }


}
