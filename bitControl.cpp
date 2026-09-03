#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QColor"
#include "QMessageBox"

void MainWindow::print_analsys(QVector<register_t> reg_list, uint64_t reg_data)
{
    uint64_t roption = 0;
    QString strOptBin;
    int propBitCount = 0;

    ui->textEdit->clear();

    for(register_t mreg : reg_list)
    {
        if(ui->cb_regs->currentText() == mreg.name)
        {
            for(properties_t mprop : mreg.properties)
            {
                QString bitNumbersInfo;
                ui->textEdit->setTextColor(QColor("black"));

                propBitCount = mprop.bits.length();

                roption = 0;

                bitNumbersInfo += "[";
                for(int bit_no : mprop.bits)
                {
                    bitNumbersInfo += " " + QString::number(bit_no);
                    roption |= (reg_data & (1 << bit_no));
                }
                bitNumbersInfo += " ] - ";

                ui->textEdit->append(bitNumbersInfo + mprop.propInfo);

                for(options_t opt: mprop.options)
                {

                    if(opt.option == roption)
                    {
                        ui->textEdit->setTextColor(mprop.propColor);
                        ui->textEdit->append("> " + opt.option_info);
                    }
                    else
                    {
                        ui->textEdit->setTextColor(QColor("black"));
                        ui->textEdit->append("  " + opt.option_info);
                    }


                }

                ui->textEdit->append(" ");

            }
        }

    }

}

void MainWindow::bit_map_color_set(QVector<int> bits, QColor bitColor)
{
    int i = 0;
    QString bitName;
    QPushButton* pb = NULL;
    QString hexColor;
    QString strR = QString::number(bitColor.red(), 16);
    QString strG = QString::number(bitColor.green(), 16);
    QString strB = QString::number(bitColor.blue(), 16);

    if(strR.length() == 1) strR = "0" + strR;
    if(strG.length() == 1) strG = "0" + strG;
    if(strB.length() == 1) strB = "0" + strB;

    hexColor = "#" + strR + strG + strB;
    //QMessageBox::information(this, "message", hexColor);

    // get all bit buttons from bitmap group
    QList<QPushButton *> allPushButtons =
            ui->registerBitMapGroup->findChildren<QPushButton *>();

    for(int bitNo : bits)
    {
        bitName = "bit" + QString::number(bitNo);

        for(i=0;i<allPushButtons.length();i++)
        {
            pb = allPushButtons[i];
            if(pb->objectName() == bitName)
            {
                pb->setStyleSheet("background-color:" + hexColor);
            }
        }
    }
}

void MainWindow::print_bit_map(uint64_t data)
{
    uint32_t i;
    uint32_t b;
    QString bitName;
    QPushButton* pb = NULL;

    // get all bit buttons from bitmap group
    QList<QPushButton *> allPushButtons =
            ui->registerBitMapGroup->findChildren<QPushButton *>();

    for(b=0;b<64;b++)
    {
        bitName = "bit" + QString::number(b);

        for(i=0;i<allPushButtons.length();i++)
        {
            pb = allPushButtons[i];
            if(pb->objectName() == bitName)
            {
                // get bit state
                if((uint64_t)(data >> b) & (uint64_t)1){
                    pb->setText("1");
                }else{
                    pb->setText("0");
                }
            }
        }
    }
}

void MainWindow::bit_update(uint8_t bit_number, bool current)
{
    uint64_t current_data = this->input_data;
    uint64_t sdata;
    QString strEVal;

    uint64_t one = 1;
    uint64_t sc = (uint64_t)bit_number;


    sdata = one << sc;
    if(current == true)
    {
        current_data |= sdata;
    }
    else
    {
        current_data &= (uint64_t)(~sdata);
    }

    if(ui->cb_input_type->currentText()== "Hex")
    {
        strEVal = QString::number(current_data,16).toUpper();
    }
    else if(ui->cb_input_type->currentText() == "Binary")
    {
        strEVal = QString::number(current_data, 2);
    }
    else if(ui->cb_input_type->currentText() == "Decimal")
    {
        strEVal = QString::number(current_data, 10);
    }

    ui->le_edited_val->setText(strEVal);

    this->input_data = current_data;

    print_analsys(this->register_list, current_data);

}

