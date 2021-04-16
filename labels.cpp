#include "labels.h"

LabelE801016::LabelE801016(QString nam, double w, double h, double g, FormData *d, QObject *parent) : LabelBase(nam,w,h,g,d,parent)
{

}

QString LabelE801016::getCod()
{
    QString cod=LabelBase::getCod();
    cod.push_back(logo(15,13.75));
    cod.push_back(text(6.25,43.75,QString::fromUtf8("Марка - ")+data->marka(),12));
    cod.push_back(text(6.25,48.75,QString::fromUtf8("Диаметр, мм - ")+data->diametr(),12));
    cod.push_back(text(6.25,53.75,QString::fromUtf8("Плавка - ")+data->plavka(),12));
    cod.push_back(text(6.25,58.75,QString::fromUtf8("Партия - ")+data->part(),12));
    cod.push_back(text(6.25,63.75,QString::fromUtf8("Тип носителя - ")+data->spool(),12));
    cod.push_back(text(6.25,68.75,QString::fromUtf8("Код продукции - ")+data->codeProd(),12));
    cod.push_back(text(6.25,73.75,QString::fromUtf8("Масса нетто, кг - ")+data->mas(),12));
    cod.push_back(text(6.25,78.75,QString::fromUtf8("Дата изг. - ")+data->datePart(),12));
    cod.push_back(ean13(75,43.75,data->eanEd(),17.5,0.375,90));
    cod.push_back(otkStamp(55,20));
    cod.push_back(print());
    /*cod.push_back(QString::fromUtf8("PUTBMP %1,%2, \"logo.BMP\",1,100\n").arg(getDots(15,dpi)).arg(getDots(13.75,dpi)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Марка - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(43.75,dpi)).arg(ui->lineEditMark->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Диаметр, мм - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(48.75,dpi)).arg(QLocale().toString(ui->lineEditDiam->text().toDouble(),'f',1)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Плавка - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(53.75,dpi)).arg(ui->lineEditPlav->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Партия - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(58.75,dpi)).arg(ui->lineEditPart->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Тип носителя - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(63.75,dpi)).arg(ui->lineEditSpool->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Код продукции - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(68.75,dpi)).arg(getCod()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Масса нетто, кг - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(73.75,dpi)).arg(ui->lineEditKvo->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Дата изг. - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(78.75,dpi)).arg(ui->dateEdit->date().toString("dd.MM.yyyy")));
    if (ui->checkBoxEan->isChecked() && !ui->lineEditEanEd->text().isEmpty()){
        cod.push_back(QString("BARCODE %1,%2,\"EAN13\",%3,2,90,%4,%5,\"%6\"\n").arg(getDots(75,dpi)).arg(getDots(43.75,dpi)).arg(getDots(17.5,dpi)).arg(getDots(0.375,dpi)).arg(getDots(0.375,dpi)).arg(ui->lineEditEanEd->text().left(12)));
    }
    cod.push_back(getOtkStamp(55,20,dpi));
    cod.push_back(QString("PRINT %1\n").arg(ui->spinBox->value()));*/
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
    /*cod.push_back(QString("PUTBMP %1,%2,\"logo.BMP\",1,100\n").arg(getDots(6.25,dpi)).arg(getDots(13.75,dpi)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Проволока сварочная\"\n").arg(getDots(6.25,dpi)).arg(getDots(32.5,dpi)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,14,14,\"%3\"\n").arg(getDots(45,dpi)).arg(getDots(31.875,dpi)).arg(ui->lineEditMark->text()));
    cod.push_back(QString::fromUtf8("BLOCK %1,%2,%3,%4,\"0\",0,12,12,0,0,1,\"%5\"\n").arg(getDots(6.25,dpi)).arg(getDots(37.5,dpi)).arg(getDots(86.25,dpi)).arg(getDots(10,dpi)).arg(strGost()));
    cod.push_back(QString::fromUtf8("BLOCK %1,%2,%3,%4,\"0\",0,10,10,0,0,1,\"%5\"\n").arg(getDots(6.25,dpi)).arg(getDots(47.5,dpi)).arg(getDots(86.25,dpi)).arg(getDots(15,dpi)).arg(ui->plainTextEdit->toPlainText()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Диаметр, мм - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(62.5,dpi)).arg(QLocale().toString(ui->lineEditDiam->text().toDouble(),'f',1)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Плавка - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(67.5,dpi)).arg(ui->lineEditPlav->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Партия № %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(72.5,dpi)).arg(ui->lineEditPart->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Тип носителя - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(77.5,dpi)).arg(ui->lineEditSpool->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Дата изг. - %3\"\n").arg(getDots(45,dpi)).arg(getDots(62.5,dpi)).arg(ui->dateEdit->date().toString("dd.MM.yyyy")));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Масса нетто, кг - %3\"\n").arg(getDots(45,dpi)).arg(getDots(67.5,dpi)).arg(ui->lineEditKvo->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Упаковщик № %3\"\n").arg(getDots(45,dpi)).arg(getDots(72.5,dpi)).arg(ui->lineEditUpk->text()));
    cod.push_back(QString::fromUtf8("BLOCK %1,%2,%3,%4,\"0\",0,10,10,0,0,1,\"%5\"\n").arg(getDots(6.25,dpi)).arg(getDots(82.5,dpi)).arg(getDots(86.25,dpi)).arg(getDots(18,dpi)).arg(getSert()));
    cod.push_back(QString::fromUtf8("BLOCK %1,%2,%3,%4,\"0\",0,10,10,0,0,1,\"%5\"\n").arg(getDots(6.25,dpi)).arg(getDots(100.5,dpi)).arg(getDots(86.25,dpi)).arg(getDots(7,dpi)).arg(strAdr));
    if (ui->checkBoxEan->isChecked() && !getEanPack().isEmpty()){
        cod.push_back(QString("BARCODE %1,%2,\"EAN13\",%3,2,0,%4,%5,\"%6\"\n").arg(getDots(50,dpi)).arg(getDots(13.75,dpi)).arg(getDots(12.5,dpi)).arg(getDots(0.375,dpi)).arg(getDots(0.375,dpi)).arg(getEanPack()));
    }
    cod.push_back(getOtkStamp(60,37,dpi));
    cod.push_back(QString("PRINT %1\n").arg(ui->spinBox->value()));*/
    return cod;
}

