#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


int main(int argc, char* argv[]) {
    if (argc !=7 || string(argv[1]) != "-i") {
        cerr << "Uso: " << argv[0] << " -i <Archivo>" << std::endl;
        return 1;
    }

    const char* nombreArchivo = argv[2];
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    string linea;

    while (getline(archivo, linea)) {
        cout<<linea<<endl;
    }
    
    
    archivo.close();

    return 0;
}


