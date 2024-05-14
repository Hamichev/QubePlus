#include "mcu.h"

#include <QPushButton>
#include <QObject>

#include <QDebug>

MCU::MCU()
{
    ;
}

MCU::~MCU()
{
    ;
}

void MCU::CreateMCU(QMainWindow* pointer_class_Ui, MCU *mcu,  QList<Pin*> *list_Pin, uint16_t *counter_Pin, QString name_mcu, uint16_t number_pins, uint16_t index_first_pin, uint8_t is_reverse){

#define START_POSITION_X 500
#define START_POSITION_Y 50

#define SIZE_PIN_WIDTH_VERTICAL 25
/*
 *             |
 *            \./
 *          .____.
 *          |    |
 *          |    |
 *          |    | <-.
 *          |    |   |
 *          .____.   |
*/
#define SIZE_PIN_HEIGHT_VERTICAL 60

#define SIZE_PIN_WIDTH_HORIZON SIZE_PIN_HEIGHT_VERTICAL
#define SIZE_PIN_HEIGHT_HORIZON SIZE_PIN_WIDTH_VERTICAL

#define INTERVAL 1
#define OFFSET 1

    uint16_t ind;

    if(number_pins%4 != 0){
        qDebug() << "Не делится на 4";
        return;
    }

    for((*counter_Pin)=0; (*counter_Pin)<(number_pins+1); (*counter_Pin)++){ //+1 - this is central big button
        list_Pin->append(new Pin(pointer_class_Ui));

        if(((1 != index_first_pin) || (0 != index_first_pin)) && (*counter_Pin) != 0){
            if(is_reverse){
                ind = ((index_first_pin+1)-(*counter_Pin)); //+1
                if(ind < 1)
                    ind+=number_pins;
            }
            else{
                ind = ((index_first_pin+1)+(*counter_Pin)); //+1
                if(ind > number_pins)
                    ind-=number_pins;
            }
        }
        else{
            ind = (*counter_Pin);
        }

        if(ind == 0){
            ((*list_Pin)[*counter_Pin])->setText(QString::number(ind));
            ((*list_Pin)[*counter_Pin])->setFixedSize((SIZE_PIN_WIDTH_VERTICAL+INTERVAL)*(number_pins*1/4), (SIZE_PIN_HEIGHT_HORIZON+INTERVAL)*(number_pins*1/4));
            ((*list_Pin)[*counter_Pin])->move(START_POSITION_X+(SIZE_PIN_WIDTH_HORIZON+INTERVAL), START_POSITION_Y+(SIZE_PIN_HEIGHT_VERTICAL+INTERVAL));

            mcu->Name = name_mcu;
            mcu->Number_Pins = number_pins;
        }
        else if(ind<=(number_pins*1/4)){
            ((*list_Pin)[*counter_Pin])->setText(QString::number(ind));
            ((*list_Pin)[*counter_Pin])->setFixedSize(SIZE_PIN_WIDTH_VERTICAL, SIZE_PIN_HEIGHT_VERTICAL);
            ((*list_Pin)[*counter_Pin])->move(START_POSITION_X+(SIZE_PIN_WIDTH_HORIZON+INTERVAL)+(SIZE_PIN_WIDTH_VERTICAL+INTERVAL)*((ind)-OFFSET),
                                              START_POSITION_Y);
            ((*list_Pin)[*counter_Pin])->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
            ((*list_Pin)[*counter_Pin])->setOrientation(Pin::VerticalBottomToTop);
        }
        else if(ind<=(number_pins*2/4)){
            ((*list_Pin)[*counter_Pin])->setText(QString::number(ind));
            ((*list_Pin)[*counter_Pin])->setFixedSize(SIZE_PIN_WIDTH_HORIZON, SIZE_PIN_HEIGHT_HORIZON);
            ((*list_Pin)[*counter_Pin])->move(START_POSITION_X+(SIZE_PIN_WIDTH_HORIZON+INTERVAL)+(SIZE_PIN_WIDTH_VERTICAL+INTERVAL)*(number_pins*1/4),
                                              START_POSITION_Y+(SIZE_PIN_HEIGHT_HORIZON+INTERVAL)*((ind)-(number_pins*1/4) - OFFSET) + (SIZE_PIN_HEIGHT_VERTICAL+INTERVAL));
        }
        else if(ind<=(number_pins*3/4)){
            ((*list_Pin)[*counter_Pin])->setText(QString::number(ind));
            ((*list_Pin)[*counter_Pin])->setFixedSize(SIZE_PIN_WIDTH_VERTICAL, SIZE_PIN_HEIGHT_VERTICAL);
            ((*list_Pin)[*counter_Pin])->move(START_POSITION_X+(SIZE_PIN_WIDTH_HORIZON+INTERVAL)+(SIZE_PIN_WIDTH_VERTICAL+INTERVAL)*((number_pins*1/4)-((ind)-number_pins*2/4)),
                                              START_POSITION_Y+(SIZE_PIN_HEIGHT_HORIZON+INTERVAL)*((number_pins*1/4))+(SIZE_PIN_HEIGHT_VERTICAL+INTERVAL));
            ((*list_Pin)[*counter_Pin])->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
            ((*list_Pin)[*counter_Pin])->setOrientation(Pin::VerticalBottomToTop);
        }
        else if(ind<=(number_pins*4/4)){
            ((*list_Pin)[*counter_Pin])->setText(QString::number(ind));
            ((*list_Pin)[*counter_Pin])->setFixedSize(SIZE_PIN_WIDTH_HORIZON, SIZE_PIN_HEIGHT_HORIZON);
            ((*list_Pin)[*counter_Pin])->move(START_POSITION_X,
                                              START_POSITION_Y+(SIZE_PIN_HEIGHT_HORIZON+INTERVAL)*((number_pins*1/4)-((ind)-number_pins*3/4))+(SIZE_PIN_HEIGHT_VERTICAL+INTERVAL));
        }

        (*list_Pin)[*counter_Pin]->show();
    }
}

