#include "recordlist.h"
#include <QHeaderView>
#include <QLayout>
#include <QFile>

RecordList::RecordList(/*QWidget *parent*/)
    //: QWidget{parent}
{
    recordsTable = new QTableWidget(0, 2, this);
    recordsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    recordsTable->setSelectionMode(QAbstractItemView::NoSelection);
    recordsTable->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    QHeaderView* recHeader = recordsTable->horizontalHeader();
    recHeader->setSectionResizeMode(QHeaderView::Stretch);

    QStringList recHeaderList;
    recHeaderList << "Попыток" << "Имя";
    recordsTable->setHorizontalHeaderLabels(recHeaderList);
    recHeaderList.clear();
    recHeaderList << "1";
    recordsTable->setVerticalHeaderLabels(recHeaderList);

    QVBoxLayout *recLayout = new QVBoxLayout(this);
    recLayout->addWidget(recordsTable);

    QFile file("data.dat");
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        QString item;
        while(!in.atEnd())
        {
            item = in.readLine();

            QTableWidgetItem *value = new QTableWidgetItem();
            value->setData(Qt::DisplayRole, item.toInt());

            recordsTable->setRowCount(recordsTable->rowCount()+1);
            recordsTable->setItem(recordsTable->rowCount()-1, 0, value);

            item = in.readLine();

            recordsTable->setItem(recordsTable->rowCount()-1, 1, new QTableWidgetItem(item));
        }
    }
    file.close();
}

void RecordList::nwRezult(QString name, int attemps)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, attemps);

    recordsTable->setRowCount(recordsTable->rowCount()+1);
    recordsTable->setItem(recordsTable->rowCount()-1, 0, item);
    recordsTable->setItem(recordsTable->rowCount()-1, 1, new QTableWidgetItem(name));
    recordsTable->sortItems(0, Qt::AscendingOrder);

    if(recordsTable->rowCount() == 11)
        recordsTable->setRowCount(10);
    QFile file("data.dat");
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        QString item;
        for(int i=0;i<recordsTable->rowCount();i++)
        {
            for(int j=0;j<recordsTable->columnCount();j++)
            {
                item = recordsTable->item(i,j)->text();
                out << item << '\n';
            }
        }
    }
    file.close();
}
