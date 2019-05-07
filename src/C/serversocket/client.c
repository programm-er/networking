#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
//Cliente de ECO
int main(int argc,char * argv[]){
  //declaraciones de variables
  int sCliente;
  struct sockaddr_in direccionServidor;
  socklen_t tamDireccion;
  int valorRetorno = 0;
  const int TAM_DATOS = 64;
  char datos[TAM_DATOS]; //guardar datos de peticion
  char respuesta[TAM_DATOS]; //guardar respuesta del servidor

  //creación del socket Cliente
  sCliente = socket(AF_INET, SOCK_STREAM, 0);

  //tam en bytes de la estructura de datos struct sockaddr_in
  tamDireccion = sizeof(direccionServidor);
  //Limpiar las estructuras y arrays
  memset(&direccionServidor, 0, tamDireccion);
  memset(datos, 0, sizeof(datos));
  memset(respuesta, 0, sizeof(respuesta));
  direccionServidor.sin_family = AF_INET;
  direccionServidor.sin_port = htons(9000);

  valorRetorno=inet_pton(AF_INET, "127.0.0.1", &direccionServidor.sin_addr);
  if(valorRetorno<=0){
    printf("Error en la direccion");
    return -1;
  }
  //verificar que se pudo crear el socket
  //conectarse al servidor
  valorRetorno=connect(sCliente, (struct sockaddr *)&direccionServidor, tamDireccion);
  if(valorRetorno<0){
    printf("Error al conectarse al servidor");
    return -1;
  }
  //si la conexión es exitosa, entonces
    printf("> ");
    fgets(datos, TAM_DATOS, stdin);
    //Enviar solicitud al servidor
    write(sCliente, datos, TAM_DATOS);

    //Leer respuesta del servidor|
    read(sCliente, respuesta, TAM_DATOS);
    printf("Respuesta del servidor > %s\n", respuesta);

  //Cerrar conexión
  close(sCliente);
}
