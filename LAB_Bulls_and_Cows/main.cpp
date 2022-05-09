#include "bulls_and_cows_game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Bulls_and_Cows_Game w;
    w.setWindowTitle("Быки и коровы");
    w.resize(400,450);
    w.show();
    return a.exec();
}