void MainWindow::on_bit63_released(){
    if(ui->bit63->text() == "0"){
        ui->bit63->setText("1");
        bit_update(63, true);
    }else {
        ui->bit63->setText("0");
        bit_update(63, false);
    }
}
void MainWindow::on_bit62_released(){
    if(ui->bit62->text() == "0"){
        ui->bit62->setText("1");
        bit_update(62, true);
    }else {
        ui->bit62->setText("0");
        bit_update(62, false);
    }
}
void MainWindow::on_bit61_released(){
    if(ui->bit61->text() == "0"){
        ui->bit61->setText("1");
        bit_update(61, true);
    }else {
        ui->bit61->setText("0");
        bit_update(61, false);
    }
}
void MainWindow::on_bit60_released(){
    if(ui->bit60->text() == "0"){
        ui->bit60->setText("1");
        bit_update(60, true);
    }else {
        ui->bit60->setText("0");
        bit_update(60, false);
    }
}
void MainWindow::on_bit59_released(){
    if(ui->bit59->text() == "0"){
        ui->bit59->setText("1");
        bit_update(59, true);
    }else {
        ui->bit59->setText("0");
        bit_update(59, false);
    }
}
void MainWindow::on_bit58_released(){
    if(ui->bit58->text() == "0"){
        ui->bit58->setText("1");
        bit_update(58, true);
    }else {
        ui->bit58->setText("0");
        bit_update(58, false);
    }
}
void MainWindow::on_bit57_released(){
    if(ui->bit57->text() == "0"){
        ui->bit57->setText("1");
        bit_update(57, true);
    }else {
        ui->bit57->setText("0");
        bit_update(57, false);
    }
}
void MainWindow::on_bit56_released(){
    if(ui->bit56->text() == "0"){
        ui->bit56->setText("1");
        bit_update(56, true);
    }else {
        ui->bit56->setText("0");
        bit_update(56, false);
    }
}

void MainWindow::on_bit55_released(){
    if(ui->bit55->text() == "0"){
        ui->bit55->setText("1");
        bit_update(55, true);
    }else {
        ui->bit55->setText("0");
        bit_update(55, false);
    }
}
void MainWindow::on_bit54_released(){
    if(ui->bit54->text() == "0"){
        ui->bit54->setText("1");
        bit_update(54, true);
    }else {
        ui->bit54->setText("0");
        bit_update(54, false);
    }
}
void MainWindow::on_bit53_released(){
    if(ui->bit53->text() == "0"){
        ui->bit53->setText("1");
        bit_update(53, true);
    }else {
        ui->bit53->setText("0");
        bit_update(53, false);
    }
}
void MainWindow::on_bit52_released(){
    if(ui->bit52->text() == "0"){
        ui->bit52->setText("1");
        bit_update(52, true);
    }else {
        ui->bit52->setText("0");
        bit_update(52, false);
    }
}
void MainWindow::on_bit51_released(){
    if(ui->bit51->text() == "0"){
        ui->bit51->setText("1");
        bit_update(51, true);
    }else {
        ui->bit51->setText("0");
        bit_update(51, false);
    }
}
void MainWindow::on_bit50_released(){
    if(ui->bit50->text() == "0"){
        ui->bit50->setText("1");
        bit_update(50, true);
    }else {
        ui->bit50->setText("0");
        bit_update(50, false);
    }
}
void MainWindow::on_bit49_released(){
    if(ui->bit49->text() == "0"){
        ui->bit49->setText("1");
        bit_update(49, true);
    }else {
        ui->bit49->setText("0");
        bit_update(49, false);
    }
}
void MainWindow::on_bit48_released(){
    if(ui->bit48->text() == "0"){
        ui->bit48->setText("1");
        bit_update(48, true);
    }else {
        ui->bit48->setText("0");
        bit_update(48, false);
    }
}
void MainWindow::on_bit47_released(){
    if(ui->bit47->text() == "0"){
        ui->bit47->setText("1");
        bit_update(47, true);
    }else {
        ui->bit47->setText("0");
        bit_update(47, false);
    }
}
void MainWindow::on_bit46_released(){
    if(ui->bit46->text() == "0"){
        ui->bit46->setText("1");
        bit_update(46, true);
    }else {
        ui->bit46->setText("0");
        bit_update(46, false);
    }
}
void MainWindow::on_bit45_released(){
    if(ui->bit45->text() == "0"){
        ui->bit45->setText("1");
        bit_update(45, true);
    }else {
        ui->bit45->setText("0");
        bit_update(45, false);
    }
}
void MainWindow::on_bit44_released(){
    if(ui->bit44->text() == "0"){
        ui->bit44->setText("1");
        bit_update(44, true);
    }else {
        ui->bit44->setText("0");
        bit_update(44, false);
    }
}
void MainWindow::on_bit43_released(){
    if(ui->bit43->text() == "0"){
        ui->bit43->setText("1");
        bit_update(43, true);
    }else {
        ui->bit43->setText("0");
        bit_update(43, false);
    }
}
void MainWindow::on_bit42_released(){
    if(ui->bit42->text() == "0"){
        ui->bit42->setText("1");
        bit_update(42, true);
    }else {
        ui->bit42->setText("0");
        bit_update(42, false);
    }
}
void MainWindow::on_bit41_released(){
    if(ui->bit41->text() == "0"){
        ui->bit41->setText("1");
        bit_update(41, true);
    }else {
        ui->bit41->setText("0");
        bit_update(41, false);
    }
}
void MainWindow::on_bit40_released(){
    if(ui->bit40->text() == "0"){
        ui->bit40->setText("1");
        bit_update(40, true);
    }else {
        ui->bit40->setText("0");
        bit_update(40, false);
    }
}
void MainWindow::on_bit39_released(){
    if(ui->bit39->text() == "0"){
        ui->bit39->setText("1");
        bit_update(39, true);
    }else {
        ui->bit39->setText("0");
        bit_update(39, false);
    }
}
void MainWindow::on_bit38_released(){
    if(ui->bit38->text() == "0"){
        ui->bit38->setText("1");
        bit_update(38, true);
    }else {
        ui->bit38->setText("0");
        bit_update(38, false);
    }
}
void MainWindow::on_bit37_released(){
    if(ui->bit37->text() == "0"){
        ui->bit37->setText("1");
        bit_update(37, true);
    }else {
        ui->bit37->setText("0");
        bit_update(37, false);
    }
}
void MainWindow::on_bit36_released(){
    if(ui->bit36->text() == "0"){
        ui->bit36->setText("1");
        bit_update(36, true);
    }else {
        ui->bit36->setText("0");
        bit_update(36, false);
    }
}
void MainWindow::on_bit35_released(){
    if(ui->bit35->text() == "0"){
        ui->bit35->setText("1");
        bit_update(35, true);
    }else {
        ui->bit35->setText("0");
        bit_update(35, false);
    }
}
void MainWindow::on_bit34_released(){
    if(ui->bit34->text() == "0"){
        ui->bit34->setText("1");
        bit_update(34, true);
    }else {
        ui->bit34->setText("0");
        bit_update(34, false);
    }
}
void MainWindow::on_bit33_released(){
    if(ui->bit33->text() == "0"){
        ui->bit33->setText("1");
        bit_update(33, true);
    }else {
        ui->bit33->setText("0");
        bit_update(33, false);
    }
}
void MainWindow::on_bit32_released(){
    if(ui->bit32->text() == "0"){
        ui->bit32->setText("1");
        bit_update(32, true);
    }else {
        ui->bit32->setText("0");
        bit_update(32, false);
    }
}
void MainWindow::on_bit31_released(){
    if(ui->bit31->text() == "0"){
        ui->bit31->setText("1");
        bit_update(31, true);
    }else {
        ui->bit31->setText("0");
        bit_update(31, false);
    }
}
void MainWindow::on_bit30_released(){
    if(ui->bit30->text() == "0"){
        ui->bit30->setText("1");
        bit_update(30, true);
    }else {
        ui->bit30->setText("0");
        bit_update(30, false);
    }
}


