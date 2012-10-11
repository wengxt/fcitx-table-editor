#include "MainWindow.h"
#include <QFileDialog>
#include "RoleModel.h"
MainWindow::MainWindow()
{
  setupUi(this);

  roleModel = new RoleModel();
  wordModel = new WordModel();
  proxyModel = new FilterProxyModel();
  proxyModel->setDynamicSortFilter(true);
  regType_comboBox->addItem(tr("Regular expression"), QRegExp::RegExp);
  regType_comboBox->addItem(tr("Wildcard"), QRegExp::Wildcard);
  regType_comboBox->addItem(tr("Fixed string"), QRegExp::FixedString);
  regType_comboBox->setCurrentIndex(1);
}

void MainWindow::on_action_Open_triggered()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open MB File"),
                                                        "~/",
                                                        tr("File (*.txt)"));
    if (fileName.isEmpty())
        return;
    xx.openFile(fileName);
    roleModel->setParser(&xx);
    wordModel->setParser(&xx);
    keyCodeLineEdit->setText(xx.KeyCode);
    lengthSpinBox->setValue(xx.Length.toInt());
    pinyinLineEdit->setText(xx.Pinyin);
    pinyinLensSpinBox->setValue(xx.PinyinLength.toInt());

    words_role_view->setModel(roleModel);
    words_role_view->setSortingEnabled(false);
    words_role_view->horizontalHeader()->setStretchLastSection(true);

    proxyModel->setSourceModel(wordModel);
    proxyModel->setFilterKeyColumn(0);
    wordDic_tableView->setModel(proxyModel);
    wordDic_tableView->horizontalHeader()->setStretchLastSection(true);

}

void MainWindow::on_pushButton_released()
{
   QRegExp::PatternSyntax syntax =
           QRegExp::PatternSyntax(regType_comboBox->itemData(
                                      regType_comboBox->currentIndex()).toInt());
   regExp = QRegExp(reg_lineEdit->text(), Qt::CaseSensitive, syntax);
   proxyModel->setFilterRegExp(regExp);

}
