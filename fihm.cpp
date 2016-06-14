#include "fihm.h"
#include "ui_fihm.h"
#include "cbdd.h"
#include "ccapteur.h"

fihm::fihm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fihm)
{
    ui->setupUi(this);

    // Initialisation des paramètres de bases
    mEtatTele = true;   // Télé allumée au départ
    mac_Address = getMacAddress();  // Acquisition de la zone selon l'adresse mac
    Zone_Id = bdd.getZone(mac_Address);
    currentName = bdd.getCurrentrpi(getMacAddress());   // Nom de la rpi

    // Timer de décompte de non présence
    timerChrono = new QTimer();
    timerChrono->connect(timerChrono, SIGNAL(timeout()), this, SLOT(onTimerChrono()));

    // Timer général
    timer = new QTimer();
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(onTimerHeure()));
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(onTimerTemperature()));
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(onTimerPresence()));
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(onTimerBdd()));
    timer->start(1000);

    // Récupére les pages webs
    this->ui->webViewFlash->load(QUrl("http://192.168.2.78/flashstarter.php"));
    Url = "http://192.168.2.78/starterzone" + Zone_Id + ".php";
    this->ui->webViewStarter->load(QUrl(Url));
}



// Destructeur
fihm::~fihm()
{
    delete timer;
    delete timerChrono;
    delete ui;
}




// Récupére l'adresse mac de la carte
QString fihm::getMacAddress()
{
    char buffer[1000];
    FILE *file_macAddress;
    if ((file_macAddress=fopen("/sys/class/net/eth0/address","r"))==NULL){
        exit(1);
    } // if lecture du fichier contenant l'adresse mac
    fscanf(file_macAddress,"%[^\n]",buffer);
    fclose(file_macAddress);
    return buffer; // renvoie l'adresse mac
}




// Récupere l'heure actuel
void fihm::onTimerHeure()
{
    QTime Heure;
    Heure = QTime::currentTime();
    if (ui->lbPoints->isVisible())
        ui->lbPoints->setVisible(false);    //
    else                                    // clignotement des 2 points de l'heure
        ui->lbPoints->setVisible(true);     //
    ui->lbHeure->setText(Heure.toString("hh"));     // affiche l'heure
    ui->lbMinute->setText(Heure.toString("mm"));    // affiche les minutes
}




// Affiche la temperature
void fihm::onTimerTemperature()
{
      float temp = capteur.getTemp();
      this->ui->lbTemp->setText(QString::number(temp));
}




// Gestion de la mise en veille de la télé
void fihm::onTimerPresence()
{
    bool test;
    test = capteur.getPresence();
    if(!test)  // si personne non présente
    {
        if (!timerChrono->isActive())  // activation chrono durée d'absence
            timerChrono->start(PERSONNE);
    } // if test
    else  // si personne présente
    {
        if (timerChrono->isActive()) {
            timerChrono->stop();
        } // if active
        if (!mEtatTele) {
            capteur.putinOn();
            mEtatTele = true;
        } // if mEtatTele
    } // else si personne présente
}  // timerPresence




// Mise en veille
void fihm::onTimerChrono()
{
    mEtatTele = false;  // télé éteinte
    capteur.putinStandby();
    timerChrono->stop();
}




// Ecrire les données capteurs dans la Bdd
void fihm::onTimerBdd()
{
    Temp = capteur.getTemp();
    QString realtemp = QString::number(Temp);
    Presence = capteur.getPresence();
    if (currentName.compare("rpi_accueil")) {
        bdd.setCapteurs("UPDATE sensors SET temperature='"+realtemp+"', presence_rpi1='"+(Presence?"1":"0")+"';");
    } // rpi_accueil
    if (currentName.compare("rpi_self")) {
        bdd.setCapteurs("UPDATE sensors SET temperature='"+realtemp+"', presence_rpi2='"+(Presence?"1":"0")+"';");
    } // rpi_self
    if (currentName.compare("rpi_vs")) {
        bdd.setCapteurs("UPDATE sensors SET temperature='"+realtemp+"', presence_rpi3='"+(Presence?"1":"0")+"';");
    } // rpi_vs
    if (currentName.compare("rpi_dir")) {
        bdd.setCapteurs("UPDATE sensors SET temperature='"+realtemp+"', presence_rpi4='"+(Presence?"1":"0")+"';");
    } // rpi_dir
    if (currentName.compare("rpi_prof")) {
        bdd.setCapteurs("UPDATE sensors SET temperature='"+realtemp+"', presence_rpi5='"+(Presence?"1":"0")+"';");
    } // rpi_prof
}
