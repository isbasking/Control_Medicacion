#include <stdio.h>
#include <string.h>
#include <math.h>
#include "funciones.h"

// VALIDAR NUMEROS ENTEROS
int validarEnteroRango(int minimo, int maximo)
{
    int numero = 0;
    int validacion;
    int caracter;
    int entradaValida;

    do
    {
        validacion = scanf("%d", &numero);
        entradaValida = 1;

        while ((caracter = getchar()) != '\n' && caracter != EOF)
        {
            if (caracter != ' ' && caracter != '\t')
            {
                entradaValida = 0;
            }
        }

        if (validacion != 1 || entradaValida == 0 || numero < minimo || numero > maximo)
        {
            printf("ERROR: Ingrese un numero entre %d y %d.\n", minimo, maximo);
            printf("Ingrese nuevamente: ");
        }

    } while (validacion != 1 || entradaValida == 0 || numero < minimo || numero > maximo);

    return numero;
}

// VALIDAR NUMEROS DECIMALES POSITIVOS
float validarFloatPositivo(void)
{
    float numero = 0;
    int validacion;
    int caracter;
    int entradaValida;

    do
    {
        validacion = scanf("%f", &numero);
        entradaValida = 1;

        while ((caracter = getchar()) != '\n' && caracter != EOF)
        {
            if (caracter != ' ' && caracter != '\t')
            {
                entradaValida = 0;
            }
        }

        if (validacion != 1 || entradaValida == 0 || !isfinite(numero) || numero <= 0)
        {
            printf("ERROR: Ingrese un numero mayor que cero.\n");
            printf("Ingrese nuevamente: ");
        }

    } while (validacion != 1 || entradaValida == 0 || !isfinite(numero) || numero <= 0);

    return numero;
}

// LEER CADENAS DE CARACTERES
void leerCadena(char *cadena, int tamanio)
{
    int longitud;
    int caracter;

    do
    {
        if (fgets(cadena, tamanio, stdin) == NULL)
        {
            cadena[0] = '\0';
            return;
        }

        longitud = strlen(cadena);

        if (longitud > 0 && cadena[longitud - 1] == '\n')
        {
            cadena[longitud - 1] = '\0';
        }
        else
        {
            while ((caracter = getchar()) != '\n' && caracter != EOF);
        }

        if (cadena[0] == '\0')
        {
            printf("ERROR: El campo no puede estar vacio.\n");
            printf("Ingrese nuevamente: ");
        }

    } while (cadena[0] == '\0');
}

// CALCULAR TABLETAS NECESARIAS
int calcularTabletas(int dias, int frecuencia, int tabletasPorToma)
{
    return dias * frecuencia * tabletasPorToma;
}

// BUSCAR MEDICAMENTO
int buscarMedicamento(char medicamentos[][50], float miligramos[], int totalMedicamentos, char nombre[], float mg)
{
    for (int posicion = 0; posicion < totalMedicamentos; posicion++)
    {
        if (strcmp(nombre, medicamentos[posicion]) == 0 && mg == miligramos[posicion])
        {
            return posicion;
        }
    }

    return -1;
}

// REGISTRAR MEDICAMENTO
void registrarMedicamento(char medicamentos[][50], float miligramos[], int existencias[], int *totalMedicamentos)
{
    char nombre[50];
    float mg;
    int posicion;
    int cantidad;

    printf("\n======= REGISTRAR MEDICAMENTO =======\n");
    printf("Nombre del medicamento: ");
    leerCadena(nombre, 50);

    printf("Miligramos por tableta: ");
    mg = validarFloatPositivo();

    posicion = buscarMedicamento(medicamentos, miligramos, *totalMedicamentos, nombre, mg);

    if (posicion != -1)
    {
        printf("El medicamento ya esta registrado.\n");
        printf("Cantidad de tabletas que desea agregar: ");
        cantidad = validarEnteroRango(0, 1000000);
        existencias[posicion] += cantidad;
        printf("Existencias actualizadas correctamente.\n");
        return;
    }

    if (*totalMedicamentos >= 20)
    {
        printf("ERROR: No se pueden registrar mas medicamentos.\n");
        return;
    }

    strcpy(medicamentos[*totalMedicamentos], nombre);
    miligramos[*totalMedicamentos] = mg;

    printf("Cantidad de tabletas disponibles: ");
    existencias[*totalMedicamentos] = validarEnteroRango(0, 1000000);

    (*totalMedicamentos)++;

    printf("Medicamento registrado correctamente.\n");
}

