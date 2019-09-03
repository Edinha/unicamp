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

#define LISTENQ 10
#define MAXDATASIZE 100

int main (int argc, char **argv) {
   int    listenfd, connfd;
   struct sockaddr_in servaddr;
   char   buf[MAXDATASIZE];
   time_t ticks;
   struct sockaddr_in socket_info;

   //cria o socket TCP associado ao servidor
   if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      perror("socket");
      exit(1);
   }

   //inicializa com zero os campos da struct associada ao socket do servidor.
   bzero(&servaddr, sizeof(servaddr));
   //Comunicação IPV4
   servaddr.sin_family      = AF_INET;
   //Receber a conexão de clientes rodandno em qualquer porta
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   //seta a porta associada ao processo do servidor
   servaddr.sin_port        = htons(22122);


   //associa a conexão às respectivas portas e IPs descritos na estrutura
   if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
      perror("bind");
      exit(1);
   }

   //verifica se o socket não está ouvindo
   if (listen(listenfd, LISTENQ) == -1) {
      perror("listen");
      exit(1);
   }

   for ( ; ; ) {
     /**/
      if ((connfd = accept(listenfd, (struct sockaddr *) NULL, NULL)) == -1 ) {
         perror("accept");
         exit(1);
      }

      ticks = time(NULL);
      snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
      write(connfd, buf, strlen(buf));

      bzero(&socket_info, sizeof(socket_info));
      int len = sizeof(socket_info);
      if (getsockname(connfd, (struct sockaddr *) &socket_info, (socklen_t *) &len) < 0) {
         perror("getsockname error");
         exit(1);
      }

      printf("\nClient Socket Family %u", socket_info.sin_family);
      printf("\nClient Socket Port %u", socket_info.sin_port);
      printf("\nClient Socket Address %s\n", inet_ntoa(socket_info.sin_addr));

      close(connfd);
   }
   return(0);
}