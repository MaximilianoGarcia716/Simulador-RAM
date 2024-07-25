/* 
 * File:   Procesos.h
 * Author: Araceli
 *
 * Created on 2 de noviembre de 2016, 16:01
 */

#ifndef PROCESO_H
#define	PROCESO_H

#include <ctime>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

class Proceso {
public:
    Proceso();
    Proceso(int,int,int,int,int);
    virtual ~Proceso();
    int getCodigo();
    int getPila();
    int getDatos();
    int getTiempoVida();
    int getNroProceso();
    int getNroSubProc();
    void setNroSubproc();
	void setNroSubProc(int);
    void setTiempoVida();
    
private:
    int nroproceso;
    int nrosubproc;
    int codigo;
    int pila;
    int datos;
    int tiempovida;
    
};

#endif	/* PROCESOS_H */

