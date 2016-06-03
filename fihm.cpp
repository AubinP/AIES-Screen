#include "fihm.h"
#include "ui_fihm.h"
#include "cbdd.h"
#include "ccapteur.h"

fihm::fihm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fihm)
{
    ui->setupUi(this);

    mEtatTele = true;  // allumé au départ
    //Vérifie la zone de lecture en fonction de l'adresse mac
    mac_Address = getMacAddress();
    Zone_Id = bdd.getZone(mac_Address);

    //Timer pour rafraichir l'heure
    timerHeure = new QTimer();
    timerHeure->connect(timerHeure, SIGNAL(timeout()), this, SLOT(timerRefresh()));
    timerHeure->connect(timerHeure, SIGNAL(timeout()), this, SLOT(timerTemperatureTimeout()));
    timerHeure->connect(timerHeure, SIGNAL(timeout()), this, SLOT(timerUrgencyTimeout()));
    timerHeure->start(1000);

    //Url = "http://192.168.2.78/starterzone" + Zone_Id + ".php";
    this->ui->webViewStarter->load(QUrl("http://192.168.2.78/starterzone1.php"));
    //this->ui->webViewStarter->load(QUrl(Url));
    this->ui->webViewFlash->load(QUrl("http://192.168.2.78/flash.php"));

    //Timer de mesure de non présence
    timerChrono = new QTimer();
    timerChrono->connect(timerChrono, SIGNAL(timeout()), this, SLOT(timerChronoTimeout()));

    //Timer de la présence
    timerPresence = new QTimer();
    timerPresence->connect(timerPresence, SIGNAL(timeout()), this, SLOT(timerPresenceTimeout()));
    timerPresence->start(1000);
}

fihm::~fihm()
{
    delete timerHeure;
    delete timerPresence;
    delete timerChrono;
    delete ui;
}

//Récupére l'adresse mac de la carte
QString fihm::getMacAddress()
{
    char buffer[1000];
    FILE *file_macAddress;
    if ((file_macAddress=fopen("/sys/class/net/eth0/address","r"))==NULL){
        exit(1);
    }
    fscanf(file_macAddress,"%[^\n]",buffer);
    fclose(file_macAddress);
    return buffer;
}

//Récupere le temps actuel
void fihm::timerRefresh()
{
    QTime Heure;
    Heure = QTime::currentTime();
    if (ui->lbPoints->isVisible())
        ui->lbPoints->setVisible(false);
    else
        ui->lbPoints->setVisible(true);
    ui->lbHeure->setText(Heure.toString("hh"));
    ui->lbMinute->setText(Heure.toString("mm"));
}

//Affiche la temperature
void fihm::timerTemperatureTimeout()
{
      float temp = capteur.getTemp();
      this->ui->lbTemp->setText(QString::number(temp));
}

void fihm::timerPresenceTimeout()
{
    bool test;
    test = capteur.getPresence();
    if(!test)  // si personne présente
    {
        if (!timerChrono->isActive())  // activation chrono durée d'absence
            timerChrono->start(PERSONNE);
    } // if test
    else  // ya quelqu'un
    {
        if (timerChrono->isActive()) {
            timerChrono->stop();
        } // if active
        if (!mEtatTele) {
            capteur.putinOn();
            mEtatTele = true;
        } // if mEtatTele
    } // else ya qqqun
}  // timerPresenceTimeout

void fihm::timerChronoTimeout()
{
    // mettre la tele en veille
    mEtatTele = false;
    capteur.putinStandby();
    timerChrono->stop();
}

void fihm::timerUrgencyTimeout()
{

}