// MOSTRAR FARMACIA
void mostrarFarmacia(char medicamentos[][50], float miligramos[], int existencias[], int totalMedicamentos)
{
    if (totalMedicamentos == 0)
    {
        printf("\nNo existen medicamentos registrados.\n");
        return;
    }

    printf("\n======= FARMACIA HOSPITALARIA =======\n");

    for (int posicion = 0; posicion < totalMedicamentos; posicion++)
    {
        printf("\nMedicamento %d\n", posicion + 1);
        printf("Nombre: %s\n", medicamentos[posicion]);
        printf("Concentracion: %.2f mg\n", miligramos[posicion]);
        printf("Tabletas disponibles: %d\n", existencias[posicion]);

        if (existencias[posicion] == 0)
        {
            printf("Estado: SIN EXISTENCIAS\n");
        }
        else
        {
            printf("Estado: DISPONIBLE\n");
        }
    }
}

// EDITAR FARMACIA
void editarFarmacia(char medicamentos[][50], float miligramos[], int existencias[], int *totalMedicamentos)
{
    int opcion;
    int posicion;
    int cantidad;

    do
    {
        printf("\n======= EDITAR FARMACIA =======\n");
        printf("1. Registrar nuevo medicamento\n");
        printf("2. Agregar existencias\n");
        printf("3. Corregir cantidad disponible\n");
        printf("4. Regresar\n");
        printf("Seleccione una opcion: ");

        opcion = validarEnteroRango(1, 4);

        switch (opcion)
        {
        case 1:
            registrarMedicamento(medicamentos, miligramos, existencias, totalMedicamentos);
            break;
        case 2:
            if (*totalMedicamentos == 0)
            {
                printf("No existen medicamentos registrados.\n");
                break;
            }

            mostrarFarmacia(medicamentos, miligramos, existencias, *totalMedicamentos);

            printf("Seleccione el medicamento: ");
            posicion = validarEnteroRango(1, *totalMedicamentos) - 1;

            printf("Cantidad de tabletas que llegaron: ");
            cantidad = validarEnteroRango(1, 1000000);

            existencias[posicion] += cantidad;

            printf("Existencias agregadas correctamente.\n");
            break;
        case 3:
            if (*totalMedicamentos == 0)
            {
                printf("No existen medicamentos registrados.\n");
                break;
            }

            mostrarFarmacia(medicamentos, miligramos, existencias, *totalMedicamentos);

            printf("Seleccione el medicamento: ");
            posicion = validarEnteroRango(1, *totalMedicamentos) - 1;

            printf("Nueva cantidad de tabletas disponibles: ");
            existencias[posicion] = validarEnteroRango(0, 1000000);

            printf("Cantidad actualizada correctamente.\n");
            break;
        case 4:
            printf("Regresando al menu principal.\n");
            break;
        }

    } while (opcion != 4);
}

// SELECCIONAR MEDICAMENTO
int seleccionarMedicamento(char medicamentos[][50], float miligramos[], int existencias[], int *totalMedicamentos)
{
    int opcion;
    int posicion;
    char nombre[50];
    float mg;

    if (*totalMedicamentos > 0)
    {
        mostrarFarmacia(medicamentos, miligramos, existencias, *totalMedicamentos);

        printf("\n0. Ingresar medicamento no listado\n");
        printf("Seleccione el medicamento: ");
        opcion = validarEnteroRango(0, *totalMedicamentos);

        if (opcion != 0)
        {
            return opcion - 1;
        }
    }

    printf("Nombre del medicamento requerido: ");
    leerCadena(nombre, 50);

    printf("Miligramos por tableta: ");
    mg = validarFloatPositivo();

    posicion = buscarMedicamento(medicamentos, miligramos, *totalMedicamentos, nombre, mg);

    if (posicion != -1)
    {
        return posicion;
    }

    if (*totalMedicamentos >= 20)
    {
        printf("ERROR: Se alcanzo el limite de medicamentos registrados.\n");
        return -1;
    }

    posicion = *totalMedicamentos;

    strcpy(medicamentos[posicion], nombre);
    miligramos[posicion] = mg;
    existencias[posicion] = 0;

    (*totalMedicamentos)++;

    return posicion;
}

