int validarEnteroRango(int minimo, int maximo);

float validarFloatPositivo(void);

void leerCadena(char *cadena, int tamanio);

int calcularTabletas(int dias, int frecuencia, int tabletasPorToma);

int buscarMedicamento(char medicamentos[][50], float miligramos[], int totalMedicamentos, char nombre[], float mg);

void registrarMedicamento(char medicamentos[][50], float miligramos[], int existencias[], int *totalMedicamentos);

void mostrarFarmacia(char medicamentos[][50], float miligramos[], int existencias[], int totalMedicamentos);

void editarFarmacia(char medicamentos[][50], float miligramos[], int existencias[], int *totalMedicamentos);

int seleccionarMedicamento(char medicamentos[][50], float miligramos[], int existencias[], int *totalMedicamentos);

void reservarMedicacion(int medicamento, int necesarias, int existencias[], int *reservadas);

void completarMedicacion(int medicamentoPaciente[], int dias[], int frecuencia[], int tabletasPorToma[], int tabletasReservadas[], int totalPacientes, int existencias[]);

void registrarPaciente(char nombres[][50], char apellidos[][50], int medicamentoPaciente[], int dias[], int frecuencia[], int tabletasPorToma[], int tabletasReservadas[], int *totalPacientes, char medicamentos[][50], float miligramos[], int existencias[], int *totalMedicamentos);

void mostrarPacientes(char nombres[][50], char apellidos[][50], int medicamentoPaciente[], int dias[], int frecuencia[], int tabletasPorToma[], int tabletasReservadas[], int totalPacientes, char medicamentos[][50], float miligramos[]);

int buscarPaciente(char nombres[][50], char apellidos[][50], int totalPacientes);

void editarTratamiento(char nombres[][50], char apellidos[][50], int medicamentoPaciente[], int dias[], int frecuencia[], int tabletasPorToma[], int tabletasReservadas[], int totalPacientes, char medicamentos[][50], float miligramos[], int existencias[], int *totalMedicamentos);

void eliminarPaciente(char nombres[][50], char apellidos[][50], int medicamentoPaciente[], int dias[], int frecuencia[], int tabletasPorToma[], int tabletasReservadas[], int *totalPacientes, int existencias[]);