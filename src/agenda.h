#ifndef __AGENDA_H__
#define __AGENDA_H__

#define MAX_CONTACTOS 100
#define MAX_TELEFONO 20
#define MAX_NOMBRE 30
#define MAX_APELLIDO 30
#define NOMBRE_ARCHIVO "mis_contactos.txt"

enum TipoTelefono {CASA, MOVIL, OFICINA, OTRO};
enum Mes{ENERO, FEBRERO, MARZO, ABRIL, MAYO, JUNIO, JULIO, AGOSTO, SEPTIEMBRE, OCTUBRE, NOVIEMBRE, DICIEMBRE};

struct Persona{
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    enum Mes mes_nacimiento;
    int dia_nacimiento;
    char telefono[MAX_TELEFONO];
    enum TipoTelefono tipo_telefono;
};

typedef struct Persona Contacto;

typedef struct Agenda{
    Contacto contactos[MAX_CONTACTOS];
    int num_contactos; 
} Agenda;


// --- Prototipos de Funciones Auxiliares ---
void limpiarBuffer();
void leerCadena(char *cadena, int tam);


// --- Prototipos de Funciones ---
void iniciar_agenda(Agenda *agenda);
void agregar_contacto(Agenda *agenda, Contacto c);
void imprimir_agenda(Agenda agenda);
int buscar_contacto(Agenda *agenda, char *nombre);
int buscar_contacto_x_telefono(Agenda *agenda, char telefono[]);
void ordenar_contactos(Agenda *agenda);
void ordenar_contactos_inv(Agenda *agenda);
void mostrar_contacto(Contacto c);
void leer_contacto(Contacto *c);
void cargar_contactos(char *filename, Agenda *agenda);
void guardar_contactos(char *filename, Agenda agenda);

#endif // __AGENDA_H_