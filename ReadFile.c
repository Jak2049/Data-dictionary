#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100

typedef struct Nodo
{
	char nom[50];
	struct Nodo *sig;
}TNodo;


void leeDatos(FILE *arch, TNodo **lista);
TNodo *CreaNodo(char *d);
void insertaNodo(TNodo **lista, char *d);
void imprime(TNodo *lista);
void libera(TNodo **lista);

int main () 
{
	FILE *arch;
	TNodo *lista = NULL;
    char nom[N];

    printf("Nombre del archivo: ");
    scanf("%s",nom);
	
	if((arch = fopen(nom,"r")) == NULL)
	{
		printf("Archivo no encontrado\n");
		exit(0);
	}
	printf("Datos que contiene el archivo: \n");
	leeDatos(arch, &lista);
	imprime(lista);
	libera(&lista);
	fclose(arch);
}

void leeDatos(FILE *arch, TNodo **lista)
{
	char nom[N];
	
    while(fgets(nom,N,arch))
	{
        nom[strcspn(nom, "\n")] = '\0';  
		insertaNodo(lista,nom);
	}
}

void insertaNodo(TNodo **lista, char d[N])
{
	TNodo *nodo=CreaNodo(d);
    TNodo *aux = *lista;  
	if(!(*lista))
		*lista = nodo;
	else
	{
		while(aux->sig)
        aux = aux->sig;
        aux->sig = nodo;
	}
}

TNodo *CreaNodo(char *d)
{
	TNodo *nodo=(TNodo *)malloc(sizeof(TNodo));
	
	if(nodo)
	{
		nodo->nom[0]='\0';
		strcpy(nodo->nom,d);
		nodo->sig = NULL;
		return nodo;
	}
	printf("Error: no se generó el nodo\n");
	exit(0);	
}

void imprime(TNodo *lista)
{
	TNodo *cab = lista;
	while(cab)
	{
		printf("%s\n",cab->nom);
		cab = cab->sig;
	}
}

void libera(TNodo **lista)
{
	TNodo *cab = *lista;
		TNodo *temp;
	while(cab)
	{
		temp = cab;
		cab = cab->sig;
		free(temp);
	}
	*lista = NULL; 
}
