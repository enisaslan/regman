#ifndef FILEREADER_H
#define FILEREADER_H
#include "regObjects.h"
#include <QString>
#include <QStringList>
#include <QFile>

class fileReader
{
public:
    fileReader();

    QStringList readFile(QString fileUrl);
    QVector<QStringList> getStringRegData(QStringList fileData);
    QVector<QStringList> getStringPropData(QStringList registerDatas);
    int getRegSize(QStringList registerDatas);
    QString getRegName(QStringList registerDatas);
    QString getRegInfo(QStringList registerDatas);
    QString getPropName(QStringList propDatas);
    QVector<int> getPropBits(QStringList propDatas);
    QStringList getStringOptionData(QStringList propDatas);
    QVector<options_t> getOptions(QStringList optionDatas);

    QStringList fileDataClear(QStringList fileData);

};

#endif // FILEREADER_H
