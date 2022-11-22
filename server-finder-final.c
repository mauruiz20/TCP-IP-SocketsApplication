#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/* ================================ Funciones ================================ */

void *conexion(void *data);

char enteroACaracter(int numero);

/* ================================ Variables globales ================================ */

char direccion[15];

int posicionHostID;

/* ================================ Función Principal ================================ */

int main(void)
{
    printf("================================ BIENVENIDO ================================\n");
    printf("Ingrese su direccion de red: ");
    scanf("%s", direccion);
    system("clear");

    /* Se busca en la dirección introducida cuál es la posición donde empieza el Host ID */

    int flag = 0;

    for (int i = 0; i < sizeof(direccion); i++)
    {
        if (flag > 2)
        {
            posicionHostID = i;
            direccion[posicionHostID] = '\0';
            break;
        }

        if (direccion[i] == '.')
        {
            flag++;
        };
    }

    direccion[posicionHostID] = '0';
    direccion[posicionHostID + 1] = '\0';

    printf("================================ BIENVENIDO ================================\n");
    printf("Dirección de Red %s\n", direccion);
    printf("Buscando servidores...\n\n");

    /* Se crean 254 Hilos (1 por dirección (Clase C)) */

    pthread_t hilos[254];

    for (int i = 1; i <= 254; i++)
    {
        pthread_t p;
        hilos[i - 1] = p;
    }

    for (int i = 1; i <= 254; i++)
    {
        pthread_create(&hilos[i - 1], NULL, &conexion, (int *)i);
    }

    for (int i = 1; i <= 254; i++)
    {
        pthread_join(hilos[i - 1], NULL);
    }

    printf("\x1b[0m\n================================ FIN ================================\n");

    return 0;
}

/* ================================ Función conexión (Thread - Intenta conectarse a un servidor) ================================ */

void *conexion(void *data)
{
    int num = (int)data;

    /* Se copia la dirección de red base */

    char direccionNueva[15];
    strcpy(direccionNueva, direccion);

    /* Se traduce el entero y se concatena a la dirección base, así formando la dirección completa */

    if (num < 10)
    {
        char c = enteroACaracter(num);
        direccionNueva[posicionHostID] = c;
    }
    else if (num < 100)
    {
        char c1 = enteroACaracter(num / 10);
        char c2 = enteroACaracter(num % 10);
        direccionNueva[posicionHostID] = c1;
        direccionNueva[posicionHostID + 1] = c2;
        direccionNueva[posicionHostID + 2] = '\0';
    }
    else
    {
        char c1 = enteroACaracter(num / 100);
        char c2 = enteroACaracter(num / 10 % 10);
        char c3 = enteroACaracter(num % 10);
        direccionNueva[posicionHostID] = c1;
        direccionNueva[posicionHostID + 1] = c2;
        direccionNueva[posicionHostID + 2] = c3;
        direccionNueva[posicionHostID + 3] = '\0';
    }

    /* Creación del socket */

    int sockfd;
    struct sockaddr_in servidor;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("CLIENTE: creación del socket fallida...\n");        
    }

    /* Asginación de IP, Puerto */

    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = inet_addr(direccionNueva);
    servidor.sin_port = htons(80);
    bzero(&(servidor.sin_zero), 8);

    /* Intento de conexión del socket cliente al socket servidor */

    if (connect(sockfd, (struct sockaddr *)&servidor, sizeof(servidor)) < 0)
    {
        printf("\t\x1b[31m No se encontro Servidor en IP: %s\n\x1b[0m", direccionNueva);
    }
    else
    {
        printf("\t\x1b[34m Servidor encontrado IP: %s\n\x1b[0m", direccionNueva);

        /* Cierre del socket */
        
        close(sockfd);
    }
}

/* ================================ Función que traduce un entero a un caracter ================================ */

char enteroACaracter(int numero)
{
    return numero + '0';
}