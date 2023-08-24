#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


int main(int argc, char* argv[]) {


    const char* nombreArchivo = argv[2];
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    string linea;
    getline(archivo, linea);
    istringstream iss(linea);
    string token;
    int contadorComas = 0;
    for (char c : linea) {
        if (c == ',') {
            contadorComas++;
        }
    }
    int arrSize = 0;
    int arr[contadorComas +1];
    cout<<contadorComas<<endl;
    while (getline(iss, token, ',')) {
        arr[arrSize] = stoi(token);
        arrSize++;
        }
    
    archivo.close();

    return 0;
}


