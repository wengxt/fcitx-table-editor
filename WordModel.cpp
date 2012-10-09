#include "WordModel.h"
#include <QtGui>

WordModel::WordModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    modelheader << "Key" << "Word";
}

void WordModel::chooseParser(FileParser *fileParser)
{
    parserModel = fileParser;
    keymap = &(fileParser->keymap);
    validKey = &(fileParser->validKey);
    wordList = &fileParser->wordList;
    modelheader << "Key" << "Word";
}

int WordModel::rowCount(const QModelIndex & /* parent */) const
{
  return keymap->size();
}


int WordModel::columnCount(const QModelIndex & /* parent */) const
{
  return 2;
}

QVariant WordModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid()) {
    return QVariant();
  }

  if (role == Qt::TextAlignmentRole) {
    return int(Qt::AlignLeft | Qt::AlignVCenter);
  }
  if (role == Qt::DisplayRole && index.row() < wordList->size()) {
    if (index.column() == 0)
       return wordList->at(index.row()).first;
    else if (index.column() == 1)
       return (*keymap)[wordList->at(index.row()).first
               + QString::number(wordList->at(index.row()).second)];
    }
  return QVariant();
}

bool WordModel::setData(const QModelIndex &index, const QVariant &/*value*/ , int role)
{
  if (!index.isValid()) {
    return false;
  }


  if (role == Qt::EditRole) {
      if (index.column() == 0) {
      }
      else if (index.column() == 1) {
      }
      emit dataChanged(index, index);
      return true;
  }
  return false;
}

QVariant WordModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    return modelheader.at(section);
  }
  return QVariant();
}


Qt::ItemFlags WordModel::flags(const QModelIndex & index) const
{
  Qt::ItemFlags flags = QAbstractItemModel::flags(index);
  if (index.isValid())
    flags |= Qt::ItemIsEditable;
  return flags;
}

bool WordModel::isWordDicExists(QString key, int index)
{
    if (keymap->find(key + QString::number(index)) == keymap->end())
        return false;
    else
        return true;
}
