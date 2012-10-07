#ifndef _FILEPARSER_H_
#define _FILEPARSER_H_

#include <QString>
#include <QStringList>
#include <QMultiMap>
#include <QPair>
#include <QFile>

class FileParser
{
 public:
  void openFile(QString fileName);
  void pfall(void);
  QString KeyCode;
  QString Length;
  QString pinyinPrefix;
  QString pinyinLens;
  QList< QPair<QString, QStringList> > wordRole;
  QList< QPair<QString, QString> > keymap;


 private:
  void processLine(const QString text);
  QStringList readKeyVal(const QString text);
  QStringList readConf(const QString text);
  QString readSection(const QString text);

  bool intoData;
  bool intoRole;

};

#endif /* _FILEPARSER_H_ */
