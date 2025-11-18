#include <stdio.h>
#include <string.h>
#include "agenda.h"

// --- Funciones Auxiliares ---

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funcion para leer una cadena de forma segura
void leerCadena(char *cadena, int tam) {
    fgets(cadena, tam, stdin);
    int len = strlen(cadena);
    if (len > 0 && cadena[len - 1] == '\n') {
        cadena[len - 1] = '\0';
    }
}

// para convertir el enum Mes a cadena
const char* mes_a_cadena(enum Mes m) {
    switch (m) {
        case ENERO: return "Enero";
        case FEBRERO: return "Febrero";
        case MARZO: return "Marzo";
        case ABRIL: return "Abril";
        case MAYO: return "Mayo";
        case JUNIO: return "Junio";
        case JULIO: return "Julio";
        case AGOSTO: return "Agosto";
        case SEPTIEMBRE: return "Septiembre";
        case OCTUBRE: return "Octubre";
        case NOVIEMBRE: return "Noviembre";
        case DICIEMBRE: return "Diciembre";
        default: return "N/A";
    }
}

//para convertir el enum TipoTelefono a cadena
const char* tipo_a_cadena(enum TipoTelefono t) {
    switch (t) {
        case CASA: return "Casa";
        case MOVIL: return "Móvil";
        case OFICINA: return "Oficina";
        case OTRO: return "Otro";
        default: return "N/A";
    }
}


// --- Implementación de Funciones de agenda.h ---

/**
 * Esta función se encarga de iniciar el número de contactos a cero
 */
void iniciar_agenda(Agenda *agenda){
    agenda->num_contactos = 0;
}

/**
 * Esta función sirve para agregar un contacto nuevo en la agenda
 */
void agregar_contacto(Agenda *agenda, Contacto c){
    if (agenda->num_contactos >= MAX_CONTACTOS) {
        printf("Error: La agenda está llena.\n");
        return;
    }
    
    agenda->contactos[agenda->num_contactos] = c;
    agenda->num_contactos++;
}

/**
 * Esta función sirve para buscar un contacto por nombre en la agenda y retorna la posición del contacto si exisite
 * En caso contrario retorna -1
 */
int buscar_contacto(Agenda *agenda, char *nombre){
    for (int i = 0; i < agenda->num_contactos; i++) {
        //retorna 0 si son iguales
        if (strcmp(agenda->contactos[i].nombre, nombre) == 0) {
            return i; // contacto encontrado
        }
    }
    return -1; // contacto no encontrado
}

/**
 * Esta función  sirve para buscar un contacto por su número de telefono en la agenda
 */
int buscar_contacto_x_telefono(Agenda *agenda, char telefono[]){
    for (int i = 0; i < agenda->num_contactos; i++) {
        if (strcmp(agenda->contactos[i].telefono, telefono) == 0) {
            return i; // contacto encontrado
        }
    }
    return -1; // contacto no encontrado
}

/**
 * Esta función sirve para ordenar los contactos por nombres de forma ascendente
 */
void ordenar_contactos(Agenda *a){
    int i, j;
    Contacto temp;
    for(i = 0; i < a->num_contactos - 1; i++){
        for(j=0; j < a->num_contactos - i - 1; j++){
            //compara j con j+1
            if(strcmp(a->contactos[j].nombre, a->contactos[j+1].nombre) > 0){
                temp = a->contactos[j];
                a->contactos[j] = a->contactos[j+1];
                a->contactos[j+1] = temp;
            }
        }
    }
}

/**
 * Esta función sirve para ordenar los contactos por nombres de forma descendente
 */
void ordenar_contactos_inv(Agenda *a){
    int i, j;
    Contacto temp;
    for(i = 0; i < a->num_contactos - 1; i++){
        for(j=0; j < a->num_contactos - i - 1; j++){
            //Completar basandose en la función anterior
            if(strcmp(a->contactos[j].nombre, a->contactos[j+1].nombre) < 0){
                temp = a->contactos[j];
                a->contactos[j] = a->contactos[j+1];
                a->contactos[j+1] = temp;
            }
        }
    }
}

