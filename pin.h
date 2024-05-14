#ifndef PIN_H
#define PIN_H

#include <QList>
#include <QString>
#include <QPushButton>

#include <QDebug>

class Pin : public QPushButton
{
    Q_OBJECT

public:
    Pin(QWidget *parent = nullptr);

    enum Orientation {
        Horizontal,
        VerticalTopToBottom,
        VerticalBottomToTop
    };

    QString Name;

    QList<QString> LS_DATA_Name;
    QList<QString> LS_DATA_Modification;

    QList<QString> LS_ADC_Name;
    QList<QString> LS_ADC_Modification;

    QList<QString> LS_EXT_Name;
    QList<QString> LS_EXT_Modification;

    QList<QString> LS_I2C_Name;
    QList<QString> LS_I2C_Modification;

    QList<QString> LS_TIM_Name;
    QList<QString> LS_TIM_Modification;

    QList<QString> LS_UART_Name;
    QList<QString> LS_UART_Modification;
    QList<QString> LS_UART_Func_PIN;

    QList<QString> functional;

    QSize sizeHint() const;

    Pin::Orientation orientation() const;
    void setOrientation(const Pin::Orientation &orientation);

protected:
    void paintEvent(QPaintEvent *event);

public slots:

    QString getName() {
        return Name;
    }


private slots:

signals:
    //void ClearModeUiEvent();
    //void ClearSettingsUiEvent();

private:

    Orientation m_Orientation = Horizontal;

};



//void SetConnectClickedPin(MCU *mcu, QList<Pin*> *list_Pin);

#endif // PIN_H
