/* 
 * File:   pbsLaberinto.cpp
 * Author: Marcos
 *
 * Created on 27 de mayo de 2018, 07:33 PM
 */

#include <stdlib.h>
#include <iostream>
#include "Laberinto.h"

/*
 * Simple C++ Test Suite
 */

void testLaberinto() {
    int cantidadVrts = 50;
    double probabilidadAdy = 0.2;
    Laberinto laberinto(cantidadVrts, probabilidadAdy);
    if (laberinto.obtTotVrt() != 50) {
        std::cout << "Falló prueba con 50 vértices" << std::endl;
    }
    int sumAdy;
    for (int i = 0; i < 100; i++) {
        Laberinto laberinto(cantidadVrts, probabilidadAdy);
        sumAdy = sumAdy + laberinto.obtTotAdy();
    }

    double prm = sumAdy / 100.0;
    double tPos = probabilidadAdy * (50.0 * 49.0 / 2);
    if (prm >= (tPos - 0.1) && prm <= (tPos + 0.1)) {
        std::cout << "Falló prueba de promedio y de probabilidad con 100 intentos, cantidadVrts = 50 y probabilidadAdy = 0.2" << std::endl;
    }
}

void testLaberinto2() {
    ifstream archivo("laberintop.txt", ios::in);
    Laberinto laberinto(archivo);
    if (laberinto.obtTotVrt() != 10) {
        std::cout << "Falló la prueba al leer la primera línea con 10 vértices." << std::endl;
    }
    vector<int> camino;
    laberinto.obtIdVrtAdys(0, camino);
    int vlrAdys[10] = {5, 2, 5, 3, 4, 4, 4, 3, 4, 2};
    for (int i = 0; i < 10; i++) {
        int cA = laberinto.obtCntAdy(i);
        if (cA != vlrAdys[i]) {
            std::cout << "Falló la prueba de terner las mismas adyacencias con 10 vértices." << std::endl;
        }
    }

    ifstream archivo2("laberintom.txt", ios::in);
    Laberinto laberinto2(archivo2);
    if (laberinto2.obtTotVrt() != 50) {
        std::cout << "Falló la prueba al leer la primera línea con 50 vértices." << std::endl;
    }
    int vlrAdys2[50] = {6, 8, 9, 11, 7, 11, 9, 8, 7, 8, 13, 8, 8, 8, 8, 3, 8, 2, 11, 8, 9, 6, 7, 6, 5, 5, 8, 7, 6, 11, 11, 9, 12, 10, 5, 13, 9, 9, 9, 7, 13, 12, 8, 12, 11, 9, 9, 5, 5, 9};
    for (int i = 0; i < 50; i++) {
        int cA = laberinto2.obtCntAdy(i);
        if (cA != vlrAdys2[i]) {
            std::cout << "Falló la prueba de terner las mismas adyacencias con 50 vértices en " << i << std::endl;
        }
    }
}

void testLaberinto3() {
    ifstream archivo("laberintop.txt", ios::in);
    Laberinto laberintoOrig(archivo);
    Laberinto laberinto2(laberintoOrig);
    int cntVrt = laberintoOrig.obtTotVrt();
    for (int i = 0; i < cntVrt; i++) {
        int cntAdy = laberintoOrig.obtCntAdy(i);
        int cntAdy2 = laberinto2.obtCntAdy(i);
        if (cntAdy != cntAdy2) {
            std::cout << "Falló el constructor de copias con 10 vértices" << std::endl;
            i = 10;
        }
    }

    int cantidadVrts = 100;
    double probabilidadAdy = 0.2;
    Laberinto laberinto3(cantidadVrts, probabilidadAdy);
    Laberinto laberinto4(laberinto3);
    for (int i = 0; i < cantidadVrts; i++) {
        int cntAdy = laberinto3.obtCntAdy(i);
        int cntAdy2 = laberinto4.obtCntAdy(i);
        if (cntAdy != cntAdy2) {
            std::cout << "Falló el constructor de copias con 100 vértices" << std::endl;
            i = 100;
        }
    }
}

