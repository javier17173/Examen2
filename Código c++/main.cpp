//Librerias necesarias para el código
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <conio.h>

//variables constantes para el rango de los vectores
#define MAX_CANDIDATOS 25
#define MAX_VOTANTES 1000

using namespace std;

//estructuras de datos a utilizar para el registro de la información
struct Candidato {
    int id;
    char nombre[100];
    char partido[100];
    int votos;
};
struct Votante {
    int id;
    char nombre[100];
    int ano_nacimiento;
    int provincia;
    bool ha_votado;
};
struct Voto {
    int votante_id;
    int candidato_id;
    int provincia;
};

//creación de vectores y variables globales
Candidato candidatos[MAX_CANDIDATOS];
Votante votantes[MAX_VOTANTES];
int total_candidatos = 0;
int total_votantes = 0;

//prototipos de funciones y procedimientos
void gotoxy(int x, int y);
void limpiar_pantalla();
void mostrar_menu();
void ingresar_candidato();
bool validar_edad(int ano_nacimiento);
void mostrar_provincias();
void votar();
void mostrar_resultados();
void menu();

//Implementación de funciones y procedimientos
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}
void limpiar_pantalla() { //Limpia la pantalla
    system("cls");
}
void mostrar_menu() { //Muestra las opciones del menú. 
    limpiar_pantalla();
    gotoxy(10, 2); printf("===== Sistema de Votaciones Electronico =====\n ");
    gotoxy(10, 4); printf("1. Ingresar Candidatos\n");
    gotoxy(10, 5); printf("2. Votaciones\n");
    gotoxy(10, 6); printf("3. Resultados\n");
    gotoxy(10, 7); printf("4. Salir\n");
    gotoxy(10, 8); printf("Ingrese una opcion: ");
}
void ingresar_candidato() { //Método a utilizar para registrar los candidatos
    system ("cls");
	if (total_candidatos >= MAX_CANDIDATOS) { //Acá se verifica que no se haya alcanzado el máximo de candidatos a registrar
        gotoxy(10, 11);printf("No se pueden registrar mas candidatos.\n");
        return;
    }
    Candidato nuevo_candidato; //Se crea el nuevo objeto candidato. 
    //Se crea con los datos de la estrucutra (ID, nombre y partido)
    gotoxy(10, 2); printf("===== Registro de Candidatos =====\n ");
    gotoxy(10, 4);printf("Ingrese el ID del candidato: ");
    scanf("%d", &nuevo_candidato.id);
    gotoxy(10, 5);printf("Ingrese el nombre del candidato: ");
    scanf(" %[^\n]s", nuevo_candidato.nombre);
    gotoxy(10, 6);printf("Ingrese el partido politico: ");
    scanf(" %[^\n]s", nuevo_candidato.partido);
    nuevo_candidato.votos = 0;

    // Verificar si el candidato ya existe. Si existe muestra error. 
    for (int i = 0; i < total_candidatos; i++) {
        if (candidatos[i].id == nuevo_candidato.id) {
           gotoxy(10, 8);printf("El candidato con ese ID ya existe.\n");
            return;
        }
    }

    candidatos[total_candidatos++] = nuevo_candidato; //Sino, se guarda en el arreglo de los candidatos. 
    gotoxy(10, 8);printf("Candidato registrado exitosamente.\n");
}
bool validar_edad(int ano_nacimiento) { //función que corrobora la edad del votante
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int ano_actual = tm.tm_year + 1900;
    return (ano_actual - ano_nacimiento) >= 18;
}
void mostrar_provincias() {  //muestra en pantalla las provincias del país al momento de votar
    printf("1. San Jose\n");
    printf("2. Alajuela\n");
    printf("3. Cartago\n");
    printf("4. Heredia\n");
    printf("5. Guanacaste\n");
    printf("6. Puntarenas\n");
    printf("7. Limon\n");
}
void votar() { //método para votar. 
    limpiar_pantalla();
    gotoxy(10,2);printf("===== Eleccion de Votos =====\n "); 
	if (total_candidatos == 0) {
        printf("No hay candidatos registrados.\n"); //Si no se registran candidatos, muestra en pantalla que no hay registrados
        return;
    }

    Votante votante; //se crea el objeto votante y se solicitan los datos según su estructura (ID, nombre, edad, provincia y voto) 
    printf("Ingrese su ID: ");
    scanf("%d", &votante.id);
    printf("Ingrese su nombre: ");
    scanf(" %[^\n]s", votante.nombre);
    printf("Ingrese su ano de nacimiento: ");
    scanf("%d", &votante.ano_nacimiento);

    if (!validar_edad(votante.ano_nacimiento)) { //se verifica que el votante sea +18 para ejercer el voto
        gotoxy(10,7);printf("Debe ser mayor de 18 anos para votar.\n");
        return;
    }

    mostrar_provincias(); // se muestran las provincias
    printf("Seleccione su provincia: ");
    scanf("%d", &votante.provincia);

    votante.ha_votado = false;

    // Verificar si el votante ya ha votado 
    for (int i = 0; i < total_votantes; i++) {
        if (votantes[i].id == votante.id) {
            if (votantes[i].ha_votado) {
                printf("Ya ha votado.\n"); //Si la persona ya ejerció el voto, no podrá realizar otro
                return;
            } else {
                votantes[i].ha_votado = true; 
                votante.ha_votado = true;
                break;
            }
        }
    }

    if (!votante.ha_votado) {
        votantes[total_votantes++] = votante; //Se registra el voto
    }
	
    printf("Lista de candidatos:\n"); //se muestran los candidatos disponibles
    for (int i = 0; i < total_candidatos; i++) {
        printf("%d. %s (%s)\n", candidatos[i].id, candidatos[i].nombre, candidatos[i].partido);
    }
    int id_candidato;
    printf("Ingrese el ID del candidato por el cual desea votar: "); //Se solicita el ID del candidato a elegir
    scanf("%d", &id_candidato);

    bool candidato_valido = false; //Se verifica que el candidato indicado sea válido
    for (int i = 0; i < total_candidatos; i++) {
        if (candidatos[i].id == id_candidato) {
            candidato_valido = true;
            candidatos[i].votos++; //Se suma su voto a favor en caso de ser válido. 
            break;
        }
    }

    if (!candidato_valido) { //Si no se escribe el ID correcto, se indica que no es válido el candidato
        printf("Candidato no valido.\n");
        return;
    }

    printf("Voto registrado exitosamente.\n"); //Sino, se realiza el voto correctamente. 
}
void mostrar_resultados() { //Método para mostrar en pantalla el resultado de la votación
    system ("cls");
	if (total_candidatos == 0) {
        printf("No hay candidatos registrados.\n\n");
        return;
    }

    int total_votos = 0; //Se muestra la cantidad de votos
    for (int i = 0; i < total_candidatos; i++) {
        total_votos += candidatos[i].votos;
    }

    gotoxy(10,2);printf("======= Resultados de la eleccion: =======\n\n"); //Se muestran los resultados
    for (int i = 0; i < total_candidatos; i++) {
        printf("%i %s (%s): %d votos (%.2f%%)\n", candidatos[i].id, candidatos[i].nombre, candidatos[i].partido, candidatos[i].votos,
               (total_votos > 0) ? (candidatos[i].votos * 100.0 / total_votos) : 0);
    }//Muestra en pantalla el ID, nombre y partido político, votos y porcentaje de votos de los candidatos

    int max_votos = 0;
    int ganador = -1;
    for (int i = 0; i < total_candidatos; i++) {
        if (candidatos[i].votos > max_votos) {
            max_votos = candidatos[i].votos;
            ganador = i;
        }
    }
	 //Muestra en pantalla el ganador de la votación
    if (ganador != -1) {
        printf("\nEl ganador es: %s (%s) con %d votos.\n\n", candidatos[ganador].nombre, candidatos[ganador].partido, candidatos[ganador].votos);
    } else {
        printf("No hubo votos en la eleccion.\n\n");
    }
}
void menu(){ //Ejecuta las opciones del sistema según la opción del menú seleccionada
	int opcion;
	system ("cls");
    do {
        mostrar_menu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresar_candidato();
                break;
            case 2:
                votar();
                break;
            case 3:
                mostrar_resultados();
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida.\n");
                break;
        }

        printf("Presione cualquier tecla para continuar...\n");
        _getch();
    } while (opcion != 4);
}

int main() {
	menu();
    return 0;
}

