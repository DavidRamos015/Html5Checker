
#include <QString>
#include <QSqlDatabase>

#ifndef SQL_H
#define SQL_H

 enum TipoQuery
{
    AtributosEtiquetas=1,
    EtiquetasEnLinea=2,
    EtiquetasPadres=3
};



class SQL
{
public:
    SQL();
    //Q_ENUMS(TipoQuery)
    QList<QString> AtributosEtiquetas(QString etiqueta);
    QList<QString> EtiquetasEnLinea();
    QList<QString> EtiquetasPadres(QString etiquetas);
private:
    QString UrlBdd();
    QString DriverBdd();
    QString getQuery(int tipoquery,QString parametro);
    QList<QString> ObtenerListado(QString Sqlquery);
    QSqlDatabase defaultDB;
};

#endif // SQL_H