// RESERVAR MEDICACION
void reservarMedicacion(int medicamento, int necesarias, int existencias[], int *reservadas)
{
    int faltantes;

    if (existencias[medicamento] >= necesarias)
    {
        *reservadas = necesarias;
    }
    else
    {
        *reservadas = existencias[medicamento];
    }

    existencias[medicamento] -= *reservadas;
    faltantes = necesarias - *reservadas;

    printf("Tabletas necesarias: %d\n", necesarias);
    printf("Tabletas reservadas: %d\n", *reservadas);

    if (faltantes > 0)
    {
        printf("ALERTA: Medicacion insuficiente.\n");
        printf("Tabletas faltantes: %d\n", faltantes);
        printf("Se debe conseguir la medicacion de manera inmediata.\n");
    }
    else
    {
        printf("Medicacion reservada completamente.\n");
    }
}

// COMPLETAR MEDICACION PENDIENTE
void completarMedicacion(int medicamentoPaciente[], int dias[], int frecuencia[], int tabletasPorToma[], int tabletasReservadas[], int totalPacientes, int existencias[])
{
    int medicamento;
    int necesarias;
    int faltantes;
    int cantidad;

    for (int posicion = 0; posicion < totalPacientes; posicion++)
    {
        medicamento = medicamentoPaciente[posicion];
        necesarias = calcularTabletas(dias[posicion], frecuencia[posicion], tabletasPorToma[posicion]);
        faltantes = necesarias - tabletasReservadas[posicion];

        if (faltantes > 0 && existencias[medicamento] > 0)
        {
            if (existencias[medicamento] >= faltantes)
            {
                cantidad = faltantes;
            }
            else
            {
                cantidad = existencias[medicamento];
            }

            tabletasReservadas[posicion] += cantidad;
            existencias[medicamento] -= cantidad;

            printf("\nPaciente %d: Se reservaron %d tabletas adicionales.\n", posicion + 1, cantidad);

            if (tabletasReservadas[posicion] == necesarias)
            {
                printf("Medicacion completada correctamente.\n");
            }
        }
    }
}

// REGISTRAR PACIENTE
void registrarPaciente(char nombres[][50], char apellidos[][50], int medicamentoPaciente[], int dias[], int frecuencia[], int tabletasPorToma[], int tabletasReservadas[], int *totalPacientes, char medicamentos[][50], float miligramos[], int existencias[], int *totalMedicamentos)
{
    int posicion;
    int medicamento;
    int necesarias;

    if (*totalPacientes >= 20)
    {
        printf("ERROR: No se pueden registrar mas pacientes.\n");
        return;
    }

    posicion = *totalPacientes;

    printf("\n======= REGISTRAR PACIENTE =======\n");

    printf("Primer nombre: ");
    leerCadena(nombres[posicion], 50);

    printf("Primer apellido: ");
    leerCadena(apellidos[posicion], 50);

    medicamento = seleccionarMedicamento(medicamentos, miligramos, existencias, totalMedicamentos);

    if (medicamento == -1)
    {
        printf("No fue posible registrar el tratamiento.\n");
        return;
    }

    medicamentoPaciente[posicion] = medicamento;

    printf("Dias de tratamiento: ");
    dias[posicion] = validarEnteroRango(1, 365);

    printf("Cuantas veces al dia toma el medicamento: ");
    frecuencia[posicion] = validarEnteroRango(1, 24);

    printf("Cantidad de tabletas por toma: ");
    tabletasPorToma[posicion] = validarEnteroRango(1, 100);

    necesarias = calcularTabletas(dias[posicion], frecuencia[posicion], tabletasPorToma[posicion]);

    (*totalPacientes)++;

    printf("\nPaciente registrado correctamente.\n");

    reservarMedicacion(medicamento, necesarias, existencias, &tabletasReservadas[posicion]);
}

// MOSTRAR PACIENTES
void mostrarPacientes(char nombres[][50], char apellidos[][50], int medicamentoPaciente[], int dias[], int frecuencia[], int tabletasPorToma[], int tabletasReservadas[], int totalPacientes, char medicamentos[][50], float miligramos[])
{
    int medicamento;
    int necesarias;
    int faltantes;

    if (totalPacientes == 0)
    {
        printf("\nNo existen pacientes registrados.\n");
        return;
    }

    printf("\n======= PACIENTES REGISTRADOS =======\n");

    for (int posicion = 0; posicion < totalPacientes; posicion++)
    {
        medicamento = medicamentoPaciente[posicion];
        necesarias = calcularTabletas(dias[posicion], frecuencia[posicion], tabletasPorToma[posicion]);
        faltantes = necesarias - tabletasReservadas[posicion];

        printf("\nPaciente %d\n", posicion + 1);
        printf("Nombre: %s %s\n", nombres[posicion], apellidos[posicion]);
        printf("Medicamento: %s %.2f mg\n", medicamentos[medicamento], miligramos[medicamento]);
        printf("Dias registrados de tratamiento: %d\n", dias[posicion]);
        printf("Tomas diarias: %d\n", frecuencia[posicion]);
        printf("Tabletas por toma: %d\n", tabletasPorToma[posicion]);
        printf("Tabletas necesarias: %d\n", necesarias);
        printf("Tabletas reservadas: %d\n", tabletasReservadas[posicion]);
        printf("Tabletas faltantes: %d\n", faltantes);

        if (dias[posicion] == 0)
        {
            printf("Estado: TRATAMIENTO FINALIZADO\n");
        }
        else if (faltantes > 0)
        {
            printf("Estado: MEDICACION PENDIENTE\n");
        }
        else
        {
            printf("Estado: MEDICACION COMPLETA\n");
        }
    }
}

