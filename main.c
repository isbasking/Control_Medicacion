#include <stdio.h>
#include "funciones.h"

int main(void)
{
    char nombres[20][50];
    char apellidos[20][50];
    int medicamentoPaciente[20];
    int dias[20];
    int frecuencia[20];
    int tabletasPorToma[20];
    int tabletasReservadas[20];
    int totalPacientes = 0;

    char medicamentos[20][50];
    float miligramos[20];
    int existencias[20];
    int totalMedicamentos = 0;

    int opcion;

    do
    {
        printf("\n======= SISTEMA DE GESTION HOSPITALARIA =======\n");
        printf("1. Registrar medicamento\n");
        printf("2. Mostrar farmacia\n");
        printf("3. Editar farmacia\n");
        printf("4. Registrar paciente\n");
        printf("5. Mostrar pacientes\n");
        printf("6. Editar tratamiento\n");
        printf("7. Eliminar paciente\n");
        printf("8. Salir\n");
        printf("Seleccione una opcion: ");

        opcion = validarEnteroRango(1, 8);

        switch (opcion)
        {
        case 1:
            registrarMedicamento(medicamentos, miligramos, existencias, &totalMedicamentos);
            break;
        case 2:
            mostrarFarmacia(medicamentos, miligramos, existencias, totalMedicamentos);
            break;
        case 3:
            editarFarmacia(medicamentos, miligramos, existencias, &totalMedicamentos);
            break;
        case 4:
            registrarPaciente(nombres, apellidos, medicamentoPaciente, dias, frecuencia, tabletasPorToma, tabletasReservadas, &totalPacientes, medicamentos, miligramos, existencias, &totalMedicamentos);
            break;
        case 5:
            mostrarPacientes(nombres, apellidos, medicamentoPaciente, dias, frecuencia, tabletasPorToma, tabletasReservadas, totalPacientes, medicamentos, miligramos);
            break;
        case 6:
            editarTratamiento(nombres, apellidos, medicamentoPaciente, dias, frecuencia, tabletasPorToma, tabletasReservadas, totalPacientes, medicamentos, miligramos, existencias, &totalMedicamentos);
            break;
        case 7:
            eliminarPaciente(nombres, apellidos, medicamentoPaciente, dias, frecuencia, tabletasPorToma, tabletasReservadas, &totalPacientes, existencias);
            break;
        case 8:
            printf("\nSaliendo del programa...\n");
            break;
        }

        if (opcion != 8)
        {
            completarMedicacion(medicamentoPaciente, dias, frecuencia, tabletasPorToma, tabletasReservadas, totalPacientes, existencias);
        }

    } while (opcion != 8);

    return 0;
}