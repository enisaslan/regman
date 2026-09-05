#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <regObjects.h>
#include "filereader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int flag = 0;

    quint64 input_data = 0;

    QVector<mregister_t> register_list;

    fileReader* fr;

private slots:

    void print_analsys(QVector<mregister_t> reg_list, quint64 reg_data);

    void bit_map_color_set(QVector<int> bits, QColor bitColor);

    void print_bit_map(quint64 data);

    void bit_update(quint8 bit_number, bool current);

    void on_bit63_released();

    void on_bit62_released();

    void on_bit61_released();

    void on_bit60_released();

    void on_bit56_released();

    void on_bit57_released();

    void on_bit58_released();

    void on_bit59_released();

    void on_bit55_released();

    void on_bit54_released();

    void on_bit53_released();

    void on_bit52_released();

    void on_bit51_released();

    void on_bit50_released();

    void on_bit49_released();

    void on_bit48_released();

    void on_bit47_released();

    void on_bit46_released();

    void on_bit45_released();

    void on_bit44_released();

    void on_bit43_released();

    void on_bit42_released();

    void on_bit41_released();

    void on_bit40_released();

    void on_bit39_released();

    void on_bit38_released();

    void on_bit37_released();

    void on_bit36_released();

    void on_bit35_released();

    void on_bit34_released();

    void on_bit33_released();

    void on_bit32_released();

    void on_bit31_released();

    void on_bit30_released();

    void on_bit29_released();

    void on_bit28_released();

    void on_bit27_released();

    void on_bit26_released();

    void on_bit25_released();

    void on_bit24_released();

    void on_bit23_released();

    void on_bit22_released();

    void on_bit21_released();

    void on_bit20_released();

    void on_bit19_released();

    void on_bit18_released();

    void on_bit17_released();

    void on_bit16_released();

    void on_bit15_released();

    void on_bit14_released();

    void on_bit13_released();

    void on_bit12_released();

    void on_bit11_released();

    void on_bit10_released();

    void on_bit9_released();

    void on_bit8_released();

    void on_bit7_released();

    void on_bit6_released();

    void on_bit5_released();

    void on_bit4_released();

    void on_bit3_released();

    void on_bit2_released();

    void on_bit1_released();

    void on_bit0_released();

    void on_actionOpen_triggered();

    void on_le_input_textChanged(const QString &arg1);

    void on_cb_regs_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
