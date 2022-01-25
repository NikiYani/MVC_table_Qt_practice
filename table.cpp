#include "table.h"
#include "ui_table.h"

void Table::shortcut_connect_create()
{
    hk_ctrl_c = new QShortcut(this);
    hk_ctrl_v = new QShortcut(this);
    hk_del = new QShortcut(this);
    hk_backspace = new QShortcut(this);
    hk_esc = new QShortcut(this);

    hk_ctrl_c->setKey(Qt::CTRL + Qt::Key_C);
    hk_ctrl_v->setKey(Qt::CTRL + Qt::Key_V);
    hk_del->setKey(Qt::Key_Delete);
    hk_backspace->setKey(Qt::Key_Backspace);
    hk_esc->setKey(Qt::Key_Escape);

    connect(hk_ctrl_c, SIGNAL(activated()), this, SLOT(slot_shortcut_button_ctrl_c()));
    connect(hk_ctrl_v, SIGNAL(activated()), this, SLOT(slot_shortcut_button_ctrl_v()));
    connect(hk_del, SIGNAL(activated()), this, SLOT(slot_shortcut_button_del()));
    connect(hk_backspace, SIGNAL(activated()), this, SLOT(slot_shortcut_button_backspace()));
    connect(hk_esc, SIGNAL(activated()), this, SLOT(slot_shortcut_button_esc()));
}

void Table::connectors()
{
    connect(ui->tableWidget, &QTableWidget::cellChanged, this, &Table::slot_check_empty_row);
    connect(ui->tableWidget, &QTableWidget::cellChanged, this, &Table::slot_add_new_row);
}

void Table::gen_map()
{
    minerals[0] = "Talc";
    minerals[1] = "Gypsum";
    minerals[2] = "Calcite";
    minerals[3] = "Fluorite";
    minerals[4] = "Apatite";
    minerals[5] = "Quartz";
    minerals[6] = "Topaz";
    minerals[7] = "Corundum";
    minerals[8] = "Turquoise";
    minerals[9] = "Halite";
}

void Table::gen_table()
{
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(4);

    ui->tableWidget->wordWrap();
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(180);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    srand(time(nullptr));

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            QTableWidgetItem* text_field;
            if(i != ui->tableWidget->rowCount() - 1)
            {
                text_field = new QTableWidgetItem(minerals[rand() % 10]);
            }
            else
            {
                text_field = new QTableWidgetItem("");
            }
            ui->tableWidget->setItem(i, j, text_field);
        }

        ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem("Set of minerals № " + QString::number(i + 1)));
    }

    ui->tableWidget->setVerticalHeaderItem(ui->tableWidget->rowCount() - 1,
                                           new QTableWidgetItem(""));

}

void Table::slot_shortcut_button_ctrl_c()
{
    buffer = ui->tableWidget->item(ui->tableWidget->currentRow(), ui->tableWidget->currentColumn())->text();
}

void Table::slot_shortcut_button_ctrl_v()
{
    ui->tableWidget->item(ui->tableWidget->currentRow(), ui->tableWidget->currentColumn())->setText(buffer);
}

void Table::slot_shortcut_button_del()
{
    ui->tableWidget->item(ui->tableWidget->currentRow(), ui->tableWidget->currentColumn())->setText("");
}

void Table::slot_shortcut_button_backspace()
{
    slot_shortcut_button_del();
}

void Table::slot_shortcut_button_esc()
{
    QMessageBox msgBox;
    msgBox.setText("Do you really want to leave?");
    msgBox.setWindowTitle("Exit");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setDefaultButton(QMessageBox::No);
    int res = msgBox.exec();
    if(res == QMessageBox::No)
    {
        return;
    }
    else
    {
        this->close();
        exit(0);
    }
}

void Table::slot_check_empty_row()
{
    int check_empty_row = 0;
    for(int i = 0; i < ui->tableWidget->columnCount(); i++)
    {
        if(ui->tableWidget->item(ui->tableWidget->currentRow(), i)->text() != "")
        {
            break;
        }
        else
        {
            check_empty_row++;
        }
    }

    if(check_empty_row == ui->tableWidget->columnCount())
    {
        if(ui->tableWidget->currentRow() != (ui->tableWidget->rowCount() - 1))
        {
            ui->tableWidget->model()->removeRow(ui->tableWidget->currentRow());
        }
    }
}

void Table::slot_add_new_row()
{
    bool check_not_empty = false;

    for(int j = 0; j < ui->tableWidget->columnCount(); j++)
    {
        QAbstractItemModel *model = ui->tableWidget->model();

        if(model->data(model->index(ui->tableWidget->rowCount() - 1, j), Qt::DisplayRole).toString() != "")
        {
            check_not_empty = true;
        }
    }

    if(check_not_empty)
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        for(int k = 0; k < ui->tableWidget->columnCount(); k++)
        {
            QTableWidgetItem* text_field = new QTableWidgetItem();
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, k, text_field);
        }
    }

    for(int i = 0; i < ui->tableWidget->rowCount() - 1; i++)
    {
        ui->tableWidget->setVerticalHeaderItem(i,
                                               new QTableWidgetItem(QString::number(i + 1)));
    }

    ui->tableWidget->setVerticalHeaderItem(ui->tableWidget->rowCount() - 1,
                                           new QTableWidgetItem(""));
}

Table::Table(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Table)
{
    ui->setupUi(this);

    ui->tableWidget->setToolTip("Ctrl + C - копирование\n"
                                "Ctrl + V - вставка\n"
                                "Del - удаление элемента\n"
                                "Backspace - удаление элемента\n"
                                "Escape - выход");

}

Table::~Table()
{
    delete hk_ctrl_c;
    delete hk_ctrl_v;
    delete hk_del;
    delete hk_backspace;
    delete hk_esc;
    delete ui;
}
