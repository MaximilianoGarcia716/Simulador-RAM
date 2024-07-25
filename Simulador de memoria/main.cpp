#include <iostream>
#include "MemoriaROM.h"
#include "MemoriaRam.h"
#include "Graficar.h"
using namespace std;


int main (int argc, char** argv){
	srand(time(0));
    MemoriaROM ROM;
    int cantProcP, cantSubProc;
    bool tipo, UsoMem;
    cout<<"Cuantos procesos desea crear como maximo?"<<endl;
    cin>>cantProcP;
    cout<<"Cuantos subprocesos desea crear como maximo?"<<endl;
    cin>>cantSubProc;
    if(cantProcP==0||cantSubProc==0){
        cout<<"Cantidad de procesos invalido"<<endl;
        return 0;
    }
    ROM.CrearProcesos(cantProcP,cantSubProc);
    cout<<"Que memoria desea ejecutar"<<endl;
    cout<<"0. Memoria Secuencial"<<endl;
    cout<<"1. Memoria Aleatoria"<<endl;
    cin>>tipo;
    if(tipo!=0||tipo!=1){
        cout<<"Error al elegir gestion de memoria"<<endl;
        return 0;
    }
    cout<<"Que Espacio de memoria desea tener"<<endl;
    cout<<"1. 1020"<<endl;
    cout<<"0. 510"<<endl;
    cin>>UsoMem;     
     if(UsoMem!=0||UsoMem!=1){
        cout<<"Error al elegir el espacio de memoria"<<endl;
        return 0;
    }
    MemoriaRAM RAM(ROM.getProcesos(),UsoMem);
    try{
    if(tipo){
        RAM.MemoriaAleatoria();
    }else{
        RAM.MemoriaSecuencial();
    }
    RAM.EjecutarProcesos();
    }catch(MemoriaInsuficiente){
        cout << "Memoria insuficiente para acomodar todos los procesos" << endl << endl;
    }
    return 0;
}
