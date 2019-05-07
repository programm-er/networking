#include<stdio.h>
#include<string.h>
typedef struct Persona{
  char nombres[20];
  char apellidos[30];
  int edad;
}tPersona;

int main(){

  tPersona p;
  p.edad = 30;

  printf("Antes de memset\n");
  printf("Nombres: %s\n", p.nombres);
  printf("Apellidos: %s\n", p.apellidos);
  printf("Edad: %d\n", p.edad);

  memset(&p, 0, sizeof(p));

  printf("Despues de memset\n");
  printf("Nombres: %s\n", p.nombres);
  printf("Apellidos: %s\n", p.apellidos);
  printf("Edad: %d", p.edad);
}
