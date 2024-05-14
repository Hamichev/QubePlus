#ifndef I2C_H
#define I2C_H

#include <QList>
#include <QString>

#include <QPushButton>
#include <QCheckBox>

#include <QJsonObject>

#include <QMainWindow>

#include <QDebug>

#define STEP_Y 30

class I2C
{
public:
    I2C();
    ~I2C();

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


#endif // I2C_H