void MainWindow::on_bit29_released(){
    if(ui->bit29->text() == "0"){
        ui->bit29->setText("1");
        bit_update(29, true);
    }else {
        ui->bit29->setText("0");
        bit_update(29, false);
    }
}
void MainWindow::on_bit28_released(){
    if(ui->bit28->text() == "0"){
        ui->bit28->setText("1");
        bit_update(28, true);
    }else {
        ui->bit28->setText("0");
        bit_update(28, false);
    }
}


void MainWindow::on_bit27_released(){
    if(ui->bit27->text() == "0"){
        ui->bit27->setText("1");
        bit_update(27, true);
    }else {
        ui->bit27->setText("0");
        bit_update(27, false);
    }
}


void MainWindow::on_bit26_released(){
    if(ui->bit26->text() == "0"){
        ui->bit26->setText("1");
        bit_update(26, true);
    }else {
        ui->bit26->setText("0");
        bit_update(26, false);
    }
}
void MainWindow::on_bit25_released(){
    if(ui->bit25->text() == "0"){
        ui->bit25->setText("1");
        bit_update(25, true);
    }else {
        ui->bit25->setText("0");
        bit_update(25, false);
    }
}
void MainWindow::on_bit24_released(){
    if(ui->bit24->text() == "0"){
        ui->bit24->setText("1");
        bit_update(24, true);
    }else {
        ui->bit24->setText("0");
        bit_update(24, false);
    }
}
void MainWindow::on_bit23_released(){
    if(ui->bit23->text() == "0"){
        ui->bit23->setText("1");
        bit_update(23, true);
    }else {
        ui->bit23->setText("0");
        bit_update(23, false);
    }
}
void MainWindow::on_bit22_released(){
    if(ui->bit22->text() == "0"){
        ui->bit22->setText("1");
        bit_update(22, true);
    }else {
        ui->bit22->setText("0");
        bit_update(22, false);
    }
}


void MainWindow::on_bit21_released(){
    if(ui->bit21->text() == "0"){
        ui->bit21->setText("1");
        bit_update(21, true);
    }else {
        ui->bit21->setText("0");
        bit_update(21, false);
    }
}




void MainWindow::on_bit20_released(){
    if(ui->bit20->text() == "0"){
        ui->bit20->setText("1");
        bit_update(20, true);
    }else {
        ui->bit20->setText("0");
        bit_update(20, false);
    }
}
void MainWindow::on_bit19_released(){
    if(ui->bit19->text() == "0"){
        ui->bit19->setText("1");
        bit_update(19, true);
    }else {
        ui->bit19->setText("0");
        bit_update(19, false);
    }
}


