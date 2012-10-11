#include "WordModel.h"
#include <QtGui>

WordModel::WordModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    modelheader << "Key" << "Word";
}

void WordModel::setParser(FileParser *fileParser)
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
      QMap<WordDict, QString>::const_iterator i = wordList->at(index.row());
    if (index.column() == 0)
       return i.key().get_key();
    else if (index.column() == 1) {
        return i.value();
    }
  }
  return QVariant();
}

bool WordModel::setData(const QModelIndex &index, const QVariant &value , int role)
{
  if (!index.isValid()) {
    return false;
  }


  if (role == Qt::EditRole) {
      QStringList wordKeyValue;
      QString modifiedValue = value.toString();
      QMap<WordDict, QString>::const_iterator i = wordList->at(index.row());
      WordDict tmp(i.key().get_key(), i.key().get_index());
      if (index.column() == 0 && tmp.get_key() != modifiedValue) {
        wordKeyValue << modifiedValue << i.value();
        parserModel->saveWordDic(wordKeyValue);
      }
      else if (index.column() == 1 && modifiedValue != i.value()) {
          wordKeyValue << tmp.get_key() << modifiedValue;
          parserModel->saveWordDic(wordKeyValue);
      }
      else
          return false;
      keymap->remove(tmp);
      wordList->clear();
      for (i = keymap->constBegin(); i != keymap->constEnd(); ++i) {
          wordList->append(i);
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