void MCU::SetConnectClickedMCU(MCU *mcu, Pin *PB_MCU)
{
    Q_UNUSED(mcu);
    Q_UNUSED(PB_MCU);
    /*
    QObject::connect(PB_MCU, &QPushButton::clicked, [=](){
        //qDebug() << i;
        qDebug() << (*mcu).Name;
    });
    */
}

void MCU::ClearAllModeSettingsUi()
{
#define CLEAR_UI(_TYPE_,_LIST_) { \
                                    foreach(_TYPE_ *t, _LIST_){ \
                                        t->ClearUi(); \
                                    } \
                                }

    CLEAR_UI(DATA,L_DATA);
    CLEAR_UI(ADC,L_ADC);
    CLEAR_UI(EXT,L_EXT);
    CLEAR_UI(I2C,L_I2C);
    CLEAR_UI(TIM,L_TIM);
    CLEAR_UI(UART,L_UART);
}

void MCU::SetConnectClickedPin(MCU *mcu, QList<QPushButton*> *list_ButtonPeriph, QList<QPushButton*> *list_ButtonDetail, QList<Pin*> *list_Pin)
{

struct {
    int8_t data = -1;
    int8_t adc = -1;
    int8_t ext = -1;
    int8_t i2c = -1;
    int8_t tim = -1;
    int8_t uart = -1;
} ind_periph;

#define CHECK_BUTTON_PERIPH(_STR_,_DATA_,_IND_) { \
                                                    if(_STR_ == (*list_ButtonPeriph)[_IND_]->text()){ \
                                                         _DATA_ = _IND_; \
                                                    } \
                                                  }

#define CHANGE_ENABLED_BUTTON_PERIPH(_IND_PIN_,_LS_,_IND_) { \
                                                                if(0 != (*list_Pin)[_IND_PIN_]->_LS_.size()){ \
                                                                    if(-1 != _IND_) (*list_ButtonPeriph)[_IND_]->setEnabled(true); \
                                                                } \
                                                                else{ \
                                                                    if(-1 != _IND_) (*list_ButtonPeriph)[_IND_]->setEnabled(false); \
                                                                } \
                                                           }

    for(uint16_t i=0; i<(*list_ButtonPeriph).size(); i++){
        CHECK_BUTTON_PERIPH("DATA", ind_periph.data, i);
        CHECK_BUTTON_PERIPH("ADC", ind_periph.adc, i);
        CHECK_BUTTON_PERIPH("EXT", ind_periph.ext, i);
        CHECK_BUTTON_PERIPH("I2C", ind_periph.i2c, i);
        CHECK_BUTTON_PERIPH("TIM", ind_periph.tim, i);
        CHECK_BUTTON_PERIPH("UART", ind_periph.uart, i);
    }

    for(uint16_t i=0; i<(*list_Pin).size(); i++){
        QObject::connect((*list_Pin)[i], &Pin::clicked, [=](){

            for(uint16_t i=0; i<((*list_ButtonDetail).size()); i++){
                delete (*list_ButtonDetail)[i];
            }
            (*list_ButtonDetail).clear();

            mcu->ClearAllModeSettingsUi();

            if(0 == i){
                for(uint16_t j=0; j<(*list_ButtonPeriph).size(); j++){
                    (*list_ButtonPeriph)[j]->setEnabled(true);
                }
            }
            else{
                CHANGE_ENABLED_BUTTON_PERIPH(i, LS_DATA_Name, ind_periph.data);
                CHANGE_ENABLED_BUTTON_PERIPH(i, LS_ADC_Name, ind_periph.adc);
                CHANGE_ENABLED_BUTTON_PERIPH(i, LS_EXT_Name, ind_periph.ext);
                CHANGE_ENABLED_BUTTON_PERIPH(i, LS_I2C_Name, ind_periph.i2c);
                CHANGE_ENABLED_BUTTON_PERIPH(i, LS_TIM_Name, ind_periph.tim);
                CHANGE_ENABLED_BUTTON_PERIPH(i, LS_UART_Name, ind_periph.uart);
            }

            for(uint8_t j=0; j<(*list_Pin)[i]->functional.size(); j++){
                if("ADC1" == (*list_Pin)[i]->functional[j]){
                    ;
                }
                else if("I2C1" == (*list_Pin)[i]->functional[j]){
                    ;
                }
            }
        });
    }
}
