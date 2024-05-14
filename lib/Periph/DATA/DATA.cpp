#include "../DATA/DATA.h"

#include <QPainter>
#include <QStyleOptionButton>
#include <QDebug>
#include <QStylePainter>

DATA::DATA()
{
    ;
}

DATA::~DATA()
{

}

void DATA::CreateUi(QMainWindow *pointer_class_Ui, uint16_t offset_mode_x, uint16_t offset_mode_y, uint16_t offset_settings_x, uint16_t offset_settings_y)
{
    CreateModeUi(pointer_class_Ui, offset_mode_x, offset_mode_y);

    CreateSettingsUi(pointer_class_Ui, offset_settings_x, offset_settings_y);

}

void DATA::ClearUi()
{
    Mode_Position_Y = 0;
    Settings_Position_Y = 0;

    if(CB_On != 0){
        CB_On->deleteLater();
        CB_On = 0;
    }

    if(CB_type != 0){
        CB_type->deleteLater();
        CB_type = 0;
    }
}

QJsonObject DATA::CreateJsonObject()
{
    QJsonObject DataObject;
    DataObject.insert("On", QJsonValue::fromVariant(this->On));
    DataObject.insert("Type", QJsonValue::fromVariant(this->type));
    return DataObject;
}

void DATA::ReadJsonValue(QJsonValue jv)
{
    this->On = jv.toObject().value("On").toInt();
    this->type = (jv.toObject().value("Type").toString());
}

void DATA::CreateModeUi(QMainWindow *pointer_class_Ui, uint16_t offset_x, uint16_t offset_y)
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

    //type
    CB_type = new QComboBox(pointer_class_Ui);
    CB_type->move(POSITION_X, Mode_Position_Y+=STEP_Y);
    CB_type->resize(60,20);
    CB_type->addItem("OUT");
    CB_type->addItem("IN");
    CB_type->setCurrentText(this->type);

    QObject::connect(CB_type, &QComboBox::currentTextChanged, [=](const QString str){
        this->type = str;
    });

    CB_type->show();
    CB_On->show();
}

void DATA::CreateSettingsUi(QMainWindow *pointer_class_Ui, uint16_t offset_x, uint16_t offset_y)
{

}
