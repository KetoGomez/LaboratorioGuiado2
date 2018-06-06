/* 
 * File:   Laberinto.cpp
 * Author: Alan
 * 
 * Created on 7 de febrero de 2018, 04:46 PM
 */

#include "Laberinto.h"
//#include "Hormiga.h"
#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <list>
#include <algorithm>

using namespace std;
using std::vector;

Laberinto::Laberinto(int cantidadVrts, double probabilidadAdy) {

    vertices.resize(cantidadVrts);

    for (int i = 0; i < cantidadVrts; i++) {
        for (int j = i + 1; j < cantidadVrts; j++) {
            default_random_engine randomGenerator(time(0));
            uniform_real_distribution<double> num(0.0, 1.0);
            double numUsar = num(randomGenerator);
            if (numUsar <= probabilidadAdy && i != j) {
                vertices[i].lstAdy.push_front(j);
                vertices[j].lstAdy.push_front(i);
            }
        }
    }
}

Laberinto::Laberinto(ifstream& archivo) {
    int vrt = 0;
    int cntVrts;
    int pe = 0;
    char finLinea = ' ';


    if (!archivo) { // operador ! sobrecargado
        cerr << "No se pudo abrir el archivo de entrada" << endl;
    }

    archivo >> cntVrts;
    vertices.resize(cntVrts);

    while (vrt < cntVrts) {
        while (!archivo.eof()&&(finLinea != 10)) { // 10 ascii de fin de línea
            archivo >> pe;
            archivo.get(); // consume un blanco
            vertices[vrt].lstAdy.push_front(pe);
            finLinea = archivo.peek(); // intenta leer fin de línea
        }

        if (!archivo.eof()) {
            archivo.get();
        }
        finLinea = archivo.peek();

        ++vrt;
    }
}

Laberinto::Laberinto(const Laberinto& orig) {
    int cntVrtOri = orig.obtTotVrt();
    vertices.resize(cntVrtOri);
    for (int i = 0; i < cntVrtOri; i++) {
        vertices[i].lstAdy = orig.vertices[i].lstAdy;
    }
    
    
}

Laberinto::~Laberinto() {
}

/* MÉTODOS OBSERVADORES BÁSICOS */
bool Laberinto::xstVrt(int idVrt) const {
    if ((idVrt >= 0 && idVrt < vertices.size())) {
        return true;
    }
    return false;
}

bool Laberinto::xstAdy(int idVrtO, int idVrtD) const {
    if ((idVrtO >= 0 && idVrtO < vertices.size()) && (idVrtD >= 0 && idVrtD < vertices.size())) {
        std::list<int>::const_iterator xstAdy =
                std::find(vertices[idVrtO].lstAdy.begin(), vertices[idVrtO].lstAdy.end(), idVrtD);
        if (*xstAdy == idVrtD) { //buscar una manera de buscar 
            return true;
        }
    }

    return false;
}

int Laberinto::obtIdVrtInicial() const {
    return idVrtInicial;
}

int Laberinto::obtIdVrtFinal() const {
    return idVrtFinal;
}

void Laberinto::obtIdVrtAdys(int idVrt, vector<int>& rsp) const {
    rsp.resize(vertices.at(idVrt).lstAdy.size());
    std::copy(vertices[idVrt].lstAdy.begin(), vertices[idVrt].lstAdy.end(), rsp.begin());
}

Adyacencia Laberinto::obtDatoAdy(int idVrtO, int idVrtD) const {
    int indAdy = 0;
    if ((idVrtO >= 0 && idVrtO < vertices.size()) && (idVrtD >= 0 && idVrtD < vertices.size())) {
        indAdy = obtIndiceAdy(idVrtO, idVrtD);
    }
    return datosAdys.at(indAdy);
}

int Laberinto::obtCntAdy(int idVrt) const {
    return vertices[idVrt].lstAdy.size();
}

int Laberinto::obtTotAdy() const {
    /*
    int total = 0;

    for (int i = 0; i < vertices.size(); i++) {
        total += vertices[i].lstAdy.size();
    }

    return total;*/
    
    return datosAdys.size();
}

