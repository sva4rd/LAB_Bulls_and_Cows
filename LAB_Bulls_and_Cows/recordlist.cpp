#include "recordlist.h"
#include <QHeaderView>
#include <QLayout>
#include <QMessageBox>

RecordList::RecordList(/*QWidget *parent*/)
    //: QWidget{parent}
{
    recordsTable = new QTableWidget(0, 2, this);
    tableSettings(recordsTable);

    QStringList recHeaderList;
    recHeaderList << "Попыток" << "Имя";
    recordsTable->setHorizontalHeaderLabels(recHeaderList);

    QVBoxLayout *recLayout = new QVBoxLayout(this);
    recLayout->addWidget(recordsTable);

    QFile file("data.dat");
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QTableWidgetItem *value = new QTableWidgetItem();
            value->setData(Qt::DisplayRole, in.readLine().toInt());//

            recordsTable->setRowCount(recordsTable->rowCount()+1);
            recordsTable->setItem(recordsTable->rowCount()-1, 0, value);
            recordsTable->setItem(recordsTable->rowCount()-1, 1, new QTableWidgetItem(in.readLine()));//
        }
    }
    file.close();
}

void RecordList::nwRezult(QString name, int attemps)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, attemps);

    recordsTable->insertRow(recordsTable->rowCount());
    recordsTable->setItem(recordsTable->rowCount()-1, 0, item);
    recordsTable->setItem(recordsTable->rowCount()-1, 1, new QTableWidgetItem(name));
    recordsTable->sortItems(0, Qt::AscendingOrder);

    if(recordsTable->rowCount() == 11)
        recordsTable->removeRow(10);
    QFile file("data.dat");
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        for(int i=0;i<recordsTable->rowCount();i++)
            for(int j=0;j<recordsTable->columnCount();j++)
                out << recordsTable->item(i,j)->text() << '\n';
    }
    file.close();
}

void RecordList::tableSettings(QTableWidget *table)
{
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    QHeaderView* header = table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
}

RecordList::~RecordList(){}
