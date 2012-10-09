#ifndef WORDMODEL_H
#define WORDMODEL_H

#include "FileParser.h"
#include <QStringList>
#include <QAbstractTableModel>
#include <QSortFilterProxyModel>
#include <QPair>

class WordModel: public QAbstractTableModel
{
  Q_OBJECT

 public:
  WordModel(FileParser *fileParser, QObject *parent = 0);
  int rowCount(const QModelIndex &parent) const;
  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;

 private:
  bool isWordDicExists(QString key, int index);
  QStringList modelheader;
  FileParser *parserModel;
  QSet<QString> *validKey;
  QMap<QString, QString> *keymap;
  QList< QPair<QString, int> > *wordList;
};

#endif // WORDMODEL_H
