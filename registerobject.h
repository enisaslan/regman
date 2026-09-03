#ifndef REGISTEROBJECT_H
#define REGISTEROBJECT_H
#include <QList>
#include <QString>
#include <QStringList>

class registerObject
{
public:
    registerObject();

    int reg_size;
    int bit_order;

    QList<QString> props;
    QList<int> bit_nums;


};

#endif // REGISTEROBJECT_H
