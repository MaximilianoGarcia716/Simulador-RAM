/* 
 * File:   MemoriaROM.cpp
 * Author: Araceli
 * 
 * Created on 2 de noviembre de 2016, 18:45
 */

#include "MemoriaROM.h"

MemoriaROM::MemoriaROM() {
  
}

MemoriaROM::~MemoriaROM() {
}
void MemoriaROM::CrearProcesos(int cantProcP,int cantSProc){
    int cantPadres=rand()%cantProcP;
    int cantHijos=rand()%cantSProc;
    int cantProc=cantPadres+cantHijos;
    int codigo; 
    int pila;
    codigo= rand()%5+1;
    pila= rand()%5+1;
    for(int i=0;i<cantPadres;i++){
        procesos.insert(procesos.end(),Proceso(0,i,codigo,pila,cantPadres));
    }
    
    for(int i=cantPadres;i<cantProc;i++){
        procesos.insert(procesos.end(),Proceso(1,i,codigo,pila,cantPadres));
    }
    /**********Numero subproceso***********/
    int i=0,j=5;
    for(i;i<cantProc/2;i++){
        for(j;j<cantProc;j++){
            if(i!=j){
                if(procesos[i].getNroProceso()==procesos[j].getNroProceso()){
                    if(procesos[i].getNroSubProc()==procesos[j].getNroSubProc()){
                        procesos[j].setNroSubproc();
                        j--;
                    }
                }   
            }
        }    
    }
    /*************Tiempo de Ejecucion************/
    for(int i=0;i<cantPadres;i++){
        for(int j=cantPadres;j<cantProc;j++){
            if(procesos[i].getNroProceso()==procesos[j].getNroProceso()){
                if(procesos[j].getTiempoVida()>procesos[i].getTiempoVida()){
                       procesos[j].setTiempoVida();
                    j--;
                }
            }
        }   
    }
	
	/*******Ordenar Subprocesos************/
	
	
	for(int j=1;j<=cantPadres;j++){
		int a=1;
		for(int i=cantPadres;i<cantProc;i++){
			if(procesos[i].getNroProceso()==j){
				procesos[i].setNroSubProc(a);
				a++;
			}
		}
	}   
}

vector <Proceso> MemoriaROM::getProcesos(){
    return procesos;
}
