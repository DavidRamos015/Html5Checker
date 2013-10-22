void MainWindow::loadFile(const QString &fileName)
{
    //if is empty
    if(fileName.isEmpty())
    {
        //set the file name
        this->setFileName(QString ());
        ui->AppOutput->append("No file is open");
        return;
    }
    // create a QFile Object with the fileName variable
    QFile *qfo=new QFile(fileName);

    //if
    if(!(qfo->open(QIODevice::Text|QIODevice::ReadOnly)))
    {
        ui->AppOutput->append("The file "+fileName+" cannot be opened");
        QMessageBox::warning(this,"Error","The file cannot be opened",QMessageBox::Ok,QMessageBox::Ok);
        setFileName(QString());
        return;
    }
    else
    {
        ui->AppOutput->append("The file at "+fileName+" is opened");
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
            lineParser(line);
            //se cuenta la cantidad de lineas
            count_lines++;
        }
        ui->AppOutput->append("Lines: "+QString::number(count_lines));
        qfo->close();
        setFileName(fileName);
        setWindowModified(false);
    }

}



QString MainWindow::lineParser(QString line)
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
                    //si no lo es verificar si es la etiqueta de cierre </p>
                        //compararlo contra el ultimo de la pila
                        //si son iguales sacarlo de la pila


                }
                else if(tagDePila.startsWith("<"+tag))
                {
                    tagDePila=tagDePila.replace(QRegExp('"\<'+tag+'([^>]*)([^>]*)>"'),QString(""));
                    ui->TextEdit_2->setPlainText(tagDePila);
//                    //sacarlo de la pila
                    //obtener atributos y comparar aqui
                }


               // ui->TextEdit_2->appendPlainText(tag);
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

