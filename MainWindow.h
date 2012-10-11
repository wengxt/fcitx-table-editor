#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "ui_MainWindow.h"
#include "FileParser.h"
#include "RuleModel.h"
#include "WordModel.h"
#include "FilterProxyModel.h"
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
  void on_pushButton_released();
  void on_action_Save_triggered();
  void on_actionSave_As_triggered();
  void on_action_About_triggered();
  void on_keyCodeLineEdit_editingFinished();
  void on_lengthSpinBox_editingFinished();
  void on_pinyinLineEdit_editingFinished();
  void on_pinyinLensSpinBox_editingFinished();

private:
  void saveFile(const QString &file);
  QString fileName;
  FileParser xx;
  RuleModel *ruleModel;
  WordModel *wordModel;
  FilterProxyModel *proxyModel;
  QRegExp regExp;
};


#endif /* _MAINWINDOW_H_ */
