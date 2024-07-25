

#include "Graficar.h"

Graficar::Graficar(int a, bool UsoMem, vector<Proceso> procesos) {
	
	for (int i = 0; i < procesos.size(); i++) {
        if (1) {
            string auxiliar;
			auxiliar="Proceso ";
			auxiliar+=(procesos[i].getNroProceso() + 'A' - 1);
            auxiliar+= procesos[i].getNroSubProc();
            char* auxiliarchar = new char[auxiliar.size() + 1];
            auxiliarchar[auxiliar.size()] = '\0';
            std::copy(auxiliar.begin(), auxiliar.end(), auxiliarchar);
            auxiliarVectProc.insert(auxiliarVectProc.end(), auxiliarchar);
            auxiliarVectType.insert(auxiliarVectType.end(), procesos[i].getNroSubProc());
        }
    }
    this->UsoMem = UsoMem;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

}

void Graficar::drawGrid() {
    SDL_Rect GridRect;
    int i;
    GridRect.w = 2;
    GridRect.h = 34 * 15;
    GridRect.y = 70;
    for (i = 0; i < 31; i++) {
        GridRect.x = i * 15 - 1 + 7;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &GridRect);
    }
    GridRect.w = 30 * 15;
    GridRect.h = 2;
    GridRect.x = 7;
    for (i = 0; i < 35; i++) {
        GridRect.y = i * 15 - 1 + 70;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &GridRect);
    }
    SDL_RenderPresent(renderer);
}

void Graficar::dibujar(int r, int g, int b, int x, int y, int tamano) {

    rectangulo.x = x * 15 + 7;
    rectangulo.y = y * 15 + 70;
    rectangulo.w = 15 * tamano;
    rectangulo.h = 15;

    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rectangulo);
    drawGrid();
}

void Graficar::GenerarFondo(int winsizex, int winsizey) {
    SDL_Rect Rectangulos;
    // Clear screen  
    SDL_Rect fontRect;
    TTF_Font* fuente;
    fuente = TTF_OpenFont("times.ttf", 60);
    SDL_Color fColor;
    fColor.r = 136;
    fColor.g = 0;
    fColor.b = 21;

    Rectangulos.x = 0;
    Rectangulos.y = 0;
    Rectangulos.w = winsizex;
    Rectangulos.h = winsizey;
    SDL_SetRenderDrawColor(renderer, 192, 192, 192, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &Rectangulos);

    Rectangulos.x = 7;
    Rectangulos.y = 70;
    Rectangulos.w = 30 * 15;
    Rectangulos.h = 34 * 15;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &Rectangulos);

    Rectangulos.x = 500;
    Rectangulos.y = 90;
    Rectangulos.w = 780 - 500;
    Rectangulos.h = 450;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &Rectangulos);

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(fuente, "Memoria RAM", fColor);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    fontRect.x = 135;
    fontRect.y = 35;
    fontRect.w = 300 - 135;
    fontRect.h = 65 - 35;
    SDL_RenderCopy(renderer, Message, NULL, &fontRect);

    surfaceMessage = TTF_RenderText_Solid(fuente, "Proceso en ejecucion", fColor);
    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    fontRect.x = 540;
    fontRect.y = 60;
    fontRect.w = 730 - 540;
    fontRect.h = 85 - 60;
    SDL_RenderCopy(renderer, Message, NULL, &fontRect);

    if (!UsoMem) {
        Rectangulos.x = 7;
        Rectangulos.y = 70 + 17 * 15;
        Rectangulos.w = 30 * 15;
        Rectangulos.h = 17 * 15;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &Rectangulos);
    }
    SDL_RenderPresent(renderer);
}

