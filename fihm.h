#ifndef FIHM_H
#define FIHM_H

#define PERSONNE 5000

#include <QMainWindow>
#include <QtWebKit/QWebView>
#include <QUrl>
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QObject>

#include "cbdd.h"
#include "ccapteur.h"

namespace Ui {
class fihm;
}

class fihm : public QMainWindow
{
    Q_OBJECT

public:
    explicit fihm(QWidget *parent = 0);
    ~fihm();
    CBdd bdd;
    CCapteur capteur;
    QString getMacAddress();

private:
    Ui::fihm *ui;
    QString Zone_Id;
    QString mac_Address;
    QString Url;
    bool mEtatTele;
    QTimer *timerPresence;
    QTimer *timerChrono;
    QTimer *timerHeure;

private slots:
    void timerRefresh();
    void timerTemperatureTimeout();
    void timerPresenceTimeout();
    void timerChronoTimeout();
    void timerUrgencyTimeout();
};

#endif // FIHM_H
