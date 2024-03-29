#include "labels.h"

LabelE801016::LabelE801016(QString nam, double w, double h, double g, FormData *d, QObject *parent) : LabelBase(nam,w,h,g,d,parent)
{

}

QString LabelE801016::getCod()
{
    QString cod=LabelBase::getCod();
    cod.push_back(logo(15,13.75));
    /*cod.push_back(text(6.25,43.75,QString::fromUtf8("Марка - ")+data->marka(),12));
    cod.push_back(text(6.25,48.75,QString::fromUtf8("Диаметр, мм - ")+data->diametr(),12));
    cod.push_back(text(6.25,53.75,QString::fromUtf8("Плавка - ")+data->plavka(),12));
    cod.push_back(text(6.25,58.75,QString::fromUtf8("Партия - ")+data->part(),12));
    cod.push_back(text(6.25,63.75,QString::fromUtf8("Тип носителя - ")+data->spool(),12));
    cod.push_back(text(6.25,68.75,QString::fromUtf8("Код продукции - ")+data->codeProd(),12));
    cod.push_back(text(6.25,73.75,QString::fromUtf8("Масса нетто, кг - ")+data->mas(),12));
    cod.push_back(text(6.25,78.75,QString::fromUtf8("Дата изг. - ")+data->datePart(),12));
    cod.push_back(ean13(75,43.75,data->eanEd(),17.5,0.375,90));*/

    cod.push_back(text(6.25,50,QString::fromUtf8("Марка - ")+data->marka(),12));
    cod.push_back(text(6.25,55,QString::fromUtf8("Диаметр, мм - ")+data->diametr(),12));
    cod.push_back(text(6.25,60,QString::fromUtf8("Плавка - ")+data->plavka(),12));
    cod.push_back(text(6.25,65,QString::fromUtf8("Партия - ")+data->part(),12));
    cod.push_back(text(6.25,70,QString::fromUtf8("Тип носителя - ")+data->spool(),12));
    cod.push_back(text(6.25,75,QString::fromUtf8("Код продукции - ")+data->codeProd(),12));
    cod.push_back(text(6.25,80,QString::fromUtf8("Масса нетто, кг - ")+data->mas(),12));
    cod.push_back(text(6.25,85,QString::fromUtf8("Дата изг. - ")+data->datePart(),12));
    cod.push_back(ean13(13.75,33.75,data->eanEd(),9,0.375,0));

    cod.push_back(otkStamp(55,20));
    cod.push_back(print());
    return cod;
}

LabelG95110::LabelG95110(QString nam, double w, double h, double g, FormData *d, QObject *parent) : LabelBase(nam,w,h,g,d,parent)
{

}

QString LabelG95110::getCod()
{
    QString cod=LabelBase::getCod();
    cod.push_back(logo(6.25,13.75));
    cod.push_back(text(6.25,32.5,QString::fromUtf8("Проволока сварочная"),12));
    cod.push_back(text(45,31.875,data->marka(),14));
    cod.push_back(block(6.25,37.5,86.25,10,data->gost(),12));
    cod.push_back(block(6.25,47.5,86.25,15,data->description(),10));
    cod.push_back(text(6.25,62.5,QString::fromUtf8("Диаметр, мм - ")+data->diametr(),12));
    cod.push_back(text(6.25,67.5,QString::fromUtf8("Плавка - ")+data->plavka(),12));
    cod.push_back(text(6.25,72.5,QString::fromUtf8("Партия № ")+data->part(),12));
    cod.push_back(text(6.25,77.5,QString::fromUtf8("Тип носителя - ")+data->spool(),12));
    cod.push_back(text(45,62.5,QString::fromUtf8("Дата изг. - ")+data->datePart(),12));
    cod.push_back(text(45,67.5,QString::fromUtf8("Масса нетто, кг - ")+data->mas(),12));
    cod.push_back(text(45,72.5,QString::fromUtf8("Упаковщик № ")+data->upkNum(),12));
    cod.push_back(block(6.25,82.5,86.25,18,data->getSert(),10));
    cod.push_back(block(6.25,100.5,86.25,7,data->adr(),10));
    cod.push_back(ean13(50,13.75,data->eanGr(),12.5,0.375));
    cod.push_back(otkStamp(60,37));
    cod.push_back(print());
    return cod;
}

LabelE4570::LabelE4570(QString nam, double w, double h, double g, FormData *d, QObject *parent) : LabelBase(nam,w,h,g,d,parent)
{

}

QString LabelE4570::getCod()
{
    QString cod=LabelBase::getCod();
    cod.push_back(logo(2,2));
    cod.push_back(text(2.5,35,QString::fromUtf8("Марка - ")+data->marka(),10));
    cod.push_back(text(2.5,39,QString::fromUtf8("Диаметр, мм - ")+data->diametr(),10));
    cod.push_back(text(2.5,43,QString::fromUtf8("Плавка - ")+data->plavka(),10));
    cod.push_back(text(2.5,47,QString::fromUtf8("Партия - ")+data->part(),10));
    cod.push_back(text(2.5,51,QString::fromUtf8("Тип носителя - ")+data->spool(),10));
    cod.push_back(text(2.5,55,QString::fromUtf8("Код продукции - ")+data->codeProd(),10));
    cod.push_back(text(2.5,59,QString::fromUtf8("Масса нетто, кг - ")+data->mas(),10));
    cod.push_back(text(2.5,63,QString::fromUtf8("Дата изг. - ")+data->datePart(),10));
    cod.push_back(ean13(5,20.5,data->eanEd(),9,0.375,0));
    cod.push_back(otkStamp(33,40));
    cod.push_back(print());
    return cod;
}

LabelG100100::LabelG100100(QString nam, double w, double h, double g, FormData *d, QObject *parent) : LabelBase(nam,w,h,g,d,parent)
{

}

QString LabelG100100::getCod()
{
    QString cod=LabelBase::getCod();
    cod.push_back(logo(6.25,6.25));
    cod.push_back(text(6.25,25,QString::fromUtf8("Проволока сварочная"),12));
    cod.push_back(text(45,24.375,data->marka(),14));
    cod.push_back(block(6.25,30,86.25,10,data->gost(),12));
    cod.push_back(block(6.25,40,86.25,15,data->description(),10));
    cod.push_back(text(6.25,55,QString::fromUtf8("Диаметр, мм - ")+data->diametr(),12));
    cod.push_back(text(6.25,60,QString::fromUtf8("Плавка - ")+data->plavka(),12));
    cod.push_back(text(6.25,65,QString::fromUtf8("Партия № ")+data->part(),12));
    cod.push_back(text(6.25,70,QString::fromUtf8("Тип носителя - ")+data->spool(),12));
    cod.push_back(text(45,55,QString::fromUtf8("Дата изг. - ")+data->datePart(),12));
    cod.push_back(text(45,60,QString::fromUtf8("Масса нетто, кг - ")+data->mas(),12));
    cod.push_back(text(45,65,QString::fromUtf8("Упаковщик № ")+data->upkNum(),12));
    cod.push_back(block(6.25,75,86.25,15,data->getSert(),10));
    cod.push_back(block(6.25,90,86.25,7,data->adr(),10));
    cod.push_back(ean13(50,6.25,data->eanGr(),12.5,0.375));
    cod.push_back(otkStamp(60,29.5));
    cod.push_back(print());
    return cod;
}

LabelG100100Pal::LabelG100100Pal(QString nam, double w, double h, double g, FormData *d, QObject *parent) : LabelBase(nam,w,h,g,d,parent)
{

}

QString LabelG100100Pal::getCod()
{
    QString cod=LabelBase::getCod();
    cod.push_back(logo(31,6.25));
    cod.push_back(text(6.25,30,QString::fromUtf8("Марка - ")+data->marka(),12));
    cod.push_back(text(6.25,35,QString::fromUtf8("Диаметр, мм - ")+data->diametr(),12));
    cod.push_back(text(6.25,40,QString::fromUtf8("Плавка - ")+data->plavka(),12));
    cod.push_back(text(6.25,45,QString::fromUtf8("Партия - ")+data->part(),12));
    cod.push_back(text(6.25,50,QString::fromUtf8("Тип носителя - ")+data->spool(),12));
    cod.push_back(text(6.25,55,QString::fromUtf8("Количество кассет - ")+data->kvoSpool(),12));
    cod.push_back(text(6.25,60,QString::fromUtf8("Масса нетто, кг - ")+data->mas(),12));
    cod.push_back(text(6.25,65,QString::fromUtf8("Мастер - ")+data->master(),12));
    cod.push_back(text(6.25,70,QString::fromUtf8("ОТК - ")+data->otkNam(),12));
    cod.push_back(text(6.25,75,QString::fromUtf8("Дата - ")+data->datePack(),12));
    cod.push_back(text(6.25,85,QString::fromUtf8("НЕ БРОСАТЬ!"),14));
    cod.push_back(print());
    return cod;
}
