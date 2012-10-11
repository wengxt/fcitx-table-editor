#include "RuleModel.h"
#include <QtGui>

RuleModel::RuleModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void RuleModel::setParser(FileParser *fileParser)
{
    parserModel = fileParser;
    wordRule = &(parserModel->wordRule);
    modelheader << " ";
    for (int i = 0; i < fileParser->Length.toInt(); i++)
        modelheader << QString().setNum(i + 1);
}


int RuleModel::rowCount(const QModelIndex & /* parent */) const
{
  return wordRule->size();
}


int RuleModel::columnCount(const QModelIndex & /* parent */) const
{
  return wordRule->size() + 1;
}

QVariant RuleModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid()) {
    return QVariant();
  }

  if (role == Qt::TextAlignmentRole) {
    return int(Qt::AlignLeft | Qt::AlignVCenter);
  }
  if (role == Qt::DisplayRole && wordRule) {
    if (index.column() == 0)
       return wordRule->at(index.row()).first;
    else if (wordRule->at(index.row()).second.size() >= index.column())
       return wordRule->at(index.row()).second.at(index.column() - 1);
    }
  return QVariant();
}

bool RuleModel::setData(const QModelIndex &index, const QVariant &value , int role)
{
  if (!index.isValid()) {
    return false;
  }
  QList< QPair<QString, QStringList> >::iterator i = wordRule->begin();
  QStringList modifierRule;
  if (role == Qt::EditRole) {
      if (index.column() == 0)
          (*(i + index.row())).first = value.toString();
      else {
          modifierRule = (*(i + index.row())).second;
          modifierRule[index.column() - 1] =  value.toString();
          (*(i + index.row())).second = modifierRule;
      }
      emit dataChanged(index, index);
      return true;
  }
  return false;
}

QVariant RuleModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    return modelheader.at(section);
  }
  return QVariant();
}


Qt::ItemFlags RuleModel::flags(const QModelIndex & index) const
{
  Qt::ItemFlags flags = QAbstractItemModel::flags(index);
  if (index.isValid())
    flags |= Qt::ItemIsEditable;
  return flags;
}
