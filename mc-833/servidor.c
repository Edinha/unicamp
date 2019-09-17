#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

#define LOG_FILE "connection_log.txt"
#define CHILD_PROCESS 0
#define MAXLINE 4096
#define EXIT_CMD "exit"
#define LISTENQ 10
#define READ_CMD_MODE "r"


//escreve no arquivo de log do servidor quando o cliente se conecta ou se desconecta
void write_client_state_to_file(struct sockaddr_storage addr, char *filename, time_t time, char *state_description) {
    char ipstr[MAXLINE + 1];
    FILE *connectionLog;
    struct sockaddr_in *s = (struct sockaddr_in *) &addr;
    inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
    if ((connectionLog = fopen(filename, "a+")) != NULL) {
        fprintf(connectionLog, "Client Address (IP: %s, Port: %d) %s TIME: %.24s \n", ipstr, s->sin_port,
                state_description, ctime(&time));
        fclose(connectionLog);
    }

}

//função auxiliar para printar quando o cliente se conecta, se desconecta ou envia um comando
void print_new_log(struct sockaddr_storage addr, char *type, char *command, time_t ticks) {
    char ipstr[MAXLINE + 1], time_buffer[MAXLINE + 1];
    struct sockaddr_in *s = (struct sockaddr_in *) &addr;
    inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);


    snprintf(time_buffer, sizeof(time_buffer), "%.24s", ctime(&ticks));

    printf("\n\n=================== NEW CLIENT %s =================== \n", type);
    printf("Client Address (IP: %s, Port: %d) \n", ipstr, s->sin_port);
    /*se estamos printando um comando*/
    if (strlen(command) > 0) {
        printf("Received command:  %s \n", command);
    }

    printf("%s time: %s \n", type, time_buffer);
    printf("============================================================= \n");
}

//começa a escutar por conexões
int start_listening(int family, int type) {
    int listenfd;
    if ((listenfd = socket(family, type, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    return listenfd;
}

//inicializa os campos do socket do servidor
void setup_server_socket(int family, char *port, struct sockaddr_in *serveraddr) {
    bzero(serveraddr, sizeof(*serveraddr));
    //Comunicação IPV4
    serveraddr->sin_family = AF_INET;
    //Receber a conexão de clientes rodandno em qualquer porta
    serveraddr->sin_addr.s_addr = htonl(INADDR_ANY);
    //seta a porta associada ao processo do servidor
    serveraddr->sin_port = htons(atoi(port));
}

//associa a conexão às respectivas portas e IPs descritos na estrutura
void bind_connection(int listenfd, struct sockaddr_in *serveraddr) {
    if (bind(listenfd, (struct sockaddr *) serveraddr, sizeof(*serveraddr)) == -1) {
        perror("bind");
        exit(1);
    }
}

int socket_isnt_listening(int listenfd) {
    return listen(listenfd, LISTENQ) == -1;
}

int accept_client_connection(int listenfd, struct sockaddr_storage *client_addr, int len) {
    int connfd;
    if ((connfd = accept(listenfd, (struct sockaddr *) client_addr, (socklen_t *) &len)) == -1) {
        perror("accept");
        exit(1);
    }

    return connfd;
}

int read_client_msg(int connfd, char *buffer, int buffer_size) {
    return read(connfd, buffer, buffer_size);
}

void execute_command(char *cmd_output, char *cmd_local_output, const char *command) {
    FILE *f = popen(command, READ_CMD_MODE);
    bzero(cmd_output, sizeof(MAXLINE));
    strcpy(cmd_output, "\ncommand return: \n");
    while (fgets(cmd_local_output, MAXLINE, f)) {
        strcat(cmd_output, cmd_local_output);
    }
}

int main(int argc, char **argv) {

    int listenfd, connfd;
    time_t connected, disconnected;
    struct sockaddr_in servaddr;
    char cmd_output[MAXLINE + 1];
    char cmd_local_output[MAXLINE + 1];
    char recvline[MAXLINE + 1];
    char error[MAXLINE + 1];
    pid_t procPid;
    struct sockaddr_storage client_addr;

    // Se porta do server não fornecida
    if (argc != 2) {
        strcpy(error, "uso: ");
        strcat(error, argv[0]);
        strcat(error, " <port>");
        perror(error);
        exit(1); //encerre
    }

    //cria uma escuta para novas conexões associadas ao servidor
    listenfd = start_listening(AF_INET, SOCK_STREAM);

    //inicializa os campos do socket do servidor
    setup_server_socket(AF_INET, argv[1], &servaddr);

    //associa a conexão às respectivas portas e IPs descritos na estrutura
    bind_connection(listenfd, &servaddr);

    //verifica se o socket não está ouvindo
    if (socket_isnt_listening(listenfd)) {
        perror("listen");
        exit(1);
    }

    /*loop para aceitar a conexão dos clientes */
    for (;;) {
        int len = sizeof client_addr;
        connfd = accept_client_connection(listenfd, &client_addr, len);
        /*forka ao aceitar uma conexao, se o PID nao for o do pai, da break*/
        procPid = fork();
        if (procPid == CHILD_PROCESS)
            break;
        else {
            // no pai a conexão pode ser fechada, pois ela será manipulada pelo filho
            close(connfd);
        }
    }

    connected = time(NULL);
    /*printa a nova conexão*/
    print_new_log(client_addr, "CONNECTION", "", connected);
    /*pescreve no log a nova conexão*/
    write_client_state_to_file(client_addr, LOG_FILE, connected, "CONNECTION");

    // processos filhos
    for (;;) {


        //printa as informações que chegaram do filho
        int n;
        if ((n = read_client_msg(connfd, recvline, MAXLINE)) > 0) {
            //coloca um final para a string
            recvline[n] = 0;
            //escreve na saída padrão o comando recebido
            print_new_log(client_addr, "COMMAND", recvline, time(NULL));
            //escreve para o cliente o comando recebido
            write(connfd, recvline, strlen(recvline));
            /*fecha a conexão com o cliente se o comando for o de exit*/
            if (strcmp(recvline, EXIT_CMD) == 0) {
                disconnected = time(NULL);
                /*printa na saída padrão o fim da conexão*/
                print_new_log(client_addr, "DISCONNECTION", "", disconnected);
                /*escreve no arquivo de log o fim da conexão*/
                write_client_state_to_file(client_addr, LOG_FILE, disconnected, "DISCONNECTION");
                close(connfd);
                exit(0);
            }


            /*executa o comando */
            execute_command(cmd_output, cmd_local_output, recvline);

            if (strlen(cmd_output) > 0) {
                write(connfd, cmd_output, strlen(cmd_output));
            }
        }

        if (n < 0) {
            perror("read error");
            exit(1);
        }
    }

}