/* 
 * File:   Adyacencia.cpp
 * Author: Alan
 * 
 * Created on 7 de febrero de 2018, 04:49 PM
 */

#include "Adyacencia.h"

Adyacencia::Adyacencia() {
    this->cntFerormona = 0;
    this->valoracion = 0;
}

Adyacencia::Adyacencia(double cf, double v) {
    this->cntFerormona = cf;
    this->valoracion = v;
}

Adyacencia::Adyacencia(const Adyacencia& orig) {
    this->cntFerormona = orig.cntFerormona;
    this->valoracion = orig.valoracion;
}

Adyacencia::~Adyacencia() {
   
}

/* MÉTODOS OBTENEDORES */
double Adyacencia::obtCntFerormona() const{
    return this->cntFerormona;
}

double Adyacencia::obtValoracion() {
    return this->valoracion;
}

/* MÉTODOS ASIGNADORES */
void Adyacencia::asgCntFerormona(double cfn) {
    this->cntFerormona = cfn;
}

void Adyacencia::asgValoracion(double vn) {
    this->valoracion = vn;
}