// BUSCAR PACIENTE
int buscarPaciente(char nombres[][50], char apellidos[][50], int totalPacientes)
{
    int posicion;

    if (totalPacientes == 0)
    {
        printf("\nNo existen pacientes registrados.\n");
        return -1;
    }

    printf("\n======= SELECCIONAR PACIENTE =======\n");

    for (int posicion = 0; posicion < totalPacientes; posicion++)
    {
        printf("%d. %s %s\n", posicion + 1, nombres[posicion], apellidos[posicion]);
    }

    printf("Seleccione el paciente: ");
    posicion = validarEnteroRango(1, totalPacientes) - 1;

    return posicion;
}

// EDITAR TRATAMIENTO
void editarTratamiento(char nombres[][50], char apellidos[][50], int medicamentoPaciente[], int dias[], int frecuencia[], int tabletasPorToma[], int tabletasReservadas[], int totalPacientes, char medicamentos[][50], float miligramos[], int existencias[], int *totalMedicamentos)
{
    int posicion;
    int opcion;
    int medicamento;
    int nuevoMedicamento;
    int necesarias;
    int consumidas;
    int diasTranscurridos;
    int maximoDias;

    posicion = buscarPaciente(nombres, apellidos, totalPacientes);

    if (posicion == -1)
    {
        return;
    }

    if (dias[posicion] == 0)
    {
        printf("El tratamiento ya se encuentra finalizado.\n");
        return;
    }

    maximoDias = tabletasReservadas[posicion] / (frecuencia[posicion] * tabletasPorToma[posicion]);

    if (maximoDias > dias[posicion])
    {
        maximoDias = dias[posicion];
    }

    printf("Cuantos dias completos de tratamiento ha recibido desde la ultima actualizacion: ");
    diasTranscurridos = validarEnteroRango(0, maximoDias);

    consumidas = calcularTabletas(diasTranscurridos, frecuencia[posicion], tabletasPorToma[posicion]);

    tabletasReservadas[posicion] -= consumidas;
    dias[posicion] -= diasTranscurridos;

    if (dias[posicion] == 0)
    {
        printf("El paciente ha completado su tratamiento.\n");
        return;
    }

    do
    {
        medicamento = medicamentoPaciente[posicion];

        printf("\n======= EDITAR TRATAMIENTO =======\n");
        printf("Paciente: %s %s\n", nombres[posicion], apellidos[posicion]);
        printf("Medicamento: %s %.2f mg\n", medicamentos[medicamento], miligramos[medicamento]);
        printf("Dias restantes: %d\n", dias[posicion]);
        printf("Tomas diarias: %d\n", frecuencia[posicion]);
        printf("Tabletas por toma: %d\n", tabletasPorToma[posicion]);
        printf("1. Modificar dias restantes\n");
        printf("2. Modificar tabletas por toma\n");
        printf("3. Modificar frecuencia diaria\n");
        printf("4. Cambiar medicamento\n");
        printf("5. Finalizar tratamiento anticipadamente\n");
        printf("6. Regresar\n");
        printf("Seleccione una opcion: ");

        opcion = validarEnteroRango(1, 6);

        if (opcion == 6)
        {
            printf("Regresando al menu principal.\n");
            return;
        }

        nuevoMedicamento = medicamento;

        switch (opcion)
        {
        case 1:
            printf("Nueva cantidad de dias restantes: ");
            dias[posicion] = validarEnteroRango(1, 365);
            break;
        case 2:
            printf("Nueva cantidad de tabletas por toma: ");
            tabletasPorToma[posicion] = validarEnteroRango(1, 100);
            break;
        case 3:
            printf("Nueva cantidad de tomas diarias: ");
            frecuencia[posicion] = validarEnteroRango(1, 24);
            break;
        case 4:
            nuevoMedicamento = seleccionarMedicamento(medicamentos, miligramos, existencias, totalMedicamentos);

            if (nuevoMedicamento == -1)
            {
                continue;
            }

            printf("Dias del nuevo tratamiento: ");
            dias[posicion] = validarEnteroRango(1, 365);

            printf("Tomas diarias: ");
            frecuencia[posicion] = validarEnteroRango(1, 24);

            printf("Tabletas por toma: ");
            tabletasPorToma[posicion] = validarEnteroRango(1, 100);
            break;
        case 5:
            dias[posicion] = 0;
            break;
        }

        existencias[medicamento] += tabletasReservadas[posicion];

        tabletasReservadas[posicion] = 0;
        medicamentoPaciente[posicion] = nuevoMedicamento;

        necesarias = calcularTabletas(dias[posicion], frecuencia[posicion], tabletasPorToma[posicion]);

        printf("\nTratamiento actualizado correctamente.\n");

        if (dias[posicion] == 0)
        {
            printf("Medicacion no utilizada devuelta a farmacia.\n");
            printf("Tratamiento finalizado.\n");
            return;
        }

        reservarMedicacion(nuevoMedicamento, necesarias, existencias, &tabletasReservadas[posicion]);

    } while (opcion != 6);
}

