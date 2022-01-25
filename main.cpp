#include "table.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Table w;
    w.setWindowTitle("Task 2 - Table");
    w.gen_map();
    w.gen_table();
    w.shortcut_connect_create();
    w.connectors();
    w.show();
    return a.exec();
}
