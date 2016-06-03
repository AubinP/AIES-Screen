#ifndef CBDD_H
#define CBDD_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlError>

#include "ccapteur.h"

class CBdd
{
public:
    CBdd();
    ~CBdd();
    QString getRpi();
    QString getRefreshTime();
    QString getUrgencyState();
    QString getZone(QString mac);
    QString savePresence();
    QString saveTemperature();
private:
    QSqlDatabase Aies_bdd;
    QSqlQuery Aies_query;

    float temp;
    bool presence;

    QString query;
    QString databaseType;
    QString databaseHostname;
    QString databaseName;
    QString databaseUsername;
    QString databasePassword;

    QString fullRpiData;
};

#endif // CBDD_H
