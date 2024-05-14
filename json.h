#ifndef JSON_H
#define JSON_H

#include <QMainWindow>

#include <QFile>
#include <QDir>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QList>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QFont>

#include <QDebug>

#include "pin.h"
#include "mcu.h"
#include "Periph.h"

#include "lib/Periph/ADC/ADC.h"
#include "lib/Periph/EXT/EXT.h"
#include "lib/Periph/I2C/I2C.h"
#include "lib/Periph/TIM/TIM.h"
#include "lib/Periph/UART/UART.h"

QJsonObject ReadJson(QString name_file);

void ReadConfigMCU(MCU *mcu, QList<Pin*> *list_Pin);
void ReadConfigProject(QList<Pin*> *list_Pin, QString name_Project);

void WriteProject(MCU *mcu, QList<Pin*> *list_Pin, Periph *periph, QString name_Project);
void ReadProject(QString config, MCU *mcu, QList<Pin *> *list_Pin, Periph *periph, QString *Name_project, QLineEdit* LE_mcu);

#endif // JSON_H
