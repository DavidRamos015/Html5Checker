#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void loadFile(const QString &fileName);
    QString HtmlSplitter(QString line);
    ~MainWindow();
    
private slots:
    void on_btnAbrir_2_clicked();
    void closeEvent(QCloseEvent *e);
    void on_btnAbrir_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
