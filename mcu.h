#ifndef MCU_H
#define MCU_H

#include <QMainWindow>

#include <QList>
#include <QPushButton>
#include <QTransform>
#include <QApplication>

#include "pin.h"

#include "lib/Periph/DATA/DATA.h"
#include "lib/Periph/ADC/ADC.h"
#include "lib/Periph/EXT/EXT.h"
#include "lib/Periph/I2C/I2C.h"
#include "lib/Periph/TIM/TIM.h"
#include "lib/Periph/UART/UART.h"

class MCU
{
public:
    MCU();
    ~MCU();


    QList<DATA*> L_DATA;
    QList<ADC*> L_ADC;
    QList<EXT*> L_EXT;
    QList<I2C*> L_I2C;
    QList<TIM*> L_TIM;
    QList<UART*> L_UART;

    QString Name;
    uint8_t isReady = 0;

    uint32_t Number_Pins;

protected:

public slots:

    void CreateMCU(QMainWindow* pointer_class_Ui, MCU *mcu,  QList<Pin*> *list_Pin, uint16_t *counter_Pin, QString name_mcu, uint16_t number_pins, uint16_t index_first_pin, uint8_t is_reverse);

    void SetConnectClickedMCU(MCU *mcu, Pin *PB_MCU);

    void ClearAllModeSettingsUi();

    void SetConnectClickedPin(MCU *mcu, QList<QPushButton*> *list_ButtonPeriph, QList<QPushButton*> *list_ButtonDetail, QList<Pin*> *list_Pin);

private slots:

private:

};



#endif // MCU_H
