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
  WordModel(QObject *parent = 0);
  void setParser(FileParser *fileParser);
  int rowCount(const QModelIndex &parent) const;
  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;

 private:
  QStringList modelheader;
  FileParser *parserModel;
  QSet<QString> *validKey;
  QMap<WordDict, QString> *keymap;
  QList< QMap<WordDict, QString>::const_iterator > *wordList;
};

#endif // WORDMODEL_H
