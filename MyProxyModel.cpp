#include "MyProxyModel.h"

MyProxyModel::MyProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}


bool MyProxyModel::lessThan(const QModelIndex &left,
                                      const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);
    return leftData.toString() < rightData.toString();
}
