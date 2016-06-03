#include <QApplication>
#include "fihm.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fihm w;
    w.showFullScreen();
    w.show();

    return a.exec();
}
