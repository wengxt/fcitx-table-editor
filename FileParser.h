#ifndef _FILEPARSER_H_
#define _FILEPARSER_H_

#include <QString>
#include <QStringList>
#include <QMultiMap>
#include <QPair>
#include <QSet>

class FileParser
{
 public:
  void openFile(QString fileName);
  void pfall(void);

  // follow var are MB template,
  // https://github.com/fcitx/fcitx/blob/master/tools/mb2txt.c
  QString KeyCode;
  QString Length;
  QString Pinyin;
  QString PinyinLength;
  QString Prompt;
  QString ConstructPhrase;
  QString InvalidChar;

  QList< QPair<QString, QStringList> > wordRole;
  QMap<QString, QString> keymap; // index is the valid key repate times,
                                 // keymap.key() = key + QString(index), key.value() = value
  QList< QPair<QString, int> > wordList;  //save the key and index
  QSet<QString> validKey;

 private:
  void processLine(const QString text);
  QStringList readKeyVal(const QString text);
  QStringList readConf(const QString text);
  QString readSection(const QString text);
  void saveWordDic(QStringList keyvalue);

  bool intoData;
  bool intoRole;

};

#endif /* _FILEPARSER_H_ */
