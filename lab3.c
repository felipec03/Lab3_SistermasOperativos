#include "funciones.h"


int main(){
    int opt;
    char* archivoEntrada = NULL;
    char* archivoSalida = NULL;
    bool flagStdout = false;

    while((opt = getopt(argc, argv, "i:o:D")) != -1){
        switch(opt){
            case 'i':
                archivoEntrada = optarg;
                break;
            case 'o':
                archivoSalida = optarg;
                break;
            case 'D':
                flagStdout = true;
                break;
            default:
                flag = true;
                break;
        }
    }



    return 0;
}