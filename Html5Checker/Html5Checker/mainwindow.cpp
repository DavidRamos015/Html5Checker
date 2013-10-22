#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pila.h"
#include "sql.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


QString tag;
pila_ pilaDeTags;
bool isInsideTag=false;
bool isParagraph=false;

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile(const QString &fileName)
{
    //if is empty
    if(fileName.isEmpty())
    {
        //setFileName(QString());
        //ui->telog->setText("Archivo no encontrado");
        ui->AppOutput->setText("Archivo no encontrado.");
        return;
    }

    // create a QFile Object with the fileName variable
    QFile *qfo=new QFile(fileName);

    //if
    if(!(qfo->open(QIODevice::Text|QIODevice::ReadOnly)))
    {

        ui->AppOutput->append("El archivo "+fileName+" no se pudo abrir.");
        QMessageBox::warning(this,"Error","El archivo no se pudo abrir",QMessageBox::Ok,QMessageBox::Ok);
        //setFileName(QString());

        return;
    }
    else
    {
        ui->AppOutput->append("El archivo "+fileName+" ha sido abierto");
        QTextStream qts(qfo);
        //codigo de parseo.

        int count_lines=0;
        while(!qts.atEnd())
        {
            //se lee la linea
            QString line=qts.readLine();
            //se muestra en la pantalla
            ui->textEdit->appendPlainText(line);

            //se envia a parsearla
            HtmlSplitter(line);
            //se cuenta la cantidad de lineas
            count_lines++;
        }
        ui->AppOutput->append("No. de lineas: "+QString::number(count_lines));
        qfo->close();
        //setFileName(fileName);
        setWindowModified(false);
    }

}

QString MainWindow::HtmlSplitter(QString line)
{

    int i=0;
    tag.clear();
    while(line.length()>i)
    {
        tag=tag.replace(QString("<p>"),QString("<p>\""));
        tag=tag.replace(QString("</p>"),QString("\"</p>"));
        if(line.at(i)=='<')
        {
            tag.insert(tag.length(),line.at(i));
            isInsideTag=true;
        }
        if(line.at(i)=='>')
        {
            tag.insert(tag.length(),line.at(i));
            isInsideTag=false;
            tag=tag.simplified();
            if(tag.contains(QString("</")))
            {
                QString tagDePila=pilaDeTags.MostrarUltimo();

                tag=tag.replace(QString("</"),QString(""));
                tag=tag.replace(QString(">"),QString(""));
                if(isParagraph)
                {
                    if(false)//is tag es una etiqueta inline
                    {
                        //comparar contra pila
                        //obtener atributos y comparar aqui
                    }
                    else if(tag=="p")
                    {
                        pilaDeTags.Eliminar();
                        isParagraph=false;
                        //obtener atributos y comparar aqui
                    }
                    //hacer consulta a la base de datos y comprobar si tag es una etiqueta inline
                    //si no lo es, verificar si es la etiqueta de cierre </p>
                        //compararlo contra el ultimo de la pila
                        //si son iguales sacarlo de la pila
                }
                else if(tagDePila.startsWith("<"+tag))
                {
                    tagDePila=tagDePila.replace(QRegExp('"\<'+tag+'([^>]*)([^>]*)>"'),QString(""));
                    //ui->TextEdit_2->setPlainText(tagDePila);
                    ui->TextEdit_2->append(tagDePila);

//                    //sacarlo de la pila
                    //obtener atributos y comparar aqui
                }


               //ui->TextEdit_2-
                //ui->TextEdit_2->appendPlainText(tag);
            }
            else
            {
                tag=tag.simplified();
                if(tag.startsWith("<p"))
                {
                    isParagraph=true;
                    pilaDeTags.Insertar(tag);
                    tag.clear();
                }
                else if(isParagraph)
                {
                    //hacer consulta a base de datos acerca de las etiquetas inline
                    //si la etiqueta es una etiqueta inline entonces agragarla a la pila
                    //si la etiquet no es una etiqueta inline entonces ignorarla
                }
                else
                {
                    pilaDeTags.Insertar(tag);
                    tag.clear();
                }
            }

        }
        if(isInsideTag && line.at(i)!='<')
        {
           tag.insert(tag.length(),line.at(i));
        }
        i++;
    }

    return "";
}



void MainWindow::on_btnAbrir_2_clicked()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *e)
{

        e->setAccepted(false);
        QMessageBox msgBox;
        msgBox.setText("Desea salir de la aplicacion?");
        msgBox.setInformativeText("");
        msgBox.setStandardButtons(QMessageBox::Close | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setWindowTitle("Html5 Checker");
        int ret =msgBox.exec();

        if(ret==QMessageBox::Close){
            e->setAccepted(true);
            return;
        }

}

void MainWindow::on_btnAbrir_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir archivo"),
                                                     "",
                                                     tr("Archivos (*.html)"));

    loadFile(fileName);
}
