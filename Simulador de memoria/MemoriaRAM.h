
#ifndef MEMORIARAM_H
#define	MEMORIARAM_H
#include "Proceso.h"
#include "Graficar.h"

class MemoriaInsuficiente{
public:
    MemoriaInsuficiente(){};
};

class MemoriaRAM {
private:
		
	vector<Proceso> procesos;
	vector< int > Vector1;
	vector< int > Vector2;
	int cant;
        bool UsoMem;
	
public:
	void EjecutarProcesos();
	void MemoriaAleatoria();
        void MemoriaSecuencial();
	MemoriaRAM(vector<Proceso> procesos,bool UsoMem);
	~MemoriaRAM();
};

#endif