int Graficar::ProcesosHilos(int x, int y, int tamano1, int tamano2, int tamano3, int tpo, int hilo, int nroproceso, int nrosubproc) {
    int i, posicion2 = 0, posicion3 = 0;
    posicion2 = x + tamano1;
    int aux1 = 0, aux2 = 0, aux3 = 0;
    for (i = 0; i < (tpo * 40); i++) {
        if (x + tamano1 < 29) {
            mtx.lock();
            dibujar(255, 0, 0, x, y, tamano1);
            mtx.unlock();
        } else {
            mtx.lock();
            dibujar(255, 0, 0, x, y, 30 - x);
            mtx.unlock();
            if (x + tamano1 - 30 > 0) {
                aux1 = x + tamano1 - 30;
                y++;
                mtx.lock();
                dibujar(255, 0, 0, 0, y, aux1);
                mtx.unlock();
                y--;
            }
        }
        if (posicion2 + tamano2 <= 29) {
            mtx.lock();
            dibujar(0, 255, 0, posicion2, y, tamano2);
            mtx.unlock();
        } else {
            if (30 - posicion2 > 0) {
                mtx.lock();
                dibujar(0, 255, 0, posicion2, y, 30 - posicion2);
                mtx.unlock();
                aux2 = posicion2 + tamano2 - 30;
                y++;
                mtx.lock();
                dibujar(0, 255, 0, 0, y, aux2);
                mtx.unlock();
                y--;
            } else {
                aux2 = tamano2;
                y++;
                mtx.lock();
                dibujar(0, 255, 0, aux1, y, aux2);
                mtx.unlock();
                y--;
            }
        }
        if (tamano3 != 0) {
            posicion3 = posicion2 + tamano2;
            if (posicion3 + tamano3 <= 29) {
                mtx.lock();
                dibujar(0, 0, 255, posicion3, y, tamano3);
                mtx.unlock();
            } else {
                if (30 - posicion3 > 0) {
                    mtx.lock();
                    dibujar(0, 0, 255, posicion3, y, 30 - posicion3);
                    mtx.unlock();
                    aux3 = posicion3 + tamano3 - 30;
                    y++;
                    mtx.lock();
                    dibujar(0, 0, 255, 0, y, aux3);
                    mtx.unlock();
                    y--;
                } else {
                    aux3 = aux1 + aux2;
                    y++;
                    mtx.lock();
                    dibujar(0, 0, 255, aux3, y, tamano3);
                    mtx.unlock();
                    y--;
                }
            }
        }
        Sleep(25);
    }
    mtx.lock();
    QuitarTextoProc(nroproceso,nrosubproc);
    mtx.unlock();
    mtx.lock();
    GenerarFondo(800, 600);
    mtx.unlock();
    mtx.lock();
    drawGrid();
    mtx.unlock();
    mtx.lock();
    TextGen();
    mtx.unlock();
    return 0;
}

void Graficar::VentanaPpal() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &window, &renderer);
    GenerarFondo(800, 600);
    TextGen();
    SDL_SetWindowTitle(window, "Memoria");
}

void Graficar::Salir() {
    while (event.type != SDL_QUIT) {
        SDL_PollEvent(&event);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graficar::TextGen() {
    SDL_Rect fontRect;
    TTF_Font* fuente;
    fuente = TTF_OpenFont("Tahoma.ttf", 30);
    SDL_Color fColor;
    fColor.r = 0;
    fColor.g = 255;
    fColor.b = 0;
    char* text;
    for (int i = 0; i < auxiliarVectProc.size(); i++) {
        text = auxiliarVectProc[i];
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(fuente, text, fColor);
        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        fontRect.x = 500;
        fontRect.y = 95+i*20;
        if(auxiliarVectType[i]==0){
            fontRect.w = 15*9;
        }
        else{
            fontRect.w = 15*10;
        }
        
        fontRect.h = 20;
        SDL_RenderCopy(renderer, Message, NULL, &fontRect);
    }
    SDL_RenderPresent(renderer);
}

void Graficar::QuitarTextoProc(int nroproceso,int nrosubproc){
    for(int i=0;i<auxiliarVectProc.size();i++){
        char* auxi;
        auxi=auxiliarVectProc[i];
        if(auxi[8]==(nroproceso+'A'-1) && auxi[9]==nrosubproc){
			
			delete auxiliarVectProc[i];
            vector<char*>::iterator iter1 = auxiliarVectProc.begin() + i;
            vector<int>::iterator iter2 = auxiliarVectType.begin() + i;
            auxiliarVectProc.erase(iter1);
            auxiliarVectType.erase(iter2);
        }
    }
}