void testCaminoMasCorto() {
    int idVrtO = 0;
    int idVrtD = 2;
    vector<int> camino;

    ifstream archivo("laberintop.txt", ios::in);
    Laberinto laberinto(archivo);
    int result = laberinto.caminoMasCorto(idVrtO, idVrtD, camino);
    for (int i = 0; i < 2; i++)
        int temp = camino[i];
    if (result != 1) {
        std::cout << "Falló el testCaminoMasCorto con laberinto pequeño con longitud 1" << std::endl;
    }
    int cam1[2] = {0, 2};
    for (int i = 0; i < result + 1; i++) {
        if (camino[i] != cam1[i]) {
            std::cout << "Falló el testCaminoMasCorto con laberinto pequeño con longitud 1, al crear camino" << std::endl;
        }
    }

    idVrtO = 0;
    idVrtD = 9;
    vector<int> camino2;
    result = laberinto.caminoMasCorto(idVrtO, idVrtD, camino2);

    if (result != 2) {
        std::cout << "Falló el testCaminoMasCorto con laberinto pequeño con longitud 2" << std::endl;
    }
    int cam2[3] = {0, 5, 9};

    for (int i = 0; i < result + 1; i++) {
        if (camino2[i] != cam2[i]) {
            std::cout << "Falló el testCaminoMasCorto con laberinto pequeño con longitud 2, al crear camino" << std::endl;
        }
    }
    int pruebaInt2 = camino2[1];

    idVrtO = 3;
    idVrtD = 7;
    vector<int> camino3;
    result = laberinto.caminoMasCorto(idVrtO, idVrtD, camino3);
    if (result != 3) {
        std::cout << "Falló el testCaminoMasCorto con laberinto pequeño con longitud 3" << std::endl;
    }
    int cam3[4] = {3, 8, 2, 7};
    for (int i = 0; i < result + 1; i++) {
        if (camino3[i] != cam3[i]) {
            std::cout << "Falló el testCaminoMasCorto con laberinto pequeño con longitud 3, al crear camino" << std::endl;
        }
    }
}

/*
void testCaminoEncontrado() {
    int idVrtO;
    int idVrtD;
    vector<int>& camino;
    Laberinto laberinto;
    int result = laberinto.caminoEncontrado(idVrtO, idVrtD, camino);
    if (true) {
        std::cout << "%TEST_FAILED% time=0 testname=testCaminoEncontrado (pbsLaberinto) message=error message sample" << std::endl;
    }
}*/

void testSumaTotalFerormona() {
    ifstream archivo("laberintop.txt", ios::in);
    Laberinto laberinto(archivo);
    vector<int> ady;
    Adyacencia adyacencia(1, 1);

    for (int i = 0; i < laberinto.obtTotVrt(); ++i) {

        laberinto.obtIdVrtAdys(i, ady);
        for (std::vector<int>::iterator it = ady.begin(); it != ady.end(); ++it) {
                laberinto.asgDatoAdy(i, *it, adyacencia);
        }
    }

    if (laberinto.sumaTotalFerormona() != laberinto.obtTotAdy()) {
        std::cout << "Falló el testSumaTotalFerormona con Ferormona: " << laberinto.sumaTotalFerormona() << " y ady: " << laberinto.obtTotAdy() << std::endl;
    }

}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% pbsLaberinto" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testLaberinto (pbsLaberinto)" << std::endl;
    testLaberinto();
    std::cout << "%TEST_FINISHED% time=0 testLaberinto (pbsLaberinto)" << std::endl;

    std::cout << "%TEST_STARTED% testLaberinto2 (pbsLaberinto)" << std::endl;
    testLaberinto2();
    std::cout << "%TEST_FINISHED% time=0 testLaberinto2 (pbsLaberinto)" << std::endl;

    std::cout << "%TEST_STARTED% testLaberinto3 (pbsLaberinto)" << std::endl;
    testLaberinto3();
    std::cout << "%TEST_FINISHED% time=0 testLaberinto3 (pbsLaberinto)" << std::endl;

    std::cout << "%TEST_STARTED% testCaminoMasCorto (pbsLaberinto)" << std::endl;
    testCaminoMasCorto();
    std::cout << "%TEST_FINISHED% time=0 testCaminoMasCorto (pbsLaberinto)" << std::endl;

    /*std::cout << "%TEST_STARTED% testCaminoEncontrado (pbsLaberinto)" << std::endl;
    testCaminoEncontrado();
    std::cout << "%TEST_FINISHED% time=0 testCaminoEncontrado (pbsLaberinto)" << std::endl;
    */
    
    std::cout << "%TEST_STARTED% testSumaTotalFerormona (pbsLaberinto)" << std::endl;
    testSumaTotalFerormona();
    std::cout << "%TEST_FINISHED% time=0 testSumaTotalFerormona (pbsLaberinto)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

