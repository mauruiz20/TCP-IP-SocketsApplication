#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

char enteroACaracter(int numero);
int *conexion(void *arg);

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

    pthread_t threads[254];

    for (int i = 1; i < 255; i++)
    {

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
}

char enteroACaracter(int numero)
{
    return numero + '0';
}