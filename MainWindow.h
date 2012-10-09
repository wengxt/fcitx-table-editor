#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "ui_MainWindow.h"
#include <QMainWindow>
#include "FileParser.h"
#include "RoleModel.h"
#include "WordModel.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
  Q_OBJECT
 public:
  MainWindow();                        
  // virtual ~MainWindow();
private slots:
  void on_action_Open_triggered();

private:
  QString fileName;
  FileParser xx;
  RoleModel *roleModel;
  WordModel *wordModel;
};


#endif /* _MAINWINDOW_H_ */
