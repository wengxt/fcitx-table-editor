#include "MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "RuleModel.h"
MainWindow::MainWindow()
{
  setupUi(this);

  ruleModel = new RuleModel();
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
    if (!QFile::exists(fileName))
        return;
    xx.openFile(fileName);
    ruleModel->setParser(&xx);
    wordModel->setParser(&xx);
    keyCodeLineEdit->setText(xx.KeyCode);
    lengthSpinBox->setValue(xx.Length.toInt());
    pinyinLineEdit->setText(xx.Pinyin);
    pinyinLensSpinBox->setValue(xx.PinyinLength.toInt());

    words_rule_view->setModel(ruleModel);
    words_rule_view->setSortingEnabled(false);
    words_rule_view->horizontalHeader()->setStretchLastSection(true);

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

void MainWindow::on_action_Save_triggered()
{
    saveFile(fileName);
}

void MainWindow::on_actionSave_As_triggered()
{
    QString saveAsFileName = QFileDialog::getSaveFileName(this, tr("Save MB Txt File"),
                                "~/untitled.txt",
                                tr("MB txt file (*.txt)"));
    if (fileName.isEmpty())
        return;
    saveFile(saveAsFileName);
}

void MainWindow::on_action_About_triggered()
{

}

void MainWindow::on_keyCodeLineEdit_editingFinished()
{
    QString keyCodeText = keyCodeLineEdit->text();
    if (!keyCodeText.isEmpty())
        xx.KeyCode = keyCodeText;
}

void MainWindow::on_lengthSpinBox_editingFinished()
{
    QString lengthText = lengthSpinBox->text();
    if (lengthText != "0")
        xx.Length = lengthText;
}

void MainWindow::on_pinyinLineEdit_editingFinished()
{
   QString pinyinText = pinyinLineEdit->text();
   if (!pinyinText.isEmpty())
       xx.Pinyin = pinyinText;
}


void MainWindow::on_pinyinLensSpinBox_editingFinished()
{
    QString pinyinLensText = pinyinLensSpinBox->text();
    if (pinyinLensText != "0")
        xx.Length = pinyinLensText;
}

void MainWindow::saveFile(const QString &file)
{
    if (file.isEmpty())
        return;
    QFile saveFile(file);
    if (!saveFile.exists()) {
        int ret = QMessageBox::warning(this, tr("Fcitx table editor"),
                                       tr("The file isn't exists,\n "
                                          "Do you want to continue?"),
                                       QMessageBox::Save | QMessageBox::Discard);
        if (ret == QMessageBox::Discard)
            return;
    }
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        QMessageBox::information(this, tr("Fcitx table editor"),
                                 tr("some error happened,\npls choose another filename to save"));
    QTextStream out(&saveFile);
    out.setCodec("UTF-8");
    if (!xx.KeyCode.isEmpty())
        out << "KeyCode=" << xx.KeyCode << "\n";
    if (!xx.Length.isEmpty())
        out << "Length=" << xx.Length << "\n";
    if (!xx.Pinyin.isEmpty())
        out << "Pinyin=" << xx.Pinyin << "\n";
    if (!xx.PinyinLength.isEmpty())
        out << "PinyinLength=" << xx.PinyinLength << "\n";
    if (!xx.Prompt.isEmpty())
        out << "Prompt=" << xx.Prompt << "\n";
    if (!xx.ConstructPhrase.isEmpty())
        out << "ConstructPhare=" << xx.ConstructPhrase << "\n";
    if (!xx.InvalidChar.isEmpty())
        out << "InvalidChar=" << xx.InvalidChar << "\n";
    if (!xx.wordRule.isEmpty()) {
        out << "[Rule]\n";
        QPair<QString, QStringList> tmp;
        foreach(tmp, xx.wordRule) {
            out << tmp.first << "=" << tmp.second.join("+") << "\n";
        }
    }
    if (!xx.wordList.isEmpty()) {
        out << "[Data]\n";
        QMap<WordDict, QString>::const_iterator i;
        foreach(i, xx.wordList) {
            out << i.key().get_key() << " " << i.value() << "\n";
        }
    }
    saveFile.close();
}
