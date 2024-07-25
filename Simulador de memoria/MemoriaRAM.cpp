/* 
 * File:   MemoriaRAM.cpp
 * Author: Araceli
 * 
 * Created on 2 de noviembre de 2016, 22:53
 */

#include "MemoriaRAM.h"

MemoriaRAM::MemoriaRAM(vector<Proceso> procesos, bool UsoMem) {
    this->UsoMem = UsoMem;
    cant = procesos.size();
    this->procesos = procesos;
}

MemoriaRAM::~MemoriaRAM() {
}

void MemoriaRAM::MemoriaSecuencial() {
    for (int i = 0; i < procesos.size(); i++) {
        Vector1.insert(Vector1.end(), 0);
        Vector2.insert(Vector2.end(), 0);
    }
    Vector1[0] = 0;
    Vector2[0] = 0;
    int aux1, l;
    for (int i = 1; i < cant; i++) {
        l = procesos[i - 1].getPila() + procesos[i - 1].getCodigo() + procesos[i - 1].getDatos();
        if ((Vector1[i - 1] + l) < 30) {
            Vector2[i] = Vector2[i - 1];
            Vector1[i] = Vector1[i - 1] + l;
        } else {
            Vector2[i] = Vector2[i - 1] + 1;
            aux1 = (Vector1[i - 1] + l) - 30;
            Vector1[i] = Vector1[0] + aux1;
        }
    }
    if (Vector2[Vector2.size() - 1]>(16 + 17 * UsoMem)) {
        throw MemoriaInsuficiente();
    }
    int aux;
    aux = Vector1[Vector1.size() - 1] + procesos[procesos.size() - 1].getCodigo() + procesos[procesos.size() - 1].getPila() +
            procesos[procesos.size() - 1].getDatos();
    if (Vector2[Vector2.size() - 1] == (16 + 17 * UsoMem) && aux > 30) {
        throw MemoriaInsuficiente();
    }
}

void MemoriaRAM::EjecutarProcesos() {
    vector <thread> v(cant);
    Graficar MapaMemoria(cant, UsoMem, procesos); // constructor
    MapaMemoria.VentanaPpal();

    for (int i = 0; i < cant; i++) {
        v.at(i) = thread(&Graficar::ProcesosHilos, &MapaMemoria, Vector1[i], Vector2[i], procesos[i].getPila(), procesos[i].getCodigo(),
                procesos[i].getDatos(), procesos[i].getTiempoVida(), i + 1,procesos[i].getNroProceso(),procesos[i].getNroSubProc());
    }
    for (int j = 0; j < procesos.size(); j++) {
        v[j].join();
    }
    MapaMemoria.Salir();
}

void MemoriaRAM::MemoriaAleatoria() {
    int xi, xf, xm, yi, yf, ym;
    bool aux;
    vector <vector<int> > Map;
    vector <int> auxiliar;
    for (int i = 0; i < 34; i++) {
        for (int j = 0; j < 30; j++) {
            auxiliar.insert(auxiliar.end(), 0);
        }
        Map.insert(Map.end(), auxiliar);
    }
    if (!UsoMem) {
        for (int i = 17; i < 34; i++) {
            for (int j = 0; j < 30; j++) {
                Map[i][j] = 1;
            }
        }
    }
    int j = 0;
    for (int i = 0; i < procesos.size(); i++) {
        aux = 0;
        xi = rand() % 30;
        yi = rand() % 34;
        xf = xi + procesos[i].getCodigo() + procesos[i].getPila() + procesos[i].getDatos();
        yf = yi;
        ym = yi;
        xm = (xi + xf) / 2;
        if (xf > 29) {
            aux = 1;
            xf = xf - 30;
            yf++;
        }
        if (xm > 29) {
            xm = xm - 30;
            ym++;
        }
        if (yf < 34) {
            if (Map[yi][xi] == 0 && Map[yf][xf] == 0 && Map[ym][xm] == 0) {
                if (aux == 0) {
                    for (int j = xi; j < (xf + 1); j++) {
                        Map[yi][j] = 1;
                    }
                } else {
                    for (int j = xi; j < 30; j++) {
                        Map[yi][j] = 1;
                    }
                    for (int j = 0; j < xf; j++) {
                        Map[yf][j] = 1;
                    }
                }
                Vector1.insert(Vector1.end(), xi);
                Vector2.insert(Vector2.end(), yi);
                j=0;
            } else {
                i--;
                j++;
            }
        } else {
            i--;
            j++;
        }
        if (j > 50) {
            throw MemoriaInsuficiente();
        }
    }

}
