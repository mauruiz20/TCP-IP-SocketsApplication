#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <pthread.h>

void *conexion(void *data)
{
    int *direccion = (char *)data;

    //printf("%s\n", direccion);

    int Descriptor = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servidor;
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(80);
    servidor.sin_addr.s_addr = inet_addr(direccion);
    bzero(&(servidor.sin_zero), 8);

    if (connect(Descriptor, (struct sockaddr *)&servidor, sizeof(servidor)) < 0)
    {
        printf("No se encontro Servidor en IP: %s\n", direccion);
    }
    else
    {
        printf("Servidor encontrado IP: %s\n", direccion);
        close();
    }
}
char copiar(char direccion);
char enteroACaracter(int numero);

int main()
{
    int Descriptor;
    int tama_sin;

    char direccion[15];
    printf("Ingrese su direccion de red: ");
    scanf("%s", direccion);
    system("clear");

    int flag = 0;
    int posicionHostID;

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

    printf("Dirección de Red %s\n", direccion);
    printf("Buscando servidores...\n");

    /* ==================== DEMO 1 ==================== */

    // for (int i = 1; i < 10; i++)
    // {

    //     if (i < 10)
    //     {
    //         char c = enteroACaracter(i);
    //         direccion[posicionHostID] = c;
    //     }
    //     else if (i < 100)
    //     {
    //         char c1 = enteroACaracter(i / 10);
    //         char c2 = enteroACaracter(i % 10);
    //         direccion[posicionHostID] = c1;
    //         direccion[posicionHostID + 1] = c2;
    //         direccion[posicionHostID + 2] = '\0';
    //     }
    //     else
    //     {
    //         char c1 = enteroACaracter(i / 100);
    //         char c2 = enteroACaracter(i / 10 % 10);
    //         char c3 = enteroACaracter(i % 10);
    //         direccion[posicionHostID] = c1;
    //         direccion[posicionHostID + 1] = c2;
    //         direccion[posicionHostID + 2] = c3;
    //         direccion[posicionHostID + 3] = '\0';
    //     }

    //     pthread_t proceso;
    //     pthread_create(&proceso, NULL, &conexion, direccion);
    //     pthread_join(proceso, NULL);
    // }

    /* ==================== DEMO 2 ==================== */

    // pthread_t proceso1;
    // pthread_t proceso2;
    // pthread_t proceso3;
    // pthread_t proceso4;
    // pthread_t proceso5;
    // pthread_t proceso6;
    // pthread_t proceso7;
    // pthread_t proceso8;
    // pthread_t proceso9;
    // pthread_t proceso10;

    // pthread_create(&proceso1, NULL, &conexion, "10.1.0.1");
    // pthread_create(&proceso2, NULL, &conexion, "10.1.0.2");
    // pthread_create(&proceso3, NULL, &conexion, "10.1.0.3");
    // pthread_create(&proceso4, NULL, &conexion, "10.1.0.4");
    // pthread_create(&proceso5, NULL, &conexion, "10.1.0.5");
    // pthread_create(&proceso6, NULL, &conexion, "10.1.0.6");
    // pthread_create(&proceso7, NULL, &conexion, "10.1.0.7");
    // pthread_create(&proceso8, NULL, &conexion, "10.1.0.8");
    // pthread_create(&proceso9, NULL, &conexion, "10.1.0.9");
    // pthread_create(&proceso10, NULL, &conexion, "10.1.0.10");

    // pthread_join(proceso1, NULL);
    // pthread_join(proceso2, NULL);
    // pthread_join(proceso3, NULL);
    // pthread_join(proceso4, NULL);
    // pthread_join(proceso5, NULL);
    // pthread_join(proceso6, NULL);
    // pthread_join(proceso7, NULL);
    // pthread_join(proceso8, NULL);
    // pthread_join(proceso9, NULL);
    // pthread_join(proceso10, NULL);

    /* ==================== DEMO 3 ==================== */

    pthread_t hilos [255];

    for (int i = 0; i < 255; i++) {
        pthread_t proceso;
        hilos[i] = proceso;       
    }

    for (int i = 0; i < 255; i++) {
        if (i < 10)
        {
            char c = enteroACaracter(i);
            direccion[posicionHostID] = c;
        }
        else if (i < 100)
        {
            char c1 = enteroACaracter(i / 10);
            char c2 = enteroACaracter(i % 10);
            direccion[posicionHostID] = c1;
            direccion[posicionHostID + 1] = c2;
            direccion[posicionHostID + 2] = '\0';
        }
        else
        {
            char c1 = enteroACaracter(i / 100);
            char c2 = enteroACaracter(i / 10 % 10);
            char c3 = enteroACaracter(i % 10);
            direccion[posicionHostID] = c1;
            direccion[posicionHostID + 1] = c2;
            direccion[posicionHostID + 2] = c3;
            direccion[posicionHostID + 3] = '\0';
        }
        //printf("%s\n", direccion);        

        pthread_create(&hilos[i], NULL, &conexion, direccion);
    }
    

    for (int i = 0; i < 255; i++) {
        pthread_t p = hilos[i];
        pthread_join(p, NULL);     
    }

    return 0;
}

char enteroACaracter(int numero)
{
    return numero + '0';
}

char copiar(char direccion) {
    char aux [15];
    strcpy(aux, direccion);

    return aux;
}