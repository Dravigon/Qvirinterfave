#ifndef SQLQUERYMODEL_H
#define SQLQUERYMODEL_H

#include <QSqlQueryModel>

class SqlQueryModel : public QSqlQueryModel
{
  Q_OBJECT

public:
  explicit SqlQueryModel(QObject *parent = 0);
  Q_INVOKABLE QVariantMap get(int index);

  /* set Query overloading
   *1)Give a query string and the database to query from
   * void setQuery(const QString &query, const QSqlDatabase &db = QSqlDatabase());
   * 2)Give the QSqlQuery object to setQuery
   *void setQuery(const QSqlQuery &query);
   */
  void setQuery(const QString &query, const QSqlDatabase &db = QSqlDatabase());
  void setQuery(const QSqlQuery &query);
  QVariant data(const QModelIndex &index, int role) const;
  QHash<int, QByteArray> roleNames() const {	return m_roleNames;	}

private:
  void generateRoleNames();//generates role name for the given sql table
  QHash<int, QByteArray> m_roleNames;
};

#endif // SQLQUERYMODEL_H
