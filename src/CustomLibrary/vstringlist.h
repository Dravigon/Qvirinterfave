#ifndef VSTRINGLIST_H
#define VSTRINGLIST_H
#include <QObject>
#include <QDebug>
#include <QStandardItemModel>

class vstringList:public QStandardItemModel
{
  Q_OBJECT
public:
  vstringList(QObject *parent);
      enum StringRole {
          ValueRole = Qt::UserRole+1
      };
      Q_INVOKABLE void append(QString string){
        QStandardItem* item=new QStandardItem();
        item->setData(string,ValueRole);
        this->appendRow(item);
      }
      Q_INVOKABLE QString at(int i){
        return this->data(this->index(i,0,QModelIndex())).toString();
      }
      Q_INVOKABLE bool remove(int index){
        return this->removeRow(1,this->index(index,0,QModelIndex()));
      }
      Q_INVOKABLE int size(){
          return rowCount();
      }
      Q_INVOKABLE bool isEmpty(){
        return this->size() <= 0;
      }
      virtual QString xml(){
        return "";
      }
protected:
    QHash<int, QByteArray> roleNames() const {
        QHash<int, QByteArray> roles;
        roles[ValueRole]="name";
        return roles;
    }
};

#endif // VSTRINGLIST_H
