#include "MainWindow.h"
#include <QFileDialog>
MainWindow::MainWindow()
{
  setupUi(this);
}

void MainWindow::on_openfile_triggered()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open MB File"),
                                                        "~/",
                                                        tr("File (*.txt)"));
    xx.openFile(fileName);
    keyCodeLineEdit->setText(xx.KeyCode);
    lengthSpinBox->setValue(xx.Length.toInt());
    pinyinLineEdit->setText(xx.pinyinPrefix);
    pinyinLensSpinBox->setValue(xx.pinyinLens.toInt());
}
