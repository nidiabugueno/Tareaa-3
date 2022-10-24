#include "list.h"
#include "treemap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct {
  char nombre[100];
  char anio[100];
  int valoracion;
  int precio;
} Juegos;

//Prototipos
char *get_csv_field (char * , int);
void Importarjuegos (char * , TreeMap *, TreeMap *,TreeMap *, TreeMap * );
void agregarJuego(TreeMap * ,TreeMap * ,TreeMap * ,TreeMap *, Juegos *);
void MostrarPorPrecio(TreeMap *, int);
void MostrarPorValoracion(TreeMap *, int);
void MostrarJuegoDelAnio(TreeMap *, char *);
void Exportar(TreeMap *MapNombre);




int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

int lower_than_int(void * key1, void * key2) {
    return key1<key2;
}

int main() 
{
  
  TreeMap* MapNombre = createTreeMap(lower_than_string);
  TreeMap* MapAnio = createTreeMap(lower_than_string);
  TreeMap* MapValoracion = createTreeMap(lower_than_int);
  TreeMap* MapPrecio = createTreeMap(lower_than_int);

  Juegos * tmpJuego = (Juegos *)malloc(sizeof(Juegos));

  char nombre[100];
  char anio[100];
  int valoracion;
  int precio;
  char archivo[100];
  int valor;
  int opcion;
  char fecha[100];
  
  int op;
  while(op!=8){
  
    printf("---------------  MENÚ  ---------------\n");
    printf("1. Importar archivo de juegos \n");
    printf("2. Agregar juego \n");
    printf("3. Mostrar juego(s) por precio \n");
    printf("4. Filtrar juego(s) por valoración \n");
    printf("5. Mostrar juego(s) del año \n");
    printf("6. Buscar juego \n");
    printf("7. Exportar archivo \n");
    printf("8. Salir del programa \n");
    printf("--------------------------------------\n");
    printf("\n¿Que operación desea realizar?\n");
    scanf("%d", &op);
    printf("\n");

    switch(op)
    {
      case 1 : 
      {
        char* nombreArchivo;
        printf("1. --- Importar Archivo de Juegos ---\n");
        printf("\nIngrese el nombre del archivo: \n");
        getchar();
        scanf("%100[^\n]s", archivo);
        Importarjuegos(archivo, MapNombre, MapAnio, MapValoracion, MapPrecio);
        break;
      }
      case 2 : 
      {
        printf("2. --- Agregar Juego --- \n");
        printf("Ingrese el nombre del juego: \n");
        getchar();
        scanf("%100[^\n]s",tmpJuego->nombre);
        getchar();
        printf("Ingrese la fecha en el que salió [DD/MM/AAAA]: \n");
        scanf("%100[^\n]s", tmpJuego->anio);
        getchar();
        printf("Ingrese la valoración: \n");
        scanf("%d", &tmpJuego->valoracion);
        getchar();
        printf("Ingrese el precio del juego: \n");
        scanf("%d", &tmpJuego->precio);
        getchar();
        agregarJuego(MapNombre, MapAnio, MapValoracion, MapPrecio,tmpJuego);
        break;
      }
      case 3 :
      {
        printf("3. --- Mostrar Juego(s) Por Precio ---\n");
        printf("Ingrese la opcion:\n 1. Mostrar de menor a mayor\n 2. Mostrar de mayor a menor\n");
        scanf("%d",&opcion);
        
        MostrarPorPrecio(MapPrecio,opcion);
        break;
          
      }
      case 4 :
      {
        printf("4. --- Filtrar Juegos(s) Por Valoración ---\n");
        printf("Ingrese la valoración mínima: \n");
        scanf("%d",&valor);
        MostrarPorValoracion(MapValoracion,valor);

        break;
          
      }
      case 5 :
      {
        printf("5. --- Mostrar Juego(s) Del Año ---\n");
        printf("Ingrese el año: \n");
        getchar();
        scanf("%100[^\n]s",fecha);
        getchar();
        //MostrarJuegoDelAnio(MapValoracion, fecha);

        break;
          
      } 
      case 6 :
      {
        printf("6. --- Buscar Juego ---\n");
        break;
        
      }
      case 7 : 
      {
        printf("7. --- Exportar archivo ---\n");
        Exportar(MapNombre);
        break;
          
      }
      case 8 : 
      {
        printf("8. --- Salir del programa ---\n");
        printf("Saliendo...\n");
        break;
      }
    }
    printf("\n");

  }
  
  return 0;
}

char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}


void Importarjuegos (char * nombreArchivo, TreeMap * MapNombre, TreeMap * MapAnio,TreeMap * MapValoracion, TreeMap * MapPrecio){

  FILE* juegos = fopen (nombreArchivo, "r");

  if (juegos == NULL)
  {
    printf("Archivo no encontrado\n");
    return;
  }
  else
  {
    printf("Archivo abierto correctamente\n");
  }
 
  char linea[1024];
  fgets (linea, 1023, juegos);
    
  while (fgets (linea, 1023, juegos) != NULL)
  {
    linea[strlen(linea) - 1] = 0;

    Juegos* tmpJuego = (Juegos*)malloc(sizeof(Juegos));
    for (int i = 0 ; i < 6 ; i++) 
    {
      char* aux = get_csv_field(linea, i); 
      switch (i)
      {
        case 0:
        {
          strcpy(tmpJuego->nombre, aux);
          break;
        }
        case 1: 
        {
          strcpy(tmpJuego->anio, aux);
          break;
        }
        case 2:
        {
          tmpJuego->valoracion = atoi(aux);
          break;
        }
        case 3:
        {
          tmpJuego->precio = atoi(aux);
          break;
        }
      }
    }
    agregarJuego(MapNombre, MapAnio, MapValoracion, MapPrecio, tmpJuego);
    

    
  }
  fclose(juegos);
  
}

