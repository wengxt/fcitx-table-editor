#ifndef _FILEPARSER_H_
#define _FILEPARSER_H_

#include "WordDict.h"
#include <QString>
#include <QStringList>
#include <QMap>
#include <QPair>
#include <QSet>

class FileParser
{
 public:
  void openFile(const QString &fileName);
  void pfall(void);
  void saveWordDic(const QStringList &keyvalue);

  // follow var are MB template,
  // https://github.com/fcitx/fcitx/blob/master/tools/mb2txt.c
  QString KeyCode;
  QString Length;
  QString Pinyin;
  QString PinyinLength;
  QString Prompt;
  QString ConstructPhrase;
  QString InvalidChar;

  QList< QPair<QString, QStringList> > wordRule;
  QMap<WordDict, QString> keymap;
  QList< QMap<WordDict, QString>::const_iterator > wordList;

  QSet<QString> validKey;

 private:
  void processLine(const QString &text);
  QStringList readKeyVal(const QString &text);
  QStringList readConf(const QString &text);
  QString readSection(const QString &text);

  bool intoData;
  bool intoRule;

};

#endif /* _FILEPARSER_H_ */