void MainWindow::on_bit18_released(){
    if(ui->bit18->text() == "0"){
        ui->bit18->setText("1");
        bit_update(18, true);
    }else {
        ui->bit18->setText("0");
        bit_update(18, false);
    }
}
void MainWindow::on_bit17_released(){
    if(ui->bit17->text() == "0"){
        ui->bit17->setText("1");
        bit_update(17, true);
    }else {
        ui->bit17->setText("0");
        bit_update(17, false);
    }
}
void MainWindow::on_bit16_released()
{
    if(ui->bit16->text() == "0"){
        ui->bit16->setText("1");
        bit_update(16, true);
    }else {
        ui->bit16->setText("0");
        bit_update(16, false);
    }
}
void MainWindow::on_bit15_released(){
    if(ui->bit15->text() == "0"){
        ui->bit15->setText("1");
        bit_update(15, true);
    }else {
        ui->bit15->setText("0");
        bit_update(15, false);
    }
}
void MainWindow::on_bit14_released(){
    if(ui->bit14->text() == "0"){
        ui->bit14->setText("1");
        bit_update(14, true);
    }else {
        ui->bit14->setText("0");
        bit_update(14, false);
    }
}
void MainWindow::on_bit13_released(){
    if(ui->bit13->text() == "0"){
        ui->bit13->setText("1");
        bit_update(13, true);
    }else {
        ui->bit13->setText("0");
        bit_update(13, false);
    }
}
void MainWindow::on_bit12_released(){
    if(ui->bit12->text() == "0"){
        ui->bit12->setText("1");
        bit_update(12, true);
    }else {
        ui->bit12->setText("0");
        bit_update(12, false);
    }
}
void MainWindow::on_bit11_released(){
    if(ui->bit11->text() == "0"){
        ui->bit11->setText("1");
        bit_update(11, true);
    }else {
        ui->bit11->setText("0");
        bit_update(11, false);
    }
}
void MainWindow::on_bit10_released(){
    if(ui->bit10->text() == "0"){
        ui->bit10->setText("1");
        bit_update(10, true);
    }else {
        ui->bit10->setText("0");
        bit_update(10, false);
    }
}
void MainWindow::on_bit9_released(){
    if(ui->bit9->text() == "0"){
        ui->bit9->setText("1");
        bit_update(9, true);
    }else {
        ui->bit9->setText("0");
        bit_update(9, false);
    }
}
void MainWindow::on_bit8_released(){
    if(ui->bit8->text() == "0"){
        ui->bit8->setText("1");
        bit_update(8, true);
    }else {
        ui->bit8->setText("0");
        bit_update(8, false);
    }
}
void MainWindow::on_bit7_released(){
    if(ui->bit7->text() == "0"){
        ui->bit7->setText("1");
        bit_update(7, true);
    }else {
        ui->bit7->setText("0");
        bit_update(7, false);
    }
}
void MainWindow::on_bit6_released(){
    if(ui->bit6->text() == "0"){
        ui->bit6->setText("1");
        bit_update(6, true);
    }else {
        ui->bit6->setText("0");
        bit_update(6, false);
    }
}
void MainWindow::on_bit5_released(){
    if(ui->bit5->text() == "0"){
        ui->bit5->setText("1");
        bit_update(5, true);
    }else {
        ui->bit5->setText("0");
        bit_update(5, false);
    }
}
void MainWindow::on_bit4_released()
{
    if(ui->bit4->text() == "0"){
        ui->bit4->setText("1");
        bit_update(4, true);
    }else {
        ui->bit4->setText("0");
        bit_update(4, false);
    }
}
void MainWindow::on_bit3_released(){
    if(ui->bit3->text() == "0"){
        ui->bit3->setText("1");
        bit_update(3, true);
    }else {
        ui->bit3->setText("0");
        bit_update(3, false);
    }
}
void MainWindow::on_bit2_released(){
    if(ui->bit2->text() == "0"){
        ui->bit2->setText("1");
        bit_update(2, true);
    }else {
        ui->bit2->setText("0");
        bit_update(2, false);
    }
}
void MainWindow::on_bit1_released(){
    if(ui->bit1->text() == "0"){
        ui->bit1->setText("1");
        bit_update(1, true);
    }else {
        ui->bit1->setText("0");
        bit_update(1, false);
    }
}
void MainWindow::on_bit0_released(){
    if(ui->bit0->text() == "0"){
        ui->bit0->setText("1");
        bit_update(0, true);
    }else {
        ui->bit0->setText("0");
        bit_update(0, false);
    }
}
