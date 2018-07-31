#include "public.h"
#include "mainwindow.h"
#include"dialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog dlg;
    dlg.show();

    return a.exec();
}
