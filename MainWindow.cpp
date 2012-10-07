#include "MainWindow.h"
#include <QFileDialog>
#include "RoleModel.h"
MainWindow::MainWindow()
{
  setupUi(this);
}

void MainWindow::on_openfile_triggered()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open MB File"),
                                                        "~/",
                                                        tr("File (*.txt)"));
    if (fileName.isEmpty())
        return;
    xx.openFile(fileName);
    roleModel = new RoleModel(&xx);
    words_role_view->setModel(roleModel);
    keyCodeLineEdit->setText(xx.KeyCode);
    lengthSpinBox->setValue(xx.Length.toInt());
    pinyinLineEdit->setText(xx.pinyinPrefix);
    pinyinLensSpinBox->setValue(xx.pinyinLens.toInt());
}
