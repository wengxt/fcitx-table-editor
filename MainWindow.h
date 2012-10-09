#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "ui_MainWindow.h"
#include "FileParser.h"
#include "RoleModel.h"
#include "WordModel.h"
#include "MyProxyModel.h"
#include <QMainWindow>
#include <QRegExp>

class MainWindow : public QMainWindow, public Ui::MainWindow
{
  Q_OBJECT
 public:
  MainWindow();                        
  // virtual ~MainWindow();
private slots:
  void on_action_Open_triggered();
  void on_reg_lineEdit_textChanged(const QString &arg1);

private:
  QString fileName;
  FileParser xx;
  RoleModel *roleModel;
  WordModel *wordModel;
  MyProxyModel *proxyModel;
  QRegExp *regExp;
};


#endif /* _MAINWINDOW_H_ */
