
#include "Proceso.h"

Proceso::Proceso(int tipo,int i,int codigo, int pila,int cantPP) {
    if(tipo==0){
        datos=rand()%5+1;
        nrosubproc=0;
        nroproceso=i+1;
    }
    else{
        datos=0;
        setNroSubproc();
        nroproceso=rand()%cantPP+1;
    }
    setTiempoVida();
    this->codigo=codigo;
    this->pila=pila;
    

}
void Proceso::setNroSubproc(){
    nrosubproc=rand()%9+1;
    nrosubproc+='0';
}
void Proceso::setNroSubProc(int a){
	
	nrosubproc=a;
	nrosubproc+='0';
}

Proceso::Proceso() {
    
    
}  
void Proceso::setTiempoVida(){
    tiempovida=rand()%55+5;// de 5-60 segundos
}
int Proceso::getNroProceso(){
    return nroproceso;
}
int Proceso::getNroSubProc(){
    return nrosubproc;
}

Proceso::~Proceso() {
}
int Proceso::getCodigo(){
    return codigo;
}
int Proceso::getPila(){
    return pila;
}
int Proceso::getDatos(){
    return datos;
}
int Proceso::getTiempoVida(){
    return tiempovida;
}
