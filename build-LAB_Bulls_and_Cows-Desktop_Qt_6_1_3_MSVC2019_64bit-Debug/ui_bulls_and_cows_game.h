/********************************************************************************
** Form generated from reading UI file 'bulls_and_cows_game.ui'
**
** Created by: Qt User Interface Compiler version 6.1.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BULLS_AND_COWS_GAME_H
#define UI_BULLS_AND_COWS_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Bulls_and_Cows_Game
{
public:

    void setupUi(QWidget *Bulls_and_Cows_Game)
    {
        if (Bulls_and_Cows_Game->objectName().isEmpty())
            Bulls_and_Cows_Game->setObjectName(QString::fromUtf8("Bulls_and_Cows_Game"));
        Bulls_and_Cows_Game->resize(450, 392);

        retranslateUi(Bulls_and_Cows_Game);

        QMetaObject::connectSlotsByName(Bulls_and_Cows_Game);
    } // setupUi

    void retranslateUi(QWidget *Bulls_and_Cows_Game)
    {
        Bulls_and_Cows_Game->setWindowTitle(QCoreApplication::translate("Bulls_and_Cows_Game", "Bulls_and_Cows_Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Bulls_and_Cows_Game: public Ui_Bulls_and_Cows_Game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BULLS_AND_COWS_GAME_H
