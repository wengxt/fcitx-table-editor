#ifndef MYPROXYMODEL_H
#define MYPROXYMODEL_H

#include <QSortFilterProxyModel>

class MyProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    MyProxyModel(QObject *parent = 0);

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

};

#endif
