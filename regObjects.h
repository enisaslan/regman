#ifndef REGOBJECTS_H
#define REGOBJECTS_H
#include <QList>
#include <QVector>
#include <QString>
#include <QColor>
#include <QStringList>

typedef struct options_t{
    int option;
    QString option_info;
}moptions_t;

typedef struct properties_t{
    QColor propColor;
    QString propInfo;
    QVector<int> bits;
    QVector<options_t> options;
}properties_t;

typedef struct mregister_t{
    QString name;
    QString regInfo;
    int bitSize;
    QVector<properties_t> properties;
}mregister_t;

#endif // REGOBJECTS_H
