#include "FileParser.h"
#include <QtCore>

void FileParser::openFile(const QString &fileName)
{
  intoData = false;
  intoRole = false;
  wordRole.clear();

  KeyCode.clear();
  Length.clear();
  Pinyin.clear();
  PinyinLength.clear();
  Prompt.clear();
  ConstructPhrase.clear();
  InvalidChar.clear();

  keymap.clear();
  wordList.clear();
  validKey.clear();

  if (fileName.isEmpty())
      return;
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;
  
  QTextStream in(&file);
  in.setCodec("UTF-8");
  QString line;
  while (!in.atEnd()) {
    line = in.readLine();
    if (line.isEmpty())
      continue;

    processLine(line);
  }
  file.close();
}

void FileParser::pfall()
{
  QTextStream out(stdout);
  out.setCodec("UTF-8");
  out << KeyCode << endl << Length;
}
void FileParser::processLine(const QString &text)
{
  QStringList keyVal;
  if (intoData) {
    keyVal = readKeyVal(text);
    if (keyVal.size() <= 1)
      return;
    saveWordDic(keyVal);
    return;
  }

  QString section = readSection(text);
  if (!section.isEmpty()) {
    if (section == QString::fromUtf8("数据") || section == "Data") {
      intoData = true;
      intoRole = false;
      return;
    }
    if (section == QString::fromUtf8("组词规则") || section == "Rule") {
      intoRole = true;
    }
  }

  QStringList conf = readConf(text);
  if (!conf.isEmpty()) {
    if (intoRole == true) {
      QStringList tmp = conf.at(1).split('+');
      wordRole.append(qMakePair(conf.at(0), tmp));
    }
    if (conf.at(0) == QString::fromUtf8("键码") || conf.at(0) == "KeyCode") {
      KeyCode = conf.at(1);
      return;
    }
    if (conf.at(0) == QString::fromUtf8("码长") || conf.at(0) == "Length") {
      Length = conf.at(1);
      return;
    }
    if (conf.at(0) == QString::fromUtf8("拼音") || conf.at(0) == "Pinyin") { 
      Pinyin = conf.at(1);
      return;
    }
    if (conf.at(0) == QString::fromUtf8("拼音长度") || conf.at(0) == "PinyinLength") { 
      PinyinLength = conf.at(1);
      return;
    }
    if (conf.at(0) == QString::fromUtf8("提示") || conf.at(0) == "Prompt") { 
      Prompt = conf.at(1);
      return;
    }
    if (conf.at(0) == QString::fromUtf8("构词") || conf.at(0) == "ConstructPhrase") { 
      ConstructPhrase = conf.at(1);
      return;
    }
    if (conf.at(0) == QString::fromUtf8("规避字符") || conf.at(0) == "InvalidChar") { 
      InvalidChar = conf.at(1);
      return;
    }
  }
}

QStringList FileParser::readKeyVal(const QString &text)
{
  QStringList oneKeyVal;
  QString splitWhiteSpace = text;
  splitWhiteSpace.replace('\t', ' ');
  if (splitWhiteSpace.contains(' '))
    oneKeyVal = splitWhiteSpace.split(' ',QString::SkipEmptyParts);
  return oneKeyVal;
}

QStringList FileParser::readConf(const QString &text)
{
  QStringList conf;
  if (text.contains('=')) {
    conf = text.split('='); // in this time, conf has 2 str at least
    conf.replaceInStrings(" ", "");
  }
  return conf;
}

QString FileParser::readSection(const QString &text)
{
  QString sectionName;
  
  QString trimWhite = text;
  trimWhite.remove(QChar(' '));
  if ((trimWhite.at(0) == '[') &&
      (trimWhite.at(trimWhite.size() -1) == ']')) {
    sectionName = trimWhite.mid(1);
    sectionName = sectionName.left(sectionName.size() - 1);
  }
  return sectionName;
}

void FileParser::saveWordDic(const QStringList &keyvalue)
{
    QString key = keyvalue.at(0);
    QString value = keyvalue.at(1);
    int i;
    for (i = 1; i < INT_MAX; i++) {
        if (keymap.find(key + QString::number(i)) == keymap.end()) {
            keymap.insert((key + QString::number(i)), value);
            break;
        }
    }
    if (i == 1)
        validKey.insert(key);
    if (i == INT_MAX)
        qDebug() << "fuck the key,it's too much";
    wordList.append(qMakePair(key, i));
}
