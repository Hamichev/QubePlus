#include "../ADC/ADC.h"

#include <QPushButton>
#include <QCheckBox>


ADC::ADC()
{
    ;
}

ADC::~ADC()
{

}

void ADC::CreateUi(QMainWindow* pointer_class_Ui, uint16_t offset_mode_x, uint16_t offset_mode_y, uint16_t offset_settings_x, uint16_t offset_settings_y)
{
    CreateModeUi(pointer_class_Ui, offset_mode_x, offset_mode_y);

    CreateSettingsUi(pointer_class_Ui, offset_settings_x, offset_settings_y);

}

void ADC::ClearUi()
{

    Mode_Position_Y = 0;
    Settings_Position_Y = 0;

    if(CB_On != 0){
        CB_On->deleteLater();
        CB_On = 0;
    }

    if(CB_channel != 0){
        CB_channel->deleteLater();
        CB_channel = 0;
    }

}

QJsonObject ADC::CreateJsonObject()
{
    QJsonObject DataObject;
    DataObject.insert("On", QJsonValue::fromVariant(this->On));
    DataObject.insert("Modify", QJsonValue::fromVariant(this->Modify));
    return DataObject;
}

void ADC::ReadJsonValue(QJsonValue jv)
{
    this->On = jv.toObject().value("On").toInt();
    this->Modify = jv.toObject().value("Modify").toString();
}

void ADC::CreateModeUi(QMainWindow *pointer_class_Ui, uint16_t offset_x, uint16_t offset_y)
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

    CB_channel = new QComboBox(pointer_class_Ui);
    CB_channel->move(POSITION_X, Mode_Position_Y+=STEP_Y);
    CB_channel->resize(60,20);
    for(uint16_t i=0; i<SL_channel.size(); i++) CB_channel->addItem(SL_channel[i]);
    if("" != this->Modify)
        CB_channel->setCurrentText(this->Modify);
    else
        Modify = CB_channel->currentText();

    QObject::connect(CB_channel, &QComboBox::currentTextChanged, [=](const QString str){
        this->Modify = str;
    });

    CB_channel->show();
    CB_On->show();

    // Подтягиваем текущее значение конйигурации
    //CB_On->setCheckState(Qt::CheckState::Checked);

}

void ADC::CreateSettingsUi(QMainWindow *pointer_class_Ui, uint16_t offset_x, uint16_t offset_y)
{
#define POSITION_X offset_x+5

    Settings_Position_Y = offset_y;

}
