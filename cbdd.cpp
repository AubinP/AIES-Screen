#include "cbdd.h"
#include "ccapteur.h"


CBdd::CBdd()
{
    QString databaseType = "QMYSQL";
    QString databaseHostname = "192.168.2.78";
    QString databaseName = "aies2016";
    QString databaseUsername = "aies2016";
    QString databasePassword = "aies2016";

    Aies_bdd =QSqlDatabase::addDatabase(databaseType);
    Aies_bdd.setDatabaseName(databaseName);
    Aies_bdd.setHostName(databaseHostname);
    Aies_bdd.setUserName(databaseUsername);
    Aies_bdd.setPassword(databasePassword);
}

CBdd::~CBdd()
{

}

QString CBdd::getRpi()
{
    fullRpiData = "";
    if(!Aies_bdd.open())
    {
        qDebug("Ouverture de la base de donnée impossible");
        return "-1";
    }
    else
    {
        QSqlQuery Aies_query("SELECT * FROM rpi;");
        while(Aies_query.next())
        {
            QString nameRpi = Aies_query.value(1).toString();
            QString ipRpi = Aies_query.value(2).toString();
            QString macRpi = Aies_query.value(3).toString();
            QString zoneRpi = Aies_query.value(4).toString();
            fullRpiData += nameRpi + ";" + ipRpi + ";" + macRpi + ";" + zoneRpi + ";";
        }
        Aies_bdd.close();
        return fullRpiData;
    }
}

QString CBdd::getZone(QString mac)
{
    fullRpiData = "";
    if(!Aies_bdd.open())
    {
        qDebug("Ouverture de la base de donnée impossible");
        return "-1";
    }
    else
    {
        query = "SELECT zone_id FROM rpi WHERE mac = '"+mac+"';";
        QSqlQuery Aies_query(query);
        while(Aies_query.next())
        {
            QString this_Zone = Aies_query.value(0).toString();
            fullRpiData = this_Zone;
        }
        Aies_bdd.close();
        return fullRpiData;
    }
}

void CBdd::setCapteurs(QString Query)
{
    fullRpiData = "";
    if(!Aies_bdd.open())
    {
        qDebug("Ouverture de la base de donnée impossible");
    }
    else
    {
        QSqlQuery Aies_query;
        Aies_query.exec(Query);
        Aies_bdd.close();
    }
}

QString CBdd::getCurrentrpi(QString macaddr)
{
    fullRpiData = "";
    if(!Aies_bdd.open())
    {
        qDebug("Ouverture de la base de donnée impossible");
        return "-1";
    }
    else
    {
        query = "SELECT name FROM rpi WHERE mac = '"+macaddr+"';";
        QSqlQuery Aies_query(query);
        while(Aies_query.next())
        {
            QString this_Zone = Aies_query.value(0).toString();
            fullRpiData = this_Zone;
        }
        Aies_bdd.close();
        return fullRpiData;
    }
}
