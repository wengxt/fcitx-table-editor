#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "ui_window.h"
#include <QMainWindow>
#include "FileParser.h"

class MainWindow : public QMainWindow, public Ui::window
{
  Q_OBJECT
 public:
  MainWindow();                        
  // virtual ~MainWindow();
private slots:
  void on_openfile_triggered();

private:
  QString fileName;
  FileParser xx;
};


#endif /* _MAINWINDOW_H_ */
