#ifndef VSTANDARDITEMMODEL_H
#define VSTANDARDITEMMODEL_H
#include <QObject>
#include <QDebug>
#include <QStandardItemModel>

class VStandardItemModel:public QStandardItemModel
{
public:
    VStandardItemModel();
    VStandardItemModel(QObject *parent);

    Q_INVOKABLE void set_data(int i,QString value,QString role){
        qDebug()<<role<<":"<<value;
        setData(index(i,0),value,roleNames().key(role.toUtf8()));
    }
    Q_INVOKABLE int size(){
        return rowCount();
    }
    Q_INVOKABLE void add(QStandardItem* item){
        appendRow(item);
        qDebug()<<"\n\n""\n\n";
    }
    Q_INVOKABLE bool removeat(int i){
        return removeRow(i);
    }
    Q_INVOKABLE bool removelast(){
        return removeRow(rowCount());
    }
};

#endif // VSTANDARDITEMMODEL_H
