#include "widget.h"
#include <QApplication>
#include "denglu.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   denglu d;
   d.show();

    return a.exec();
}
