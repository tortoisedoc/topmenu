#pragma once

#include <QAbstractListModel>
#include <QStringList>

struct FoodItem {
    QString name;
    QString group;
};

class FoodModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        GroupRole
    };

    explicit FoodModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addFood(const QString &name, const QString &group);
    Q_INVOKABLE void removeFood(int index);
    Q_INVOKABLE void editFood(int index, const QString &newName, const QString &newGroup);

private:
    QList<FoodItem> foods;
};

