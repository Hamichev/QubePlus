#ifndef TIM_H
#define TIM_H

#include <QList>
#include <QString>

#include <QPushButton>
#include <QCheckBox>

#include <QJsonObject>

#include <QMainWindow>

#include <QDebug>

#define STEP_Y 30

class TIM
{
public:
    TIM();
    ~TIM();

    QString Name;

    uint8_t On = 0;

    QCheckBox* CB_On = 0;

    uint16_t Mode_Position_Y;
    uint16_t Settings_Position_Y;

    //QString Modification;

protected:

public slots:

    void CreateUi(QMainWindow* pointer_class_Ui, uint16_t offset_mode_x, uint16_t offset_mode_y, uint16_t offset_settings_x, uint16_t offset_settings_y);

    void ClearUi();

    QJsonObject CreateJsonObject();
    void ReadJsonValue(QJsonValue jv);

private slots:

    void CreateModeUi(QMainWindow* pointer_class_Ui, uint16_t offset_x, uint16_t offset_y);
    void CreateSettingsUi(QMainWindow* pointer_class_Ui, uint16_t offset_x, uint16_t offset_y);

private:

};


#endif // TIM_H
