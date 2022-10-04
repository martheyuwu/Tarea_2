#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"
#include "list.h"
typedef struct{//Se forma el struct de la propiedad, el cual nos servira mas adelante
    char id[50];
    char ciudad[50];
    char direccion[50];
    char tipo[50];
    char capacidad[50];
    char valor[50];
}propiedad;
const char *importar_propiedades(List*,HashMap*);//Se forman todas nuestras funciones a ocupar, lo que hace cada funcion esta en su titulo
void agregar_propiedad(HashMap*,List*);
void mostrar_propiedades(HashMap*,List*);
void mostrar_propiedades_ciudad(HashMap*,List*);
void mostrar_propiedades_tipo(HashMap*,List*);
void agregar_favoritos(List*);
void mostrar_favorios(HashMap*,List*);
void exportar_propiedades(HashMap*,List*,const char*);
void mostrar_propiedad_minima(HashMap*,List*);
int main(){
    const char *archivo;
    int op,aux=1; //
    List *listaid=createList();//Se crea una lista donde se podran almacenar las distintas id de las propiedades
    HashMap *mapid=createMap(100);//Se crea el mapa para las id
    List *listaidfav=createList();//Se crea otra lista para los id de las propiedades favoritas
    while (op!=10){//Se crea este while para poder mostrar las opciones cada vez que se termine un procedimiento, si se coloca 10 se termina el programa
        if (aux==0){//cuando el aux cambia a 0 significa que se logro realizar una operacion
            printf("\n********************\n");
            printf("operacion realizada\n");
            printf("********************\n");
        }
        printf("----------------------------------------\n");//Se muestran todas las posibles opciones a elegir
        printf("1.- Importar propiedades desde un archivo CSV\n");
        printf("2.- Agregar propiedad\n");
        printf("3.- Mostrar todas las propiedades\n");
        printf("4.- Mostrar propiedades de cierta ciudad\n");
        printf("5.- Mostrar propiedades según su tipo\n");
        printf("6.- Mostrar propiedades con capacidad mínima\n");
        printf("7.- Agregar a favoritos\n");
        printf("8.- Mostrar favoritos\n");
        printf("9.- Exportar base de datos actualizada\n");
        printf("10.- terminar programa\n");
        printf("----------------------------------------\n");
        printf("ingrese operacion a realizar: ");//Se pregunta que operacion y se guarda en la variable op
        scanf("%d",&op);
        switch (op){//Se realiza cada operacion dependiendo de cual se quiere hacer y se cambia el aux, en caso del 10 que es terminar programa, solo se escribe un mensaje de despedida
            case 1: archivo=importar_propiedades(listaid,mapid);
                    aux=0;
                    break;
            case 2: agregar_propiedad(mapid,listaid);
                    aux=0;
                    break;
            case 3: mostrar_propiedades(mapid,listaid);
                    aux=0;
                    break;
            case 4: mostrar_propiedades_ciudad(mapid,listaid);
                    aux=0;
                    break;
            case 5: mostrar_propiedades_tipo(mapid,listaid);
                    aux=0;
                    break;
            case 6: mostrar_propiedad_minima(mapid,listaid);
                    aux=0;
                    break;
            case 7: agregar_favoritos(listaidfav);
                    aux=0;
                    break;
            case 8: mostrar_favorios(mapid,listaidfav);
                    aux=0;
                    break;
            case 9: exportar_propiedades(mapid,listaid,archivo);
                    aux=0;
                    break;
            case 10: printf("hasta luego....");
                    break;
        }
    }
}
const char *importar_propiedades(List *listaid,HashMap *mapid){
    char *id,*ciudad,*direccion,*tipo,*capacidad,*valor,*archivo;//Se crean varias variables en donde se almacenarán los distintos datos de la propiedad, ademas de el archivo que contiene a todas estas
    char linea[1024];
    archivo=(char*)malloc(50*sizeof(char));
    printf("ingrese nombre del archivo: ");
    fflush(stdin);
    scanf("%50[^\n]s",archivo);//se pregunta por el archivo que se necesita abrir
    FILE *fp = fopen (archivo, "r");
    fgets(linea,1024,fp);
    while (fgets(linea,1024,fp)!=NULL){//mientras que hayan caracteres en el archivo, se seguira el while
        propiedad *prop=(propiedad*)malloc(sizeof(propiedad));
        id=get_csv_field(linea,0);
        pushBack(listaid,id);
        ciudad=get_csv_field(linea,1);
        direccion=get_csv_field(linea,2);
        tipo=get_csv_field(linea,3);
        capacidad=get_csv_field(linea,4);
        valor=get_csv_field(linea,5);//Se van asignando los distintos valores que estan en el archivo, a las variables
        strcpy(prop->id,id);
        strcpy(prop->ciudad,ciudad);
        strcpy(prop->direccion,direccion);
        strcpy(prop->tipo,tipo);
        strcpy(prop->capacidad,capacidad);
        strcpy(prop->valor,valor);//y despues se van copiando y moviendo hacia las variables de propiedades para poder ser insertadas en el mapa
        insertMap(mapid,prop->id,prop);
    }
    return archivo;
}
void agregar_propiedad(HashMap *mapid,List *listaid){
    char id[50],ciudad[50],direccion[50],tipo[50],capacidad[50],valor[50];//Se definen estas variables con los datos necesarios de las propiedades
    printf("ingrese id: ");//Se pregunta por el ID de la propiedad que se quiere agregar
    fflush(stdin);
    scanf("%50[^\n]s",id);
    Pair *par=searchMap(mapid,id);//Se busca el ID ingresado en el map para revisar que no se repita
    if (par!=NULL)
        printf("se repite el id\n");
    else{
        printf("ingrese ciudad: ");//En el caso de que el ID no este dentro de la lista, se puede agregar la propiedad, y se debe agregar cada dato necesario de la propiedad
        fflush(stdin);
        scanf("%50[^\n]s",ciudad);
        printf("ingrese direccion: ");
        fflush(stdin);
        scanf("%50[^\n]s",direccion);
        printf("ingrese tipo: ");
        fflush(stdin);
        scanf("%50[^\n]s",tipo);
        printf("ingrese capacidad: ");
        fflush(stdin);
        scanf("%50[^\n]s",capacidad);
        printf("ingrese valor: ");
        fflush(stdin);
        scanf("%50[^\n]s",valor);
        propiedad *prop=(propiedad*)malloc(sizeof(propiedad));//se define el tipo de variable propiedad
        strcpy(prop->id,id);//se le asigna los datos a cada variable de la estructura
        strcpy(prop->ciudad,ciudad);
        strcpy(prop->direccion,direccion);
        strcpy(prop->tipo,tipo);
        strcpy(prop->capacidad,capacidad);
        strcpy(prop->valor,valor);
        insertMap(mapid,prop->id,prop);
        pushBack(listaid,prop->id);//Se hace un pushback para que se ingrese el id a la lista de ids
    }
}
void mostrar_propiedades(HashMap *mapid,List *listaid){
    propiedad *prop=(propiedad*)malloc(sizeof(propiedad));
    char *ids=firstList(listaid);//Se va al primer nodo de la lista de id para poder ver la primera propiedad
    while (ids!=NULL){//Se continua el procedimiento mientras que hayan propiedades disponibles
        Pair *par=searchMap(mapid,ids);//Se busca el primer id dentro del mapa
        prop=par->value;
        printf("%s,",prop->id);//Y se va imprimiendo cada aspecto de la propiedad del id correspondiente
        printf("%s,",prop->ciudad);
        printf("%s,",prop->direccion);
        printf("%s,",prop->tipo);
        printf("%s,",prop->capacidad);
        printf("%s\n",prop->valor);
        ids=nextList(listaid);//Y se pasa al siguiente id en la lista
    }
}
void mostrar_propiedades_ciudad(HashMap *mapid,List *listaid){
    char ciudad[50];//Se crea la variable de ciudad
    int hay=0;
    propiedad *prop=(propiedad*)malloc(sizeof(propiedad));
    printf("ingrese ciudad: ");
    fflush(stdin);
    scanf("%50[^\n]s",ciudad);//Se pregunta por la ciudad de las cuales se deben imprimir las propiedades
    char *ids=firstList(listaid);//Se parte desde el primer id
    while (ids!=NULL){
        Pair *par=searchMap(mapid,ids);//Se busca segun id en el mapa
        prop=par->value;
        if (strcmp(ciudad,prop->ciudad)==0){//Si la variable ciudad coincide, se imprimen toda su informacion y se cambia el *hay* para decir que si hay proopiedades en esa ciudad
            hay=1;
            printf("%s,",prop->id);
            printf("%s,",prop->ciudad);
            printf("%s,",prop->direccion);
            printf("%s,",prop->tipo);
            printf("%s,",prop->capacidad);
            printf("%s\n",prop->valor);
        }
        ids=nextList(listaid);//Se pasa al siguiente id
    }
    if (hay==0)//En el caso de que nunca cambie de 0 la variable *hay*, significa que no hay propiedades en esa ciudad
        printf("no existen propiedades para esta ciudad\n");
}
void mostrar_propiedades_tipo(HashMap *mapid,List *listaid){
    char tipo[50];//Esta funcion funciona de forma similar a la anterior, solo que se muestra todas las propiedades de un cierto tipo, y no se menciona si no existen de cierto tipo
    propiedad *prop=(propiedad*)malloc(sizeof(propiedad));
    printf("ingrese tipo: ");
    fflush(stdin);
    scanf("%50[^\n]s",tipo);
    char *ids=firstList(listaid);
    while (ids!=NULL){
        Pair *par=searchMap(mapid,ids);
        prop=par->value;
        if (strcmp(tipo,prop->tipo)==0){
            printf("%s,",prop->id);
            printf("%s,",prop->ciudad);
            printf("%s,",prop->direccion);
            printf("%s,",prop->tipo);
            printf("%s,",prop->capacidad);
            printf("%s\n",prop->valor);
        }
        ids=nextList(listaid);
    }
}
void mostrar_propiedad_minima(HashMap *mapid,List *listaid){
    int cantpersonas;
    int capint;//Se crean las variables necesarias para la funcion
    propiedad *prop=(propiedad*)malloc(sizeof(propiedad));
    printf("ingrese cuantas personas son: ");
    fflush(stdin);//Se pregunta cuantas personas son las que vivirian en la propiedad
    scanf("%d",&cantpersonas);
    char *ids=firstList(listaid);//Se va al primer id
    while (ids!=NULL){
        Pair *par=searchMap(mapid,ids);
        prop=par->value;
        capint=atoi(prop->capacidad);//Mientras que hayan propiedades, se va asignando la capacidad a capint para poder comparar
        if (capint>=cantpersonas){//si la capacidad de la vivienda es mayor o igual a la cantidad de personas, se dice que la propiedad sirve y se imprimen todos sus datos
            printf("%s,",prop->id);
            printf("%s,",prop->ciudad);
            printf("%s,",prop->direccion);
            printf("%s,",prop->tipo);
            printf("%s,",prop->capacidad);
            printf("%s\n",prop->valor);
        }
        ids=nextList(listaid);//Se pasa al siguiente id
    }
}
void agregar_favoritos(List *listaidfav){
    int aux=0;
    char *id;//Se definen variables a ocupar
    id=(char*)malloc(50*sizeof(char));
    printf("ingrese id de la propiedad a agregar: ");
    fflush(stdin);
    scanf("%50[^\n]s",id);//Se pregunta el id de la propiedad que se quiere agregar a favoritos
    char *ids=firstList(listaidfav);
    while (ids!=NULL){//Se hace un while para recorrer las id de la lista de favoritos
        if (strcmp(ids,id)==0){
            aux=1;//Si la id ya esta en la lista de favoritos, se cambia el aux y se rompe el while
            break;
        }
        ids=nextList(listaidfav);//en el caso de que no sea el mismo id, se va al siguiente
    }
    if (aux==0)//si el aux nunca cambia es porque no esta el id en la lista de favoritos, por lo cual se agrega con un pushback
        pushBack(listaidfav,id);
    else
        printf("se repite el id\n");
}
void mostrar_favorios(HashMap *mapid,List *listaidfav){
    propiedad *prop=(propiedad*)malloc(sizeof(propiedad));
    char *ids=firstList(listaidfav);//Se va al principio de la lista de favoritos
    while (ids!=NULL){//mientras que la lista tenga ids se entra al while
        Pair *par=searchMap(mapid,ids);
        prop=par->value;//Se imprimen todos los valores de las propiedades favoritas
        printf("%s,",prop->id);
        printf("%s,",prop->ciudad);
        printf("%s,",prop->direccion);
        printf("%s,",prop->tipo);
        printf("%s,",prop->capacidad);
        printf("%s\n",prop->valor);
        ids=nextList(listaidfav);//Se pasa al siguiente id
    }
}
void exportar_propiedades(HashMap *mapid,List *listaid,const char *archivo){
    propiedad *prop=(propiedad*)malloc(sizeof(propiedad));     //se define la variable de tipo propiedad
    FILE *fpt;
    fpt=fopen(archivo,"w+");   //se abre el archivo de propiedades
    fprintf(fpt,"Id,Ciudad,Direccion,Tipo,Capacidad,Valor\n");  //se agrega la primera linea de texto
    char *ids=firstList(listaid);
    while (ids!=NULL){       //se recorre la listra de ids y se agregan las propiedades al csv
        Pair *par=searchMap(mapid,ids);
        prop=par->value;
        fprintf(fpt,"%s,",prop->id);
        fprintf(fpt,"%s,",prop->ciudad);
        fprintf(fpt,"%s,",prop->direccion);
        fprintf(fpt,"%s,",prop->tipo);
        fprintf(fpt,"%s,",prop->capacidad);
        fprintf(fpt,"%s\n",prop->valor);
        ids=nextList(listaid);
    }
    fclose(fpt);   //se cierra el archivo con todos los datos ya ingresados en el csv
}