int Laberinto::obtTotVrt() const {
    return vertices.size();
}

int Laberinto::caminoMasCorto(int idVrtO, int idVrtD, vector<int>& camino) const {
    int cntVrts = vertices.size();
    bool visto[cntVrts];
    int distancia[cntVrts];
    int antecesor[cntVrts];
    vector<int> ady;
    int posM = idVrtO; //posicion del vertice menor.

    for (int i = 0; i < cntVrts; i++) {
        visto[i] = false;
        distancia[i] = -1;
        antecesor[i] = -1;
    }

    distancia[idVrtO] = 0;

    while (visto[idVrtD] == false) {

        posM = obtPosMenor(distancia, visto);
        obtIdVrtAdys(posM, ady);

        for (std::vector<int>::const_iterator it = ady.begin(); it != ady.end(); it++) {
            int w = *it;
            if (distancia[w] > distancia[posM] + 1 || distancia[w] == -1) {
                distancia[w] = distancia[posM] + 1;
                antecesor[w] = posM;
            }
        }
        visto[posM] = true;

    }

    int totVrt = distancia[idVrtD] + 1;
    int idVrt = idVrtD;

    for (int n = 0; n < totVrt; n++) {
        camino.push_back(idVrt);
        idVrt = antecesor[idVrt];
    }

    reverse(camino.begin(), camino.end());


    return distancia[idVrtD];
}

int Laberinto::caminoEncontrado(int idVrtO, int idVrtD, vector<int>& camino) const {
}

double Laberinto::sumaTotalFerormona() const {
    double totFer = 0;
    
    for (std::map<int, Adyacencia>::const_iterator iter = datosAdys.begin();
            iter != datosAdys.end(); ++iter) {
        
        totFer += iter->second.obtCntFerormona(); //const Fer
    }

    return totFer;
}

void Laberinto::asgIdVrtInicial(int idVrtInicialN) {
    idVrtInicial = idVrtInicialN;
}

void Laberinto::asgIdVrtFinal(int idVrtFinalN) {
    idVrtFinal = idVrtFinalN;
}

void Laberinto::asgDatoAdy(int idVrtO, int idVrtD, const Adyacencia& ady) {
    if ((idVrtO >= 0 && idVrtO < vertices.size()) &&(idVrtD >= 0 && idVrtD < vertices.size())) {
        int ind = obtIndiceAdy(idVrtO, idVrtD);
        
        //std::cout << "indice adyacencia: " <<ind << std::endl;
        
        datosAdys[ind] = ady;
        
        //std::cout  << "tamano adyacencia: "<< datosAdys.size() << std::endl;
    }
}

void Laberinto::decrementarFerormonaAdys(double decrFerormona) {
    for (std::map<int, Adyacencia>::iterator iter = datosAdys.begin();
            iter != datosAdys.end(); ++iter) {
        iter->second.asgCntFerormona(iter->second.obtCntFerormona() * decrFerormona);
    }
}

void Laberinto::actualizarValoracionAdys() {
    for (std::map<int, Adyacencia>::iterator iter = datosAdys.begin();
            iter != datosAdys.end(); ++iter) {
        iter->second.asgCntFerormona(iter->second.obtCntFerormona() / sumaTotalFerormona());
    }
}

int Laberinto::obtIndiceAdy(int f, int c) const {
    if (f > c) {
        int t = f;
        f = t;
        c = f;
    }
    return f * vertices.size() + c - f * (f + 1) / 2;
}

int Laberinto::obtPosMenor(int* dist, bool* visto) const {

    int idVrtDisM = -1;
    int disMen = -1;
    int cntVrts = vertices.size();

    for (int i = 0; i < cntVrts; i++) {
        if ((dist[i] != -1) && (visto[i] == false) && (disMen > dist[i] || disMen == -1)) {
            idVrtDisM = i;
            disMen = dist[i];
        }
    }

    return idVrtDisM;

}

int main(int argc, char** argv) {

    return 0;
}