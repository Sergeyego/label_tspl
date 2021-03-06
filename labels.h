#ifndef LABELS_H
#define LABELS_H

#include <QObject>
#include "labelbase.h"

class LabelE801016 : public LabelBase
{
public:
    LabelE801016(QString nam, double w, double h, double g, FormData *d, QObject *parent);
protected:
    virtual QString getCod();
};

class LabelG95110 : public LabelBase
{
public:
    LabelG95110(QString nam, double w, double h, double g, FormData *d, QObject *parent);
protected:
    virtual QString getCod();
};

class LabelE4570 : public LabelBase
{
public:
    LabelE4570(QString nam, double w, double h, double g, FormData *d, QObject *parent);
protected:
    virtual QString getCod();
};

class LabelG100100 : public LabelBase
{
public:
    LabelG100100(QString nam, double w, double h, double g, FormData *d, QObject *parent);
protected:
    virtual QString getCod();
};

class LabelG100100Pal : public LabelBase
{
public:
    LabelG100100Pal(QString nam, double w, double h, double g, FormData *d, QObject *parent);
protected:
    virtual QString getCod();
};

#endif // LABELS_H
