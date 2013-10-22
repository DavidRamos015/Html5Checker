#include "sql.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
#include <QVariant>
#include <qDebug>

//#include <QSqlDriver>
//#include <QSqlRecord>

SQL::SQL()
{
    defaultDB =QSqlDatabase::addDatabase(DriverBdd());
}

QString SQL::UrlBdd()
{
    //return "C:\\tagsfinal.sqlite";
    return "C:\\Users\\DAVID RAMOS\\Desktop\\tagsfinal.sqlite";
}

QString SQL::DriverBdd()
{
    return "QSQLITE";
    //return "QODBC";
}


QString SQL::getQuery(int tipoquery,QString parametro)
{
    switch(tipoquery)
    {
    case 1: //EtiquetasPadres
    {
        QString sql;
        sql =QString("SELECT  DISTINCT p.Etiqueta ContenidaEn \n"
                     "FROM   Etiquetas_Hijos eh \n"
                     "       JOIN Etiquetas h \n"
                     "            ON  h.Id_Etiqueta = eh.Id_Etiqueta_Hijo \n"
                     "       JOIN Etiquetas p \n"
                     "            ON  p.Id_Etiqueta = eh.Id_Etiqueta_Padre \n"
                     "            AND p.Id_Etiqueta <> eh.Id_Etiqueta_Hijo \n"
                     " WHERE  h.Etiqueta = '<%0>'").arg(parametro);

        return sql;
    }
    case 2: //AtributosEtiquetas
        return QString("SELECT a.Atributo FROM Etiquetas_Atributos ea Join  Atributos a on a.Id_Atributo=ea.Id_Atributo Join Etiquetas e on e.Id_Etiqueta=ea.Id_Etiqueta and e.Etiqueta='<%0>'").arg(parametro);

    case 3: //EtiquetasEnLinea
        return QString("select e.Etiqueta  from Etiquetas e where e.InLineTag=1");
    default:
        return "";
    }
}

QList<QString> SQL::AtributosEtiquetas(QString etiqueta)
{
    return ObtenerListado(getQuery(2,etiqueta));
}

QList<QString> SQL::EtiquetasPadres(QString etiqueta)
{
    return ObtenerListado(getQuery(1,etiqueta));
}

QList<QString> SQL::EtiquetasEnLinea()
{
    return ObtenerListado(getQuery(1,""));
}

QList<QString> SQL::ObtenerListado(QString Sqlquery)
{


    defaultDB.setDatabaseName(UrlBdd());
    QList<QString> lista;

    if ( defaultDB.open() )
    {
        QSqlQuery query(QString::null, defaultDB);
        query.exec (Sqlquery);

        // qDebug()<<Sqlquery;

        if ( query.isActive())
        {
            // qDebug()<<"Query activo";

            while (query.next ())
            {
                QString valor2=query.value(0).toString();
                if (!valor2.isEmpty())
                    lista.append(valor2);

            }
        }
    }


    return lista;
}
