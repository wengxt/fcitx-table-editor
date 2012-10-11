#ifndef FILTERPROXYMODEL_H
#define FILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class FilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    FilterProxyModel(QObject *parent = 0);

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

};

#endif
