#include "filereader.h"

fileReader::fileReader()
{

}

//QVector<register_t> fileReader::fileParser(QStringList datalist)
//{


//}

int fileReader::getRegSize(QStringList registerDatas)
{
    int size=0;
    bool ok = false;
    for(QString line : registerDatas)
    {
        if(line.contains("register_size"))
        {
            QStringList keyValue = line.split("=");
            if((keyValue.length() == 2) && (keyValue[0] == "register_size"))
            {
                size = keyValue[1].toInt(&ok, 10);
                if(ok == true)
                {
                    return size;
                }
            }
        }
    }

    return 0;
}

QString fileReader::getRegName(QStringList registerDatas)
{
    for(QString line : registerDatas)
    {
        if(line.contains("register_name"))
        {
            QStringList keyValue = line.split("=");
            if(keyValue[0] == "register_name")
            {
                return keyValue[1];
            }
        }
    }

    return "";
}

QString fileReader::getRegInfo(QStringList registerDatas)
{
    for(QString line : registerDatas)
    {
        if(line.contains("register_info"))
        {
            QStringList keyValue = line.split("=");
            if(keyValue[0] == "register_info")
            {
                return keyValue[1];
            }
        }
    }

    return "";
}

QString fileReader::getPropName(QStringList propDatas)
{
    for(QString line : propDatas)
    {
        if(line.contains("field_name"))
        {
            QStringList keyValue = line.split("=");
            if(keyValue[0] == "field_name")
            {
                return keyValue[1];
            }
        }
    }

    return "";
}

QVector<int> fileReader::getPropBits(QStringList propDatas)
{
    QVector<int> pbits;
    bool ok;
    QStringList strBits;
    int bitNo;
    for(QString line : propDatas)
    {
        if(line.contains("field_bits"))
        {
            QStringList keyValue = line.split("=");
            if(keyValue[0] == "field_bits")
            {
                strBits = keyValue[1].split(",");
                for(QString stBitNo : strBits)
                {
                    bitNo = stBitNo.toInt(&ok, 10);
                    if(ok == true)
                    {
                        pbits.append(bitNo);
                    }
                    else
                    {
                        pbits.clear();
                        return pbits;
                    }
                }

                return pbits;
            }
        }
    }

    pbits.clear();
    return pbits;
}

QVector<options_t> fileReader::getOptions(QStringList optionDatas)
{
    QVector<options_t> optionList;
    options_t optionObject;
    int option_value;
    QString optionInfo;
    bool ok;
    QStringList parts;
    QStringList payloadParts;
    for(QString line : optionDatas)
    {
        parts = line.split("=");
        if(parts.length() == 2)
        {
            if(parts[0] != "register_value")
            {
                optionList.clear();
                return optionList;
            }

            payloadParts = parts[1].split("|");
            if(payloadParts.length() != 2)
            {
                optionList.clear();
                return optionList;
            }

            option_value = payloadParts[0].toInt(&ok, 10);
            if(ok == true)
            {
                optionObject.option = option_value;
            }
            else
            {
                optionList.clear();
                return optionList;
            }

            optionInfo = payloadParts[1];
            optionObject.option_info = optionInfo;
            optionList.append(optionObject);
        }
    }

    return optionList;
}

QStringList fileReader::getStringOptionData(QStringList propDatas)
{
    QStringList optionData;
    int startFlag = 0;
    for(QString line : propDatas)
    {
        if(line.contains("<options>"))
        {
            startFlag = 1;
        }

        if((startFlag) && !(line.contains("<options>")) && !(line.contains("<options/>")))
        {
           if(line.length()) optionData.append(line);
        }

        if(line.contains("<options/>"))
        {
            return optionData;
        }
    }

    optionData.clear();
    return optionData;
}

QVector<QStringList> fileReader::getStringPropData(QStringList registerDatas)
{
    QVector<QStringList> temp;
    QStringList propData;
    int startFlag = 0;
    for(QString line : registerDatas)
    {
        if(line.contains("<field>"))
        {
            propData.append(line);
            startFlag = 1;
        }

        if(startFlag)
        {
           if(line.length()) propData.append(line);
        }

        if(line.contains("<field/>"))
        {
            propData.append(line);
            temp.append(propData);
            propData.clear();
            startFlag = 0;
        }
    }

    return temp;
}

QVector<QStringList> fileReader::getStringRegData(QStringList fileData)
{
    QVector<QStringList> temp;
    QStringList regData;
    int startFlag = 0;

    for(QString line : fileData)
    {
        if(line.contains("<register>"))
        {
            regData.append(line);
            startFlag = 1;
        }

        if(startFlag)
        {
           if(line.length()) regData.append(line);
        }

        if(line.contains("<register/>"))
        {
            regData.append(line);
            temp.append(regData);
            regData.clear();
            startFlag = 0;
        }
    }

    return temp;
}

QStringList fileReader::fileDataClear(QStringList fileData)
{
    QStringList clearFile;
    for(QString line : fileData)
    {
        if(line.length() > 2)
        {
            QString validPart = line;

            if(line.contains("!!!"))
            {
                validPart = line.split("!!!")[0];
            }

            if(validPart.length() > 2)
            {
                if(validPart.contains("<register>")){ clearFile.append("<register>"); }
                else if(validPart.contains("<register/>")){ clearFile.append("<register/>"); }
                else if(validPart.contains("<field>")){ clearFile.append("<field>"); }
                else if(validPart.contains("<field/>")){ clearFile.append("<field/>"); }
                else if(validPart.contains("<options>")){ clearFile.append("<options>"); }
                else if(validPart.contains("<options/>")){ clearFile.append("<options/>"); }
                else
                {
                    QStringList validPartKeyVal = validPart.split("=");

                    if(validPartKeyVal.length() == 2)
                    {
                        QString keyData = validPartKeyVal[0].toUtf8();
                        QString valueData = validPartKeyVal[1].toUtf8();

                        if(keyData.contains("register_name")){ keyData = "register_name"; }
                        else if(keyData.contains("register_info")){ keyData = "register_info"; }
                        else if(keyData.contains("register_size")){
                            keyData = "register_size";
                            valueData.replace(QString(" "), QString(""));
                        }
                        else if(keyData.contains("field_name")){ keyData = "field_name"; }
                        else if(keyData.contains("field_bits")){
                            keyData = "field_bits";
                            valueData.replace(QString(" "), QString(""));
                        }
                        else if(keyData.contains("register_value")){
                            QStringList regValueInfoList = valueData.split("|");
                            if(regValueInfoList.length() < 2)
                            {
                                clearFile.clear();
                                return clearFile;
                            }

                            QString regValue = regValueInfoList[0].toUtf8();
                            QString regInfo = regValueInfoList[1].toUtf8();

                            regValue.replace(QString(" "), QString(""));
                            valueData = regValue + "|" + regInfo;
                            keyData = "register_value";
                        }


                        QString clearLine = keyData + "=" + valueData;
                        clearFile.append(clearLine);
                    }
                }

            }

        }
    }

    return clearFile;
}

QStringList fileReader::readFile(QString fileUrl)
{
    QStringList dataList;
    QFile file(fileUrl);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return dataList;
    }

    while (!file.atEnd())
    {
        QString line = file.readLine();
        line.replace(QString("\n"), QString(""));
        line.replace(QString("\r"), QString(""));
        dataList.append(line);
    }

    return dataList;
}