/**
 * Función auxiliar para imprimir un contacto
 */
void mostrar_contacto(Contacto c){
    printf("  Nombre: %s %s\n", c.nombre, c.apellido);
    printf("  Nacimiento: %d de %s\n", c.dia_nacimiento, mes_a_cadena(c.mes_nacimiento));
    printf("  Teléfono: %s (%s)\n", c.telefono, tipo_a_cadena(c.tipo_telefono));
}

/**
 * Función auxiliar para leer un contacto
 */
void leer_contacto(Contacto *c){
    int mes_num, tipo_num;

    printf("--- Nuevo Contacto ---\n");
    limpiarBuffer(); // Limpiar el buffer antes de leer cadenas para evitar problemas con fgets

    printf("Nombre: ");
    leerCadena(c->nombre, MAX_NOMBRE);

    printf("Apellido: ");
    leerCadena(c->apellido, MAX_APELLIDO);

    printf("Día de nacimiento (1-31): ");
    scanf("%d", &c->dia_nacimiento);

    printf("Mes de nacimiento (1=Enero, 12=Diciembre): ");
    scanf("%d", &mes_num);
    c->mes_nacimiento = mes_num - 1; 

    limpiarBuffer(); // Limpiar buffer porque se leyeron numeros

    printf("Número de teléfono: ");
    leerCadena(c->telefono, MAX_TELEFONO);

    printf("Tipo de teléfono (0=Casa, 1=Móvil, 2=Oficina, 3=Otro): ");
    scanf("%d", &tipo_num);
    c->tipo_telefono = tipo_num;
}

/**
 * Función que imprime todos los contactos de la agenda en pantalla
 */
void imprimir_agenda(Agenda agenda){
    if (agenda.num_contactos == 0) {
        printf("La agenda está vacía.\n");
        return;
    }

    printf("--- Mostrando %d Contactos ---\n", agenda.num_contactos);
    for (int i = 0; i < agenda.num_contactos; i++) {
        printf("----------------------------------\n");
        printf("Contacto #%d:\n", i + 1);
        mostrar_contacto(agenda.contactos[i]);
    }
    printf("----------------------------------\n");
}

/**
 * Función que sirve para cargar contactos escritos en un archivo a la agenda
 */
void cargar_contactos(char *filename, Agenda *agenda){
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Aviso: No se encontró el archivo '%s'. Se creará uno nuevo al guardar.\n", filename);
        return;
    }

    iniciar_agenda(agenda);
    
    Contacto temp;
    
    //ocupamos el formato: nombre|apellido|dia|mes|telefono|tipo_enum
    while (agenda->num_contactos < MAX_CONTACTOS && 
           fscanf(f, "%[^|]|%[^|]|%d|%d|%[^|]|%d\n",
                  temp.nombre, 
                  temp.apellido, 
                  &temp.dia_nacimiento, 
                  (int*)&temp.mes_nacimiento,
                  temp.telefono, 
                  (int*)&temp.tipo_telefono
           ) == 6) 
    {
        agregar_contacto(agenda, temp);
    }

    fclose(f);
    printf("Se cargaron %d contactos desde '%s'.\n", agenda->num_contactos, filename);
}

/**
 * Función que sirve para guardar todos los contactos de la agenda en un archivo
 */
void guardar_contactos(char *filename, Agenda agenda){
    FILE *f = fopen(filename, "w"); //w= write
    if (f == NULL) {
        printf("Error: No se pudo abrir/crear el archivo '%s' para guardar.\n", filename);
        return;
    }

    // recorre todos los contactos y los escribe en el archivo
    for (int i = 0; i < agenda.num_contactos; i++) {
        Contacto c = agenda.contactos[i];
        
        fprintf(f, "%s|%s|%d|%d|%s|%d\n",
                c.nombre,
                c.apellido,
                c.dia_nacimiento,
                c.mes_nacimiento,
                c.telefono,
                c.tipo_telefono
        );
    }

    fclose(f);
    printf("Contactos guardados exitosamente en '%s'.\n", filename);
}
