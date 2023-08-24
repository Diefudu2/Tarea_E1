#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring> 
#include "SS.cpp"
#include "IS.cpp"
#include "PS.cpp"
#include "QS.cpp"
using namespace std;

void saveArrayToFile(int arr[], int size, const std::string& filename) {
    ofstream outputFile(filename);

    if (outputFile.is_open()) {
        for (int i = 0; i < size; ++i) {
            outputFile << arr[i];
            
            if (i != size - 1) {
                outputFile << ",";
            }
        }

        outputFile.close();
    }else{cout<<"-1\n";}
}

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




    if (argc >= 5) {
        if (strcmp(argv[4], "SS") == 0) {
            selectionSort(arr, arrSize);
            cout << "Se ordenó mediante SS" << endl;
        } else if (strcmp(argv[4], "QS") == 0) {
            quickSort(arr, 0, arrSize-1);
            cout << "Se ordenó mediante QS" << endl;
        } else if (strcmp(argv[4], "IS") == 0) {
            insertionSort(arr, arrSize);
            cout << "Se ordenó mediante IS" << endl;
        } else if (strcmp(argv[4], "PS") == 0) {
            bubbleSort(arr, arrSize);
            cout << "Se ordenó mediante PS" << endl;
        } else {
            cout << "Algoritmo de ordenamiento desconocido" << endl;
        }
    } else {
        cout << "Número insuficiente de argumentos en la línea de comandos" << endl;
    }
    
    saveArrayToFile(arr, arrSize, argv[6]);

    return 0;
}


