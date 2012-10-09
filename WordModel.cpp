#include "WordModel.h"
#include <QtGui>

WordModel::WordModel(FileParser *fileParser, QObject *parent)
    : QAbstractTableModel(parent)
{
    parserModel = fileParser;
    keymap = &(fileParser->keymap);
    validKey = &(fileParser->validKey);
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
  if (role == Qt::DisplayRole && index.row() < keymap->size()) {
    if (index.column() == 0)
       return wordKeyMap->at(index.row())->get_key();
    else if (index.column() == 1)
       return wordKeyMap->at(index.row())->get_value();
    }
  return QVariant();
}

bool WordModel::setData(const QModelIndex &index, const QVariant &value , int role)
{
  if (!index.isValid()) {
    return false;
  }


  if (role == Qt::EditRole) {
      if (index.column() == 0)
          wordKeyMap->at(index.row())->set_key(value.toString());
      else if (index.column() == 1)
          wordKeyMap->at(index.row())->set_value(value.toString());
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