LabelE4570::LabelE4570(QString nam, double w, double h, double g, FormData *d, QObject *parent) : LabelBase(nam,w,h,g,d,parent)
{

}

QString LabelE4570::getCod()
{
    QString cod=LabelBase::getCod();
    cod.push_back(logo(2,2));
    cod.push_back(text(5,35,QString::fromUtf8("Марка - ")+data->marka(),10));
    cod.push_back(text(5,39,QString::fromUtf8("Диаметр, мм - ")+data->diametr(),10));
    cod.push_back(text(5,43,QString::fromUtf8("Плавка - ")+data->plavka(),10));
    cod.push_back(text(5,47,QString::fromUtf8("Партия - ")+data->part(),10));
    cod.push_back(text(5,51,QString::fromUtf8("Тип носителя - ")+data->spool(),10));
    cod.push_back(text(5,55,QString::fromUtf8("Код продукции - ")+data->codeProd(),10));
    cod.push_back(text(5,59,QString::fromUtf8("Масса нетто, кг - ")+data->mas(),10));
    cod.push_back(text(5,63,QString::fromUtf8("Дата изг. - ")+data->datePart(),10));
    cod.push_back(ean13(5,20.5,data->eanEd(),9,0.375,0));
    cod.push_back(otkStamp(31,40));
    cod.push_back(print());
    /*cod.push_back(QString::fromUtf8("PUTBMP %1,%2, \"logo.BMP\",1,100\n").arg(getDots(2,dpi)).arg(getDots(2,dpi)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Марка - %3\"\n").arg(getDots(5,dpi)).arg(getDots(35,dpi)).arg(ui->lineEditMark->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Диаметр, мм - %3\"\n").arg(getDots(5,dpi)).arg(getDots(39,dpi)).arg(QLocale().toString(ui->lineEditDiam->text().toDouble(),'f',1)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Плавка - %3\"\n").arg(getDots(5,dpi)).arg(getDots(43,dpi)).arg(ui->lineEditPlav->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Партия - %3\"\n").arg(getDots(5,dpi)).arg(getDots(47,dpi)).arg(ui->lineEditPart->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Тип носителя - %3\"\n").arg(getDots(5,dpi)).arg(getDots(51,dpi)).arg(ui->lineEditSpool->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Код продукции - %3\"\n").arg(getDots(5,dpi)).arg(getDots(55,dpi)).arg(getCod()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Масса нетто, кг - %3\"\n").arg(getDots(5,dpi)).arg(getDots(59,dpi)).arg(ui->lineEditKvo->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Дата изг. - %3\"\n").arg(getDots(5,dpi)).arg(getDots(63,dpi)).arg(ui->dateEdit->date().toString("dd.MM.yyyy")));
    if (ui->checkBoxEan->isChecked() && !ui->lineEditEanEd->text().isEmpty()){
        cod.push_back(QString("BARCODE %1,%2,\"EAN13\",%3,2,0,%4,%5,\"%6\"\n").arg(getDots(5,dpi)).arg(getDots(20.5,dpi)).arg(getDots(9,dpi)).arg(getDots(0.375,dpi)).arg(getDots(0.375,dpi)).arg(ui->lineEditEanEd->text().left(12)));
    }
    cod.push_back(getOtkStamp(31,40,dpi));
    cod.push_back(QString("PRINT %1\n").arg(ui->spinBox->value()));*/
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
    cod.push_back(block(6.25,75,86.25,18,data->getSert(),10));
    cod.push_back(block(6.25,93,86.25,6.75,data->adr(),10));
    cod.push_back(ean13(50,6.25,data->eanGr(),12.5,0.375));
    cod.push_back(otkStamp(60,29.5));
    cod.push_back(print());
    /*cod.push_back(QString("PUTBMP %1,%2,\"logo.BMP\",1,100\n").arg(getDots(6.25,dpi)).arg(getDots(6.25,dpi)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Проволока сварочная\"\n").arg(getDots(6.25,dpi)).arg(getDots(25,dpi)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,14,14,\"%3\"\n").arg(getDots(45,dpi)).arg(getDots(24.375,dpi)).arg(ui->lineEditMark->text()));
    cod.push_back(QString::fromUtf8("BLOCK %1,%2,%3,%4,\"0\",0,12,12,0,0,1,\"%5\"\n").arg(getDots(6.25,dpi)).arg(getDots(30,dpi)).arg(getDots(86.25,dpi)).arg(getDots(10,dpi)).arg(strGost()));
    cod.push_back(QString::fromUtf8("BLOCK %1,%2,%3,%4,\"0\",0,10,10,0,0,1,\"%5\"\n").arg(getDots(6.25,dpi)).arg(getDots(40,dpi)).arg(getDots(86.25,dpi)).arg(getDots(15,dpi)).arg(ui->plainTextEdit->toPlainText()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Диаметр, мм - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(55,dpi)).arg(QLocale().toString(ui->lineEditDiam->text().toDouble(),'f',1)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Плавка - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(60,dpi)).arg(ui->lineEditPlav->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Партия № %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(65,dpi)).arg(ui->lineEditPart->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Тип носителя - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(70,dpi)).arg(ui->lineEditSpool->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Дата изг. - %3\"\n").arg(getDots(45,dpi)).arg(getDots(55,dpi)).arg(ui->dateEdit->date().toString("dd.MM.yyyy")));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Масса нетто, кг - %3\"\n").arg(getDots(45,dpi)).arg(getDots(60,dpi)).arg(ui->lineEditKvo->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Упаковщик № %3\"\n").arg(getDots(45,dpi)).arg(getDots(65,dpi)).arg(ui->lineEditUpk->text()));
    cod.push_back(QString::fromUtf8("BLOCK %1,%2,%3,%4,\"0\",0,10,10,0,0,1,\"%5\"\n").arg(getDots(6.25,dpi)).arg(getDots(75,dpi)).arg(getDots(86.25,dpi)).arg(getDots(18,dpi)).arg(getSert()));
    cod.push_back(QString::fromUtf8("BLOCK %1,%2,%3,%4,\"0\",0,10,10,0,0,1,\"%5\"\n").arg(getDots(6.25,dpi)).arg(getDots(93,dpi)).arg(getDots(86.25,dpi)).arg(getDots(6.75,dpi)).arg(strAdr));
    if (ui->checkBoxEan->isChecked() && !getEanPack().isEmpty()){
        cod.push_back(QString("BARCODE %1,%2,\"EAN13\",%3,2,0,%4,%5,\"%6\"\n").arg(getDots(50,dpi)).arg(getDots(6.25,dpi)).arg(getDots(12.5,dpi)).arg(getDots(0.375,dpi)).arg(getDots(0.375,dpi)).arg(getEanPack()));
    }
    cod.push_back(getOtkStamp(60,29.5,dpi));
    cod.push_back(QString("PRINT %1\n").arg(ui->spinBox->value()));*/
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
    /*cod.push_back(QString("PUTBMP %1,%2,\"logo.BMP\",1,100\n").arg(getDots(31,dpi)).arg(getDots(6.25,dpi)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Марка - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(30,dpi)).arg(ui->lineEditMark->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Диаметр, мм - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(35,dpi)).arg(QLocale().toString(ui->lineEditDiam->text().toDouble(),'f',1)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Плавка - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(40,dpi)).arg(ui->lineEditPlav->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Партия № %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(45,dpi)).arg(ui->lineEditPart->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Тип носителя - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(50,dpi)).arg(ui->lineEditSpool->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Количество кассет - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(55,dpi)).arg(ui->lineEditKvoSpool->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Масса нетто, кг - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(60,dpi)).arg(ui->lineEditKvo->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Мастер - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(65,dpi)).arg(ui->comboBoxMaster->currentText()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"ОТК - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(70,dpi)).arg(ui->comboBoxOtk->currentText()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Дата - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(75,dpi)).arg(ui->dateEditPack->date().toString("dd.MM.yyyy")));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,14,14,\"НЕ БРОСАТЬ!\"\n").arg(getDots(35,dpi)).arg(getDots(85,dpi)));
    cod.push_back(QString("PRINT %1\n").arg(ui->spinBox->value()));*/
    return cod;
}
