#ifndef BULLS_AND_COWS_GAME_H
#define BULLS_AND_COWS_GAME_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QValidator>
#include <QGridLayout>
#include "recordlist.h"

class Bulls_and_Cows_Game : public QWidget
{
    Q_OBJECT
    friend class RecordList;
public:
    Bulls_and_Cows_Game(QWidget *parent = nullptr);
    ~Bulls_and_Cows_Game();

private slots:
    void nwGame();
    void recShow();
    void checkNum();
    void getInput();
signals:
    void personInfo(QString name, int attemps);

private:
    QTableWidget *gameTable;
    QLabel *status;
    QLineEdit *input;
    QPushButton *nwgButton;
    QPushButton *recButton;
    QPushButton *chkButton;
    QLabel *inLabel;
    QGridLayout *grid;
    QValidator * val;

    RecordList *records;

    QString number;

    bool numberRuleCheck(QString n);
    bool validate();
    void winning();
    void closeEvent(QCloseEvent *event);
};
#endif // BULLS_AND_COWS_GAME_H
