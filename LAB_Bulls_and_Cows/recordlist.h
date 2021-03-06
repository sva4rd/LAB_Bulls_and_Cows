#ifndef RECORDLIST_H
#define RECORDLIST_H

#include <QWidget>
#include <QTableWidget>
#include <QFile>

class RecordList : public QWidget
{
    Q_OBJECT
    friend class Bulls_and_Cows_Game;
private:
    explicit RecordList(/*QWidget *parent = nullptr*/);
    ~RecordList();
    QTableWidget *recordsTable;
    bool isChange;
    void tableSettings(QTableWidget *table);
    void writeInFile();
private slots:
    void nwRezult(QString name, int attemps);
};

#endif // RECORDLIST_H
