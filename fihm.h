#ifndef FIHM_H
#define FIHM_H

#define PERSONNE 10000

#include <QMainWindow>
#include <QtWebKit/QWebView>
#include <QUrl>
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QObject>
#include <QDebug>

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
    QString currentName;
    QString Url;
    bool mEtatTele;
    float Temp;
    bool Presence;
    QTimer *timerPresence;
    QTimer *timerChrono;
    QTimer *timer;


private slots:
    void onTimerHeure();
    void onTimerTemperature();
    void onTimerPresence();
    void onTimerChrono();
    void onTimerBdd();
};

#endif // FIHM_H
