#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fr = new fileReader();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QVector<QStringList> strRegDataList;
    QVector<QStringList> strPropDataList;
    QStringList dataList;
    QStringList clearDataList;
    QString fileUrl;
    uint8_t red = 140;
    uint8_t green = 180;
    uint8_t blue = 220;

    fileUrl = QFileDialog::getOpenFileName(this,
         tr("Open Register Info File"), "/", tr("Register Manager File (*.regman)"));

    dataList = fr->readFile(fileUrl);

    register_list.clear();
    ui->cb_regs->clear();

    clearDataList = fr->fileDataClear(dataList);
    if(clearDataList.length())
    {
        strRegDataList = fr->getStringRegData(clearDataList);

        for(QStringList strRegisterObject : strRegDataList)
        {
            mregister_t register_object;

            QString RegName = fr->getRegName(strRegisterObject);
            QString RegInfo = fr->getRegInfo(strRegisterObject);
            int RegSize = fr->getRegSize(strRegisterObject);

            register_object.name = RegName;
            register_object.regInfo = RegInfo;
            register_object.bitSize = RegSize;

            QVector<QStringList> strPropDataList = fr->getStringPropData(strRegisterObject);
            if(strPropDataList.length())
            {
                for(QStringList propDatas : strPropDataList)
                {
                    properties_t propObject;
                    QString propName = fr->getPropName(propDatas);
                    QVector<int> bitList = fr->getPropBits(propDatas);

                    propObject.propInfo = propName;
                    propObject.propColor = QColor::fromRgb(red,green,blue);

                    red += 60;
                    green += 120;
                    blue -= 40;

                    for(int bitNo : bitList)
                    {
                        propObject.bits.append(bitNo);
                    }

                    QStringList optionDatas = fr->getStringOptionData(propDatas);
                    QVector<options_t> options = fr->getOptions(optionDatas);

                    for(options_t option : options)
                    {
                        propObject.options.append(option);
                    }

                    register_object.properties.append(propObject);
                }

            }

            register_list.append(register_object);
        }
    }

    for(mregister_t mreg : register_list)
    {
        //ui->textEdit->append(QString::number(register_list.length()));
        //ui->lbl_reg_info->setText(mreg.regInfo);
        ui->cb_regs->addItem(mreg.name);

//        for(properties_t prop : mreg.properties)
//        {
//            bit_map_color_set(prop.bits, prop.propColor);
//        }
    }

    ui->cb_regs->setCurrentIndex(0);


}


void MainWindow::on_le_input_textChanged(const QString &arg1)
{
    bool legal = true;
    if(arg1.length())
    {
        input_data = 0;
        if(ui->cb_input_type->currentText() == "Decimal")
        {
            quint64 int_data = (quint64)arg1.toULongLong(&legal, 10);
            if(legal == true)
            {
                print_bit_map(int_data);
                input_data = int_data;
            }
            else
            {
                print_bit_map(0);
                input_data = 0;
            }

            print_analsys(this->register_list, this->input_data);
        }
        else if(ui->cb_input_type->currentText() == "Hex")
        {
            quint64 int_data = (quint64)arg1.toULongLong(&legal, 16);
            if(legal == true)
            {
                print_bit_map(int_data);
                input_data = int_data;
            }
            else
            {
                print_bit_map(0);
                input_data = 0;
            }

            print_analsys(this->register_list, this->input_data);
        }
        else if(ui->cb_input_type->currentText() == "Binary")
        {
            quint64 int_data = (quint64)arg1.toULongLong(&legal, 2);
            if(legal == true)
            {
                print_bit_map(int_data);
                input_data = int_data;
            }
            else
            {
                print_bit_map(0);
                input_data = 0;
            }

            print_analsys(this->register_list, this->input_data);
        }
    }
}


void MainWindow::on_cb_regs_currentIndexChanged(int index)
{
    mregister_t mreg = register_list[index];
    QVector<int> clearBits;
    ui->lbl_reg_info->setText(mreg.regInfo);

    for(int i=0; i<64; i++)
    {
      clearBits.append(i);
    }

    // clear bit map colors
    bit_map_color_set(clearBits, QColor::fromRgb(255,255,255));

    for(properties_t prop : mreg.properties)
    {
        bit_map_color_set(prop.bits, prop.propColor);
    }

    ui->textEdit->clear();
}

