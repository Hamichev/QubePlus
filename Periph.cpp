#include "Periph.h"

#include <QPainter>
#include <QStyleOptionButton>
#include <QDebug>
#include <QStylePainter>

Periph::Periph(QWidget *parent) : QPushButton(parent)
{
    ;
}

Periph::~Periph()
{
    ;
}

void Periph::CreatePeriphButton(QMainWindow* pointer_class_Ui, MCU *mcu, uint16_t offset_x, uint16_t offset_y)
{
#define POSITION_X offset_x+10

    m_mcu = mcu;

    uint16_t Position_Y = offset_y;


    CREATE_BUTTON_PERIPH(L_DATA,"DATA");
    CREATE_BUTTON_PERIPH(L_ADC,"ADC");
    CREATE_BUTTON_PERIPH(L_EXT,"EXT");
    CREATE_BUTTON_PERIPH(L_I2C,"I2C");
    CREATE_BUTTON_PERIPH(L_TIM,"TIM");
    CREATE_BUTTON_PERIPH(L_UART,"UART");

}

void Periph::CreateConnectPeriphDetailButtonConnectDetail(QMainWindow* pointer_class_Ui, MCU *mcu, uint16_t offset_x, uint16_t offset_y,
                                                          uint16_t offset_mode_x, uint16_t offset_mode_y, uint16_t offset_settings_x, uint16_t offset_settings_y)
{
#define POSITION_X offset_x+5

static uint16_t Position_Y = offset_y;

    foreach(QPushButton *t, ButtonPeriph){
        if("DATA" == t->text()){
            QObject::connect(t, &QPushButton::clicked, [=](){
                CLEAR_DETAIL();
                mcu->ClearAllModeSettingsUi();
                CREATE_BUTTON_DETAIL(L_DATA,"DATA",pointer_class_Ui,offset_mode_x,offset_mode_y,offset_settings_x,offset_settings_y); \
            });
        }
    }

    //CREATE_CONNECT_PERIPH(L_DATA,"DATA",pointer_class_Ui,offset_mode_x,offset_mode_y,offset_settings_x,offset_settings_y);
    CREATE_CONNECT_PERIPH(L_ADC,"ADC",pointer_class_Ui,offset_mode_x,offset_mode_y,offset_settings_x,offset_settings_y);
    CREATE_CONNECT_PERIPH(L_EXT,"EXT",pointer_class_Ui,offset_mode_x,offset_mode_y,offset_settings_x,offset_settings_y);
    CREATE_CONNECT_PERIPH(L_I2C,"I2C",pointer_class_Ui,offset_mode_x,offset_mode_y,offset_settings_x,offset_settings_y);
    CREATE_CONNECT_PERIPH(L_TIM,"TIM",pointer_class_Ui,offset_mode_x,offset_mode_y,offset_settings_x,offset_settings_y);
    CREATE_CONNECT_PERIPH(L_UART,"UART",pointer_class_Ui,offset_mode_x,offset_mode_y,offset_settings_x,offset_settings_y);

}

void Periph::ClearDetailModeSettingsUi()//(MCU *mcu)
{
    for(uint16_t i=0; i<(ButtonDetail.size()); i++){
        delete ButtonDetail[i];
    }
    ButtonDetail.clear();

    //m_mcu->ClearAllModeUi();

#define CLEAR_UI(_TYPE_,_LIST_) { \
                                    if(_LIST_.size() != 0){ \
                                        foreach(_TYPE_ *t, _LIST_){ \
                                            t->ClearUi(); \
                                        } \
                                    } \
                                }

    CLEAR_UI(DATA,m_mcu->L_DATA);
    CLEAR_UI(ADC,m_mcu->L_ADC);
    CLEAR_UI(EXT,m_mcu->L_EXT);
    CLEAR_UI(I2C,m_mcu->L_I2C);
    CLEAR_UI(TIM,m_mcu->L_TIM);
    CLEAR_UI(UART,m_mcu->L_UART);
}
