#include "qubeplus.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QubePlus w;
    w.show();
    return a.exec();
}
