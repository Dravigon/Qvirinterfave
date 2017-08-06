#ifndef  Contoller_H
#define  Contoller_H

#include <QObject>
#include <QString>

class  Contoller : public QObject
{
    Q_OBJECT


public:
    explicit  Contoller(QObject *parent = nullptr);

    Q_INVOKABLE long maxBandwidth(){
        return  1000;
    }
    Q_INVOKABLE int getMaxPort(){
        return 5000;
    }


signals:
    void userNameChanged();

private:
    QString m_userName;
};

#endif //  Contoller_H
