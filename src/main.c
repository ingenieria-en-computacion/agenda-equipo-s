#include <stdio.h>
#include "agenda.h"

void mostrarMenu();

int main(){
    Agenda miAgenda;
    Contacto contactoTemporal;
    int opcion;
    char busqueda[MAX_NOMBRE];
    int indiceEncontrado;
    
    // Iniciar la agenda
    iniciar_agenda(&miAgenda);

    //cargar contactos desde archivo
    cargar_contactos(NOMBRE_ARCHIVO, &miAgenda);

    //iniciamos ciclo
    do {
        mostrarMenu();
        printf("Seleccione una opción: ");

        if (scanf("%d", &opcion) != 1) {
            opcion = -1; // opción inválida
            limpiarBuffer(); 
        }
        printf("\n");

        switch (opcion) {
            case 1:
                // Agregar contacto
                leer_contacto(&contactoTemporal);
                agregar_contacto(&miAgenda, contactoTemporal);
                printf("Contacto agregado\n");
                break;
            case 2: 
                // Imprimir agenda
                imprimir_agenda(miAgenda);
                break;
            case 3: 
                // Buscar contacto por nombre
                printf("Ingrese el nombre del contacto a buscar: ");
                limpiarBuffer();
                leerCadena(busqueda, MAX_NOMBRE);
                indiceEncontrado = buscar_contacto(&miAgenda, busqueda);

                if (indiceEncontrado != -1) {
                    printf("Contacto encontrado:\n");
                    mostrar_contacto(miAgenda.contactos[indiceEncontrado]);
                } else {
                    printf("Contacto no encontrado.\n");
                }
                break;
            case 4: 
                // Buscar contacto por teléfono
                printf("Ingrese el número de teléfono del contacto a buscar: ");
                limpiarBuffer();
                leerCadena(busqueda, MAX_TELEFONO);
                indiceEncontrado = buscar_contacto_x_telefono(&miAgenda, busqueda);

                if (indiceEncontrado != -1) {
                    printf("Contacto encontrado:\n");
                    mostrar_contacto(miAgenda.contactos[indiceEncontrado]);
                } else {
                    printf("Contacto no encontrado.\n");
                }
                break;
            case 5:
                // Ordenar contactos Z-A
                ordenar_contactos_inv(&miAgenda);
                printf("Contactos ordenados de Z a A.\n");
                break;
            case 6:
                // Ordenar contactos A-Z
                ordenar_contactos(&miAgenda);
                printf("Contactos ordenados de A a Z.\n");
                break;
            case 7: 
                // Guardar contactos en archivo
                guardar_contactos(NOMBRE_ARCHIVO, miAgenda);
                printf("Contactos guardados en %s\n", NOMBRE_ARCHIVO);
                break;
            case 8: 
                // Salir
                printf("Saliendo del programa.\n");
                guardar_contactos(NOMBRE_ARCHIVO, miAgenda);
                break;
            default:
                printf("Opción inválida. Por favor, intente de nuevo.\n");
                break;
        
        }
        if (opcion != 8) {
            printf("\nPresione Enter para continuar...");
            limpiarBuffer();
            getchar(); // Espera a que el usuario presione Enter
        }
    }while (opcion != 8);

    return 0;

}

//implementación de las funciones declaradas en agenda.h

void mostrarMenu(){
    printf("----- Menú de la Agenda -----\n");
    printf("1. Agregar contacto\n");
    printf("2. Imprimir agenda\n");
    printf("3. Buscar contacto por nombre\n");
    printf("4. Buscar contacto por teléfono\n");
    printf("5. Ordenar contactos Z-A\n");
    printf("6. Ordenar contactos A-Z\n");
    printf("7. Guardar contactos en archivo\n");
    printf("8. Salir\n");
}
