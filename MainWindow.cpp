#include "MainWindow.h"
#include <QFileDialog>
#include "RoleModel.h"
MainWindow::MainWindow()
{
  setupUi(this);
}

void MainWindow::on_action_Open_triggered()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open MB File"),
                                                        "~/",
                                                        tr("File (*.txt)"));
    if (fileName.isEmpty())
        return;
    xx.openFile(fileName);
    keyCodeLineEdit->setText(xx.KeyCode);
    lengthSpinBox->setValue(xx.Length.toInt());
    pinyinLineEdit->setText(xx.Pinyin);
    pinyinLensSpinBox->setValue(xx.PinyinLength.toInt());

    roleModel = new RoleModel(&xx);
    wordModel = new WordModel(&xx);
    words_role_view->setModel(roleModel);
    words_role_view->setSortingEnabled(false);
    words_role_view->horizontalHeader()->setStretchLastSection(true);
    wordDic_tableView->setModel(wordModel);
    wordDic_tableView->setSortingEnabled(true);
    wordDic_tableView->horizontalHeader()->setStretchLastSection(true);
}

