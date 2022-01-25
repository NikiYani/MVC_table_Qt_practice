#ifndef TABLE_H
#define TABLE_H

#include <QTableWidgetItem>
#include <QMainWindow>
#include <QMessageBox>
#include <QShortcut>
#include <QPixmap>
#include <memory>
#include <time.h>
#include <map>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Table; }
QT_END_NAMESPACE

class Table : public QMainWindow
{
    Q_OBJECT

public:
    Table(QWidget *parent = nullptr);
    ~Table();

    void shortcut_connect_create();
    void gen_table();
    void gen_map();
    void connectors();

private slots:
    void slot_shortcut_button_ctrl_c();
    void slot_shortcut_button_ctrl_v();
    void slot_shortcut_button_del();
    void slot_shortcut_button_backspace();
    void slot_shortcut_button_esc();
    void slot_check_empty_row();
    void slot_add_new_row();

private:
    Ui::Table *ui;
    std::map<int, QString> minerals;
    QString buffer;
    QShortcut *hk_ctrl_c;
    QShortcut *hk_ctrl_v;
    QShortcut *hk_del;
    QShortcut *hk_backspace;
    QShortcut *hk_esc;
};
#endif // TABLE_H
