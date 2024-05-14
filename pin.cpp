#include "pin.h"

#include <QPainter>
#include <QStyleOptionButton>
#include <QDebug>
#include <QStylePainter>

Pin::Pin(QWidget *parent) : QPushButton(parent)
{
    ;
}

QSize Pin::sizeHint() const
{
    QSize sh = QPushButton::sizeHint();

    if (m_Orientation != Pin::Horizontal)
    {
        sh.transpose();
    }

    return sh;
}

void Pin::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStylePainter painter(this);
    QStyleOptionButton option;
    initStyleOption(&option);

    if (m_Orientation == Pin::VerticalTopToBottom)
    {
        painter.rotate(90);
        painter.translate(0, -1 * width());
        option.rect = option.rect.transposed();
    }

    else if (m_Orientation == Pin::VerticalBottomToTop)
    {
        painter.rotate(-90);
        painter.translate(-1 * height(), 0);
        option.rect = option.rect.transposed();
    }

    painter.drawControl(QStyle::CE_PushButton, option);
}

Pin::Orientation Pin::orientation() const
{
    return m_Orientation;
}

void Pin::setOrientation(const Pin::Orientation &orientation)
{
    m_Orientation = orientation;
}


