#ifndef  _ROLEMODEL_H_
#define  _ROLEMODEL_H_

#include <QStringList>
#include <QAbstractTableModel>
#include "FileParser.h"

class RoleModel: public QAbstractTableModel
{
  Q_OBJECT

 public:
  RoleModel(QObject *parent = 0);
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
  QList< QPair<QString, QStringList> > *wordRole;
};

#endif   /* ----- #ifndef _ROLEMODEL_h ---- */
