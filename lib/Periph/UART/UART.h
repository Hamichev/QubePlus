#ifndef UART_H
#define UART_H

#include <QList>
#include <QString>

#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>

#include <QJsonObject>

#include <QMainWindow>

#include <QDebug>

#define STEP_Y 30

class UART
{

public:
    UART();
    ~UART();

    QString Name;

    uint8_t On = 0;
    QString TX = "";
    QString Func_TX = "";
    QString RX = "";
    QString Func_RX = "";
    uint32_t Baudrate = 9600;


    QCheckBox* CB_On = 0;
    QLabel*     L_TX = 0;
    QComboBox* CB_TX = 0;
    QLabel*     L_RX = 0;
    QComboBox* CB_RX = 0;
    QLabel*     L_Baudrate = 0;
    QComboBox* CB_Baudrate = 0;

    QStringList SL_TX_pin;
    QStringList SL_TX_func;

    QStringList SL_RX_pin;
    QStringList SL_RX_func;

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


#endif // UART_H
