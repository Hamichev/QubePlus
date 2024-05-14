#include "../TIM/TIM.h"

#include <QPainter>
#include <QStyleOptionButton>
#include <QDebug>
#include <QStylePainter>

TIM::TIM()
{
    ;
}

TIM::~TIM()
{

}

void TIM::CreateUi(QMainWindow *pointer_class_Ui, uint16_t offset_mode_x, uint16_t offset_mode_y, uint16_t offset_settings_x, uint16_t offset_settings_y)
{
    CreateModeUi(pointer_class_Ui, offset_mode_x, offset_mode_y);

    CreateSettingsUi(pointer_class_Ui, offset_settings_x, offset_settings_y);

}

void TIM::ClearUi()
{
    Mode_Position_Y = 0;
    Settings_Position_Y = 0;

    if(CB_On != 0){
        CB_On->deleteLater();
        CB_On = 0;
    }
}

QJsonObject TIM::CreateJsonObject()
{
    QJsonObject DataObject;
    DataObject.insert("On", QJsonValue::fromVariant(this->On));
    return DataObject;
}

void TIM::ReadJsonValue(QJsonValue jv)
{
    this->On = jv.toObject().value("On").toInt();
}

void TIM::CreateModeUi(QMainWindow *pointer_class_Ui, uint16_t offset_x, uint16_t offset_y)
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

    CB_On->show();

    // Подтягиваем текущее значение конйигурации
    //CB_On->setCheckState(Qt::CheckState::Checked);


}

void TIM::CreateSettingsUi(QMainWindow *pointer_class_Ui, uint16_t offset_x, uint16_t offset_y)
{

}
