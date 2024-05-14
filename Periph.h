#ifndef PERIPH_H
#define PERIPH_H

#include <QList>
#include <QString>
#include <QPushButton>

#include <QDebug>

#include "pin.h"
#include "mcu.h"

#include "lib/Periph/DATA/DATA.h"
#include "lib/Periph/ADC/ADC.h"
#include "lib/Periph/EXT/EXT.h"
#include "lib/Periph/I2C/I2C.h"
#include "lib/Periph/TIM/TIM.h"
#include "lib/Periph/UART/UART.h"

#define WIDTH 60
#define HEIGHT 25

#define STEP_Y HEIGHT+5

#define CREATE_BUTTON_PERIPH(_LIST_,_STR_) { \
                                                if(0 != mcu->_LIST_.size()){ \
                                                    ButtonPeriph.append(new QPushButton(pointer_class_Ui)); \
                                                \
                                                    ButtonPeriph[ButtonPeriph.size() - 1]->setText(_STR_); \
                                                    ButtonPeriph[ButtonPeriph.size() - 1]->setFixedSize(WIDTH, HEIGHT); \
                                                    ButtonPeriph[ButtonPeriph.size() - 1]->move(POSITION_X, Position_Y+=STEP_Y); \
                                                \
                                                    ButtonPeriph[ButtonPeriph.size() - 1]->show(); \
                                                } \
                                            }

#define CREATE_CONNECT_DETAIL(_PB_,_IND_,_LIST_,_UI_,_M_X_,_M_Y_,_S_X_,_S_Y_) { \
                                                                                QObject::connect(_PB_, &QPushButton::clicked, [=](){ \
                                                                                    mcu->ClearAllModeSettingsUi(); \
                                                                                    mcu->_LIST_[_IND_]->CreateUi(_UI_,_M_X_,_M_Y_,_S_X_,_S_Y_); \
                                                                                }); \
                                                                            }

#define CREATE_BUTTON_DETAIL(_LIST_,_STR_,_UI_,_M_X_,_M_Y_,_S_X_,_S_Y_) { \
                                                                            for(uint16_t i=0; i<mcu->_LIST_.size(); i++){ \
                                                                                ButtonDetail.append(new QPushButton(pointer_class_Ui)); \
                                                                            \
                                                                                ButtonDetail[ButtonDetail.size() - 1]->setText(mcu->_LIST_[i]->Name); \
                                                                                ButtonDetail[ButtonDetail.size() - 1]->setFixedSize(WIDTH, HEIGHT); \
                                                                                ButtonDetail[ButtonDetail.size() - 1]->move(POSITION_X, Position_Y+=STEP_Y); \
                                                                            \
                                                                                ButtonDetail[ButtonDetail.size() - 1]->show(); \
                                                                                \
                                                                                CREATE_CONNECT_DETAIL(ButtonDetail[ButtonDetail.size()-1],i,_LIST_,_UI_,_M_X_,_M_Y_,_S_X_,_S_Y_); \
                                                                            } \
                                                                        }

#define CLEAR_DETAIL()                     { \
                                                for(uint16_t i=0; i<(ButtonDetail.size()); i++){ \
                                                    delete ButtonDetail[i]; \
                                                } \
                                                ButtonDetail.clear(); \
                                                Position_Y = offset_y; \
                                           }

#define CREATE_CONNECT_PERIPH(_LIST_,_STR_,_UI_,_M_X_,_M_Y_,_S_X_,_S_Y_) { \
                                                                            foreach(QPushButton *t, ButtonPeriph){ \
                                                                                if(_STR_ == t->text()){ \
                                                                                    QObject::connect(t, &QPushButton::clicked, [=](){ \
                                                                                        CLEAR_DETAIL(); \
                                                                                        mcu->ClearAllModeSettingsUi(); \
                                                                                        CREATE_BUTTON_DETAIL(_LIST_,_STR_,_UI_,_M_X_,_M_Y_,_S_X_,_S_Y_); \
                                                                                    }); \
                                                                                } \
                                                                            } \
                                                                        }

class Periph  : public QPushButton
{

    Q_OBJECT

public:
    Periph(QWidget *parent = nullptr);
    ~Periph();

    QList<QPushButton*> ButtonPeriph;

    QList<QPushButton*> ButtonDetail;

    QString Name;

protected:

public slots:

    void    CreatePeriphButton(QMainWindow* pointer_class_Ui, MCU *mcu, uint16_t offset_x, uint16_t offset_y);
    void    CreateConnectPeriphDetailButtonConnectDetail(QMainWindow* pointer_class_Ui, MCU *mcu, uint16_t offset_x, uint16_t offset_y,
                                                         uint16_t offset_mode_x, uint16_t offset_mode_y, uint16_t offset_settings_x, uint16_t offset_settings_y);

    void    ClearDetailModeSettingsUi(); //MCU *mcu

private slots:

private:
    MCU *m_mcu;
};


#endif // PERIPH_H
