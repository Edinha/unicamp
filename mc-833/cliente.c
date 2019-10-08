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

int main(int argc, char **argv) {
   int    sockfd, n;
   char   recvline[MAXLINE + 1];
   char   error[MAXLINE + 1];
   char  input_line[MAXLINE +1];
   struct sockaddr_in servaddr;
   struct sockaddr_in socket_info;

   if (argc != 2) { // Se IP do server não fornecido
      strcpy(error,"uso: ");
      strcat(error,argv[0]);
      strcat(error," <IPaddress>");
      perror(error);
      exit(1); //encerre
   }

  //cria o socket TCP do cliente associado a conexão
   if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      perror("socket error");
      exit(1);
   }


  //inicializa com 0 a struct que representa o socket servidor.
   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port   = htons(22122);
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

   bzero(input_line, sizeof(inputline));
   while(1){
     int args_read = scanf("%[^\n]",input_line);
     if(args_read == EOF){
       break;
     }
     write(sockfd, input_line, strlen(inputline));
     for(;;){

     }
   }



   //enquanto há mensagens enviadas do servidor
   while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
      //coloca um final para a string
      recvline[n] = 0;
      //escreve no saída padrão a mensagem recebida
      if (fputs(recvline, stdout) == EOF) {
         perror("fputs error");
         exit(1);
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

   // //printa as informações do socket do cliente obtidas
   // printf("\nSocket Family %u", socket_info.sin_family);
   // printf("\nSocket Port %u", socket_info.sin_port);
   // printf("\nSocket Address %s\n", inet_ntoa(socket_info.sin_addr));

   if (n < 0) {
      perror("read error");
      exit(1);
   }

   exit(0);
}
