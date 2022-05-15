#include "bulls_and_cows_game.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QInputDialog>
#include <QCloseEvent>

Bulls_and_Cows_Game::Bulls_and_Cows_Game(QWidget *parent)
    : QWidget(parent)
{
    records = new RecordList();
    records->setWindowTitle("Рекорды");
    records->resize(300, 348);
    //records->setFixedSize(300,348);
    records->move(700, 150);

    val = new QRegularExpressionValidator(QRegularExpression("^[0-9]{4}$"));
    gameTable = new QTableWidget(0, 2, this);
    records->tableSettings(gameTable);

    QStringList lst;
    lst << "Число" << "Результат";
    gameTable->setHorizontalHeaderLabels(lst);

    status = new QLabel("Игра не начата", this);
    status->setAlignment(Qt::AlignCenter);
    input = new QLineEdit(this);
    nwgButton = new QPushButton("&Новая игра", this);
    recButton = new QPushButton("&Рекорды", this);
    chkButton = new QPushButton("&Проверить", this);
    inLabel = new QLabel("&Введите число: ", this);
    inLabel->setBuddy(input);

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(nwgButton, 0, 0);
    grid->addWidget(status, 0, 1);
    grid->addWidget(recButton, 0, 2);
    grid->addWidget(inLabel, 1, 0);
    grid->addWidget(input, 1, 1);
    grid->addWidget(chkButton, 1, 2);
    grid->addWidget(gameTable, 2, 0, 5, 3);

    connect(nwgButton, &QPushButton::clicked, this, &Bulls_and_Cows_Game::nwGame);
    connect(recButton, &QPushButton::clicked, this, &Bulls_and_Cows_Game::recShow);
    connect(chkButton, &QPushButton::clicked, this, &Bulls_and_Cows_Game::checkNum);
    connect(input, &QLineEdit::editingFinished, this, &Bulls_and_Cows_Game::getInput);
    connect(this, &Bulls_and_Cows_Game::personInfo, records, &RecordList::nwRezult);

    input->setValidator(val);
    input->setReadOnly(true);
    chkButton->setDisabled(true);
}

bool Bulls_and_Cows_Game::validate()
{
    QString s = input->text();
    if(s.size()!=4)
        s = "Должно быть введено четырехзначное число!";//QMessageBox::warning(this, "Ошибка", "Должно быть введено четырехзначное число!");
    else if(!numberRuleCheck(s))
        s = "Цифры в числе должны быть различны!";//QMessageBox::warning(this, "Ошибка", "Цифры в числе должны быть различны!");
    else
        return true;

    QMessageBox::warning(this, "Ошибка", s);
    input->setFocus();
    input->setText("");
    return false;
}

bool Bulls_and_Cows_Game::numberRuleCheck(QString n)
{
    for(int i = 0; i < n.size()-1; i++)
        for(int j = i+1; j < n.size(); j++)
            if(n[i] == n[j] || (n.size()==3 && (n[i]=='0' || n[j]=='0')))
                return false;
    return true;
}

void Bulls_and_Cows_Game::nwGame()
{
    chkButton->setDisabled(false);
    input->setReadOnly(false);
    status->setText("Игра началась");
    input->setText("");
    gameTable->setRowCount(0);
    do
    {
        number = QString::number(QRandomGenerator::global()->bounded(100, 10000));
    }while(!numberRuleCheck(number));
    if(number.size() == 3)
        number.push_front("0");
    //QMessageBox::information(this, "Циферка", number);
}

void Bulls_and_Cows_Game::recShow()
{
    records->show();
}

void Bulls_and_Cows_Game::checkNum()
{
    if(!validate())
        return;
    int bulls = 0;
    int cows = 0;
    QString s = input->text();
    for(int i = 0; i < number.size(); i++)
        for(int j = 0; j < number.size(); j++)
            if(number[i] == s[j])
            {
                if(i==j)
                    bulls++;
                else
                    cows++;
            }

    gameTable->insertRow(gameTable->rowCount());
    gameTable->setItem(gameTable->rowCount()-1, 0, new QTableWidgetItem(input->text()));
    gameTable->setItem(gameTable->rowCount()-1, 1, new QTableWidgetItem(QString("Быков: %1; Коров: %2").arg(bulls).arg(cows)));
    input->setText("");
    gameTable->scrollToBottom();

    if(bulls == 4)
        winning();
    else
        status->setText("Не угадали, попробуйте ещё раз...");
}

void Bulls_and_Cows_Game::winning()
{
    QMessageBox::information(this, "Победа!",
                             QString("Вы победили!\nИскомое число: %1"
                             "\nЧисло попыток: %2").arg(number).arg(gameTable->rowCount()));
    input->setReadOnly(true);
    status->setText("Вы победили");
    chkButton->setDisabled(true);
    if(records->recordsTable->rowCount()<10 || gameTable->rowCount() < (records->recordsTable->item(9,0)->text()).toInt())
    {
        bool bOk;
        QString name = QInputDialog::getText( 0, "Список лидеров", "Ваше имя:", QLineEdit::Normal, "", &bOk);
        if(bOk)
        {
            if(name.isEmpty())
                name = "<без имени>";
            emit personInfo(name, gameTable->rowCount());
        }
        else
            QMessageBox::information(this, "Информация","Ваш результат не будет занесен в таблицу рекордов");
    }
}

void Bulls_and_Cows_Game::closeEvent(QCloseEvent *event)
{
    records->close();
    event->accept();
}

void Bulls_and_Cows_Game::getInput()
{
    emit chkButton->clicked();
}

Bulls_and_Cows_Game::~Bulls_and_Cows_Game()
{
    delete records;
}
