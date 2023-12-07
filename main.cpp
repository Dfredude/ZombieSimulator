#include "ZombieSim.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ZombieSim w;
    w.show();
    return a.exec();
}
