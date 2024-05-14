#include "../UART/UART.h"

#include <QPainter>
#include <QStyleOptionButton>
#include <QDebug>
#include <QStylePainter>

UART::UART()
{
    ;
}

UART::~UART()
{

}

void UART::CreateUi(QMainWindow *pointer_class_Ui, uint16_t offset_mode_x, uint16_t offset_mode_y, uint16_t offset_settings_x, uint16_t offset_settings_y)
{
    CreateModeUi(pointer_class_Ui, offset_mode_x, offset_mode_y);

    CreateSettingsUi(pointer_class_Ui, offset_settings_x, offset_settings_y);

}

void UART::ClearUi()
{
    Mode_Position_Y = 0;
    Settings_Position_Y = 0;

    if(CB_On != 0){
        CB_On->deleteLater();
        CB_On = 0;
    }

    if(L_TX != 0){
        L_TX->deleteLater();
        L_TX = 0;
    }

    if(CB_TX != 0){
        CB_TX->deleteLater();
        CB_TX = 0;
    }

    if(L_RX != 0){
        L_TX->deleteLater();
        L_TX = 0;
    }

    if(CB_RX != 0){
        CB_RX->deleteLater();
        CB_RX = 0;
    }

    if(L_Baudrate != 0){
        L_TX->deleteLater();
        L_TX = 0;
    }

    if(CB_Baudrate != 0){
        CB_Baudrate->deleteLater();
        CB_Baudrate = 0;
    }
}

QJsonObject UART::CreateJsonObject()
{
    QJsonObject DataObject;
    DataObject.insert("On", QJsonValue::fromVariant(this->On));
    DataObject.insert("TX", QJsonValue::fromVariant(this->TX));
    DataObject.insert("Func_TX", QJsonValue::fromVariant(this->Func_TX));
    DataObject.insert("RX", QJsonValue::fromVariant(this->RX));
    DataObject.insert("Func_RX", QJsonValue::fromVariant(this->Func_RX));
    DataObject.insert("Baudrate", QJsonValue::fromVariant(this->Baudrate));
    return DataObject;
}

void UART::ReadJsonValue(QJsonValue jv)
{
    this->On = jv.toObject().value("On").toInt();
    this->TX = jv.toObject().value("TX").toString();
    this->Func_TX = jv.toObject().value("Func_TX").toString();
    this->RX = jv.toObject().value("RX").toString();
    this->Func_RX = jv.toObject().value("Func_RX").toString();
    this->Baudrate = jv.toObject().value("Baudrate").toInt();
}

void UART::CreateModeUi(QMainWindow *pointer_class_Ui, uint16_t offset_x, uint16_t offset_y)
{
#define POSITION_X offset_x+5

    Mode_Position_Y = offset_y;

    CB_On = new QCheckBox(pointer_class_Ui);

    CB_On->setText(Name);
    CB_On->move(POSITION_X, Mode_Position_Y+=STEP_Y);

    QObject::connect(CB_On, &QCheckBox::stateChanged, [=](int ind){
        this->On = ind;
    });

    CB_On->setChecked(this->On);

    L_TX = new QLabel(pointer_class_Ui);
    L_TX->move(POSITION_X, Mode_Position_Y+=STEP_Y);
    L_TX->setText("TX:");

    CB_TX = new QComboBox(pointer_class_Ui);
    CB_TX->move(POSITION_X, Mode_Position_Y+=STEP_Y);
    CB_TX->resize(60,20);
    for(uint16_t i=0; i<SL_TX_pin.size(); i++) CB_TX->addItem(SL_TX_pin[i]);
    if("" != this->TX)
        CB_TX->setCurrentText(this->TX);
    else{
        TX = CB_TX->currentText();
        Func_TX = SL_TX_func[CB_TX->currentIndex()];
    }

    L_RX = new QLabel(pointer_class_Ui);
    L_RX->move(POSITION_X, Mode_Position_Y+=STEP_Y);
    L_RX->setText("RX:");

    CB_RX = new QComboBox(pointer_class_Ui);
    CB_RX->move(POSITION_X, Mode_Position_Y+=STEP_Y);
    CB_RX->resize(60,20);
    for(uint16_t i=0; i<SL_RX_pin.size(); i++) CB_RX->addItem(SL_RX_pin[i]);
    if("" != this->RX)
        CB_RX->setCurrentText(this->RX);
    else{
        RX = CB_RX->currentText();
        Func_RX = SL_RX_func[CB_RX->currentIndex()];
    }

    L_Baudrate = new QLabel(pointer_class_Ui);
    L_Baudrate->move(POSITION_X, Mode_Position_Y+=STEP_Y);
    L_Baudrate->setText("Baudrate:");

    CB_Baudrate = new QComboBox(pointer_class_Ui);
    CB_Baudrate->move(POSITION_X, Mode_Position_Y+=STEP_Y);
    CB_Baudrate->resize(60,20);
    CB_Baudrate->addItem("9600");
    CB_Baudrate->addItem("115200");
    CB_Baudrate->setCurrentText("9600");
    if(9600 != this->Baudrate)
        CB_Baudrate->setCurrentText(QString::number(this->Baudrate));
    else{
        Baudrate = CB_Baudrate->currentText().toUInt();
    }

    QObject::connect(CB_TX, &QComboBox::currentTextChanged, [=](const QString str){
        this->TX = str;

        if("PB5" == str){
            CB_RX->setCurrentText("PB6");
        }

    });

    QObject::connect(CB_TX, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int ind){
        this->Func_TX = SL_TX_func[ind];
    });


    QObject::connect(CB_RX, &QComboBox::currentTextChanged, [=](const QString str){
        this->RX = str;

        if("PB6" == str){
            CB_TX->setCurrentText("PB5");
        }
    });

    QObject::connect(CB_RX, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int ind){
        this->Func_RX = SL_RX_func[ind];
    });

    QObject::connect(CB_Baudrate, &QComboBox::currentTextChanged, [=](const QString str){
        this->Baudrate = str.toUInt();
    });

    CB_On->show();
    L_TX->show();
    CB_TX->show();
    L_RX->show();
    CB_RX->show();
    L_Baudrate->show();
    CB_Baudrate->show();
}

void UART::CreateSettingsUi(QMainWindow *pointer_class_Ui, uint16_t offset_x, uint16_t offset_y)
{

}
