#include "RoleModel.h"
#include <QtGui>

RoleModel::RoleModel(FileParser *fileParser, QObject *parent)
    : QAbstractTableModel(parent)
{
    parserModel = fileParser;
    wordRole = &(parserModel->wordRole);
    modelheader << " ";
    for (int i = 0; i < fileParser->Length.toInt(); i++)
        modelheader << QString().setNum(i + 1);
}

int RoleModel::rowCount(const QModelIndex & /* parent */) const
{
  return parserModel->Length.toInt() - 1;
}


int RoleModel::columnCount(const QModelIndex & /* parent */) const
{
  return parserModel->Length.toInt() + 1;
}

QVariant RoleModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid()) {
    return QVariant();
  }

  if (role == Qt::TextAlignmentRole) {
    return int(Qt::AlignLeft | Qt::AlignVCenter);
  }
  if (role == Qt::DisplayRole) {
    if (index.column() == 0)
       return wordRole->at(index.row()).first;
    else if (wordRole->at(index.row()).second.size() >= index.column())
       return wordRole->at(index.row()).second.at(index.column() - 1);
    }
  return QVariant();
}

bool RoleModel::setData(const QModelIndex &index, const QVariant &value , int role)
{
  if (!index.isValid()) {
    return false;
  }
  QList< QPair<QString, QStringList> >::iterator i = wordRole->begin();
  QStringList modifierRole;
  if (role == Qt::EditRole) {
      if (index.column() == 0)
          (*(i + index.row())).first = value.toString();
      else {
          modifierRole = (*(i + index.row())).second;
          modifierRole[index.column() - 1] =  value.toString();
          (*(i + index.row())).second = modifierRole;
      }
      emit dataChanged(index, index);
      return true;
  }
  return false;
}

QVariant RoleModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    return modelheader.at(section);
  }
  return QVariant();
}


Qt::ItemFlags RoleModel::flags(const QModelIndex & index) const
{
  Qt::ItemFlags flags = QAbstractItemModel::flags(index);
  if (index.isValid())
    flags |= Qt::ItemIsEditable;
  return flags;
}
