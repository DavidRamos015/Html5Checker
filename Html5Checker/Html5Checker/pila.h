#ifndef PILA_H
#define PILA_H

#include <iostream>
#include <QString>
#include <QDebug>

using namespace std;

class nodoP
{
   protected:
               QString dato;
               nodoP *next;
   public:
             nodoP(QString);
             nodoP *get_siguiente(){return next;}
             QString get_dato(){return dato;}
             void set_siguiente(nodoP *x){next=x;}
};

class pila_
{
      private:
              nodoP *pila;
              nodoP *pila_aux;
              int Longitud;
      public:
             pila_();
             bool es_vacia();
             void limpiar_pila(){pila=NULL;}
             void Insertar(QString);
             void Eliminar();
             QString MostrarUltimo();
             void Imprimir();
             void Buscar(QString);
             void Eliminar_repetidos();
};

#endif // PILA_H