// ELIMINAR PACIENTE
void eliminarPaciente(char nombres[][50], char apellidos[][50], int medicamentoPaciente[], int dias[], int frecuencia[], int tabletasPorToma[], int tabletasReservadas[], int *totalPacientes, int existencias[])
{
    int posicion;
    int opcion;
    int medicamento;
    int diasAntes;
    int diasCumplidos;
    int consumidas;
    int devueltas;
    int necesarias;

    posicion = buscarPaciente(nombres, apellidos, *totalPacientes);

    if (posicion == -1)
    {
        return;
    }

    medicamento = medicamentoPaciente[posicion];

    printf("\n======= ELIMINAR PACIENTE =======\n");
    printf("Paciente: %s %s\n", nombres[posicion], apellidos[posicion]);

    if (dias[posicion] > 0)
    {
        printf("1. Completo el tratamiento\n");
        printf("2. Sale antes de completar el tratamiento\n");
        printf("3. Cancelar eliminacion\n");
        printf("Seleccione una opcion: ");

        opcion = validarEnteroRango(1, 3);

        switch (opcion)
        {
        case 1:
            necesarias = calcularTabletas(dias[posicion], frecuencia[posicion], tabletasPorToma[posicion]);

            if (tabletasReservadas[posicion] < necesarias)
            {
                printf("ERROR: El paciente tiene medicacion pendiente.\n");
                printf("No se puede confirmar el tratamiento completo.\n");
                return;
            }

            printf("Tratamiento completado.\n");
            printf("No se devolveran tabletas a farmacia.\n");
            break;
        case 2:
            printf("Cuantos dias antes finaliza el tratamiento: ");
            diasAntes = validarEnteroRango(1, dias[posicion]);

            diasCumplidos = dias[posicion] - diasAntes;
            consumidas = calcularTabletas(diasCumplidos, frecuencia[posicion], tabletasPorToma[posicion]);

            if (consumidas > tabletasReservadas[posicion])
            {
                printf("ERROR: Los dias cumplidos superan la medicacion reservada.\n");
                printf("Eliminacion cancelada.\n");
                return;
            }

            devueltas = tabletasReservadas[posicion] - consumidas;
            existencias[medicamento] += devueltas;

            printf("Tabletas devueltas a farmacia: %d\n", devueltas);
            break;
        case 3:
            printf("Eliminacion cancelada.\n");
            return;
        }
    }
    else
    {
        printf("El tratamiento ya fue finalizado.\n");
    }

    for (int posicionActual = posicion; posicionActual < *totalPacientes - 1; posicionActual++)
    {
        strcpy(nombres[posicionActual], nombres[posicionActual + 1]);
        strcpy(apellidos[posicionActual], apellidos[posicionActual + 1]);
        medicamentoPaciente[posicionActual] = medicamentoPaciente[posicionActual + 1];
        dias[posicionActual] = dias[posicionActual + 1];
        frecuencia[posicionActual] = frecuencia[posicionActual + 1];
        tabletasPorToma[posicionActual] = tabletasPorToma[posicionActual + 1];
        tabletasReservadas[posicionActual] = tabletasReservadas[posicionActual + 1];
    }

    (*totalPacientes)--;

    printf("Paciente eliminado correctamente.\n");
}