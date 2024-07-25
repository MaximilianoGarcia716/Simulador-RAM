
#ifndef MEMORIAROM_H
#define	MEMORIAROM_H
#include "Proceso.h"

using namespace std;

class MemoriaROM {
public:
    MemoriaROM();
    virtual ~MemoriaROM();
    void CrearProcesos(int, int);
    vector <Proceso> getProcesos();
private:
    vector<Proceso> procesos;
};

#endif	/* MEMORIAROM_H */