void agregarJuego(TreeMap * MapNombre, TreeMap * MapAnio, TreeMap * MapValoracion, TreeMap *MapPrecio, Juegos* tmpJuego){
  
  //MAP NOMBRE
  
  if(searchTreeMap(MapNombre, tmpJuego->nombre) == NULL)
  {
    
    List* lista = createList();
    pushBack(lista, tmpJuego);
    insertTreeMap(MapNombre, tmpJuego->nombre, lista);
    
  } 
  else
  {
    List * list = searchTreeMap(MapNombre, tmpJuego->nombre)->value;
    pushBack(list, tmpJuego->nombre);
  }

  //MAP AÑO
  
  if(searchTreeMap(MapAnio, tmpJuego->anio) == NULL)
  {
    
    List* lista = createList();
    pushBack(lista, tmpJuego);
    insertTreeMap(MapAnio, tmpJuego->anio, lista);
    
  } 
  else
  {
    List * list = searchTreeMap(MapAnio, tmpJuego->anio)->value;
    pushBack(list, tmpJuego->nombre);
  }

  //MAP VALORACION
  
  if(searchTreeMap(MapValoracion, tmpJuego->valoracion) == NULL)
  {
    List* lista = createList();
    pushBack(lista, tmpJuego);
    insertTreeMap(MapValoracion, tmpJuego->valoracion, lista);
    
    
  } 
  else
  {
    List * list = searchTreeMap(MapValoracion, tmpJuego->valoracion)->value;
    pushBack(list, tmpJuego->nombre);
  } 

  //MAP PRECIO
  
  if(searchTreeMap(MapPrecio, tmpJuego->precio) == NULL)
  {
    List* lista = createList();
    pushBack(lista, tmpJuego);
    insertTreeMap(MapPrecio, tmpJuego->precio, lista);
    
  } 
  else
  {
    List * list = searchTreeMap(MapPrecio, tmpJuego->precio)->value;
    pushBack(list, tmpJuego->nombre);
  } 


  return;
}

void MostrarPorPrecio(TreeMap * MapPrecio, int opcion){
  Pair *aux;
  
  if (opcion == 1){
    
    aux = firstTreeMap(MapPrecio);
    
    while(aux != NULL){
      List * lista = aux->value;
      Juegos * tmpJuego = firstList(lista);
      while(tmpJuego != NULL){
        
        printf("%s %d\n",tmpJuego->nombre, tmpJuego->precio);
        
        tmpJuego = nextList(lista);
      }
      aux = nextTreeMap(MapPrecio); 
    }
    return ;
  }
    
  else{
    
    aux = lastTreeMap(MapPrecio);
    
    while(aux != NULL){
      List * lista = aux->value;
      Juegos * tmpJuego = firstList(lista);
      
      while(tmpJuego != NULL){
        
        printf("%s %d\n",tmpJuego->nombre,tmpJuego->precio);
        tmpJuego = nextList(lista);
      }
      aux = prevTreeMap(MapPrecio); 
    }
    return ;
  }
  
  
}

void MostrarPorValoracion(TreeMap * MapValoracion, int valor){
  
  Pair* aux = upperBound(MapValoracion,valor);
  
  while(aux != NULL)
  {
    List* lista = aux->value;
    Juegos* tmpJuego = firstList(lista);
    while(tmpJuego != NULL){
      printf("%s %d\n",tmpJuego->nombre,tmpJuego->valoracion);
      tmpJuego = nextList(lista);
    }
    
    aux = nextTreeMap(MapValoracion);
  }
  
}

//FALTA
void MostrarJuegoDelAnio(TreeMap* MapValoracion, char* Fecha){
  Pair * aux = lastTreeMap(MapValoracion);
  
}

//TA MALAAAA
void Exportar(TreeMap *MapNombre){
  
  char Narchivo[30];
  
  printf("Ingrese el nombre del archivo: ");
  getchar();
  scanf("%100[^\n]s", Narchivo);
  getchar();

  FILE *x = fopen(Narchivo, "w");
  if(x == NULL){
    printf("Error\n");
  } 
  else{
    fprintf(x,"Nombre,Año de salida,Valoracion,Precio\n");
    Pair *aux = firstTreeMap(MapNombre);
    while(aux != NULL)
    {
      Juegos *data = aux->value;
      fprintf(x,"%s,%s,%d,%d", data->nombre,data->anio,data->valoracion,data->precio);
      fprintf(x,"\n");
      aux = nextTreeMap(MapNombre);
    }
    
  }
  fclose(x);
}