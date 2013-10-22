#include "pila.h"
#include <iostream>


using namespace std;

nodoP::nodoP(QString n)
{
      dato=n;
      next=NULL;
}

pila_::pila_()
{
            pila=NULL;
            pila_aux=NULL;
            Longitud=0;
}

bool pila_::es_vacia()
{
     if(pila==NULL){ return true;}
     else {return false;}
}
void pila_::Insertar(QString Dato)
{
     nodoP *nuevo;
     nuevo = new nodoP(Dato);
     if (es_vacia())
     {
                     pila = nuevo;
                     Longitud++;
     }
     else
     {
         nuevo->set_siguiente(pila);
         pila = nuevo;
         Longitud++;
     }
}

void pila_::Eliminar()
{
     if (es_vacia()) { cout<<"La pila esta vacia!!!";}
     else
     {

         pila = pila->get_siguiente();
         Longitud--;
     }
}

QString pila_::MostrarUltimo()
{
    if (es_vacia()) { cout<<"La pila esta vacia!!!";}
    else
    {
        return pila->get_dato();
    }
}


void pila_::Imprimir()
{
     if(es_vacia()){cout<<"La pila esta vacia!!!"<<endl;}
     else
     {
          pila_aux=pila;

          int pos=Longitud;
          while (pila_aux->get_siguiente()!=NULL)
          {
                qDebug()<<" posicion: "<<pos<<" dato: "<<pila_aux->get_dato()<<endl;

                pila_aux = pila_aux->get_siguiente();
                pos--;
          }
          qDebug()<<" posicion: "<<pos<<" dato: "<<pila_aux->get_dato()<<endl;
          qDebug()<<"n";
     }
}

void pila_::Buscar(QString x)
{
     int pos=Longitud;
     if(es_vacia()){cout<<"La pila esta vacia!!!"<<endl;}
     else
     {
         nodoP *pila_aux_=pila;
         while(pila_aux_->get_dato()!=x && pila_aux_->get_siguiente()!=NULL)
         {
               pila_aux_=pila_aux_->get_siguiente();
               pos--;
         }
         if(pila_aux_->get_dato()==x){cout<<"encontrado en la posicion: "<<pos<<endl;}
         else
         {
             cout<<"dato no encontrado"<<endl;
         }
     }
}

void pila_::Eliminar_repetidos()
{
     if(es_vacia()){cout<<"La pila esta vacia!!!"<<endl;}
     else
     {
         nodoP *pila_aux_=pila;
         nodoP *p=pila->get_siguiente();
         nodoP *q=pila_aux_;
         while(pila_aux_->get_siguiente()!=NULL)
         {
             p=pila_aux_->get_siguiente();
             while(p->get_siguiente()!=NULL)
             {
                 q=pila_aux_;
                 if(pila_aux_->get_dato()==p->get_dato())
                 {
                    q->set_siguiente(p->get_siguiente());
                    Longitud--;
                 }
                 p=p->get_siguiente();
             }
             pila_aux_=pila_aux_->get_siguiente();
         }
         Longitud--;
     }
}
