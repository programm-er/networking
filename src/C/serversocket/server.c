#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//Servidor de ECO
//smolina@ct.unanleon.edu.ni
//Asunto: Programacion SD / Cliente

int main(int argc, char *argv[]){
  //declaracion de variables
  int servidor, cliente; //descriptores de archivos
  struct sockaddr_in direccionServidor, direccionCliente;
  char *ipCliente;
  socklen_t tamDireccion;
  ssize_t bytesleidos, bytesescritos;
  const int TAM_DATOS = 64;
  char datos[TAM_DATOS]; //guardar datos
  int fdlog;
  char *log = "Cliente conectado: ";

  tamDireccion = sizeof(direccionServidor);
  bytesleidos = bytesescritos = 0;
  memset(&direccionServidor, 0, tamDireccion);
  memset(datos, 0, sizeof(char)*TAM_DATOS);

  direccionServidor.sin_family = AF_INET;
  direccionServidor.sin_addr.s_addr = htonl(INADDR_ANY);
  direccionServidor.sin_port = htons(9000);
  //create socket
  servidor = socket(AF_INET, SOCK_STREAM, 0);
  if(servidor < 0) {
    //error
    return -1;
  }
  //bind
  bind(servidor, (struct sockaddr *) &direccionServidor, tamDireccion);
  //listen
  listen(servidor, 5);
  //accept -- finito | infinito
  printf("Listening for clients...\n");
  fdlog = open("server.log", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
  while(1){
    cliente = accept(servidor, (struct sockaddr *)&direccionCliente, &tamDireccion);
    ipCliente = inet_ntoa(direccionCliente.sin_addr);
    if(ipCliente!=NULL && fdlog>0){
      ///memset(log, 0, sizeof(log)*TAM_DATOS);
      //sprintf(log, "Cliente conectado: %s", ipCliente);
      write(fdlog, log, strlen(log));
      write(fdlog, ipCliente, strlen(ipCliente));
      write(fdlog, "\n", 1);
    }

    //recibir datos del cliente
    bytesleidos = read(cliente, datos, TAM_DATOS);
    //enviar datos en respuesta al cliente
    //echo de enviado por cliente
    write(cliente, datos, bytesleidos);
    //close client connection
    close(cliente);
  }
  //close server
  close(fdlog);
  close(servidor);
}
