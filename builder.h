#ifndef BUILDER_H
#define BUILDER_H

#include "lib/Periph/DATA/DATA.h"
#include "lib/Periph/ADC/ADC.h"
#include "lib/Periph/EXT/EXT.h"
#include "lib/Periph/I2C/I2C.h"
#include "lib/Periph/TIM/TIM.h"
#include "lib/Periph/UART/UART.h"

#include "mcu.h"
#include "pin.h"

#include <QFile>
#include <QTextStream>

#include <QMessageBox>



class Builder
{
public:
    Builder();

    void Init(QMainWindow* pointer_class_Ui, MCU *mcu, QList<Pin*> *list_Pin);

    void buildCurrentProject(QString Name_project);

private slots:
    void addStringFile(QString header);

    void addNewBuild();

    void readDATAconfig();
    void readADCconfig();
    void readUARTconfig();

    void ClearAllList();

private:
    QMainWindow* m_pointer_class_Ui;
    MCU *m_mcu;
    QList<Pin*> *m_list_Pin;

    QStringList m_Include;
    QStringList m_Prototype_Func;
    QStringList m_Init_struct;
    QStringList m_Init_config;
    QStringList m_Call_Func;
    QStringList m_Result;
    QStringList m_Func;

};



#endif // BUILDER_H
