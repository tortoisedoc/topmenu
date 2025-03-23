
#include <QObject>
#include "foodmodel.h"

FoodModel::FoodModel(QObject *parent) : QAbstractListModel(parent) {}

int FoodModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return foods.count();
}

QVariant FoodModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= foods.count())
        return QVariant();

    const FoodItem &food = foods[index.row()];

    if (role == NameRole)
        return food.name;
    else if (role == GroupRole)
        return food.group;

    return QVariant();
}

QHash<int, QByteArray> FoodModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[GroupRole] = "group";
    return roles;
}

void FoodModel::addFood(const QString &name, const QString &group) {
    beginInsertRows(QModelIndex(), foods.count(), foods.count());
    foods.append({name, group});
    endInsertRows();
}

void FoodModel::removeFood(int index) {
    if (index < 0 || index >= foods.count()) return;
    beginRemoveRows(QModelIndex(), index, index);
    foods.removeAt(index);
    endRemoveRows();
}

void FoodModel::editFood(int index, const QString &newName, const QString &newGroup) {
    if (index < 0 || index >= foods.count()) return;
    foods[index].name = newName;
    foods[index].group = newGroup;
    emit dataChanged(this->index(index, 0), this->index(index, 0));
}
