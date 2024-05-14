#ifndef QUBEPLUS_H
#define QUBEPLUS_H

#include <QMainWindow>

#include <QList>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>

#include <QtGui>

#include <QFileDialog>

#include "mcu.h"
#include "json.h"
#include "pin.h"

#include "Periph.h"
#include "builder.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QubePlus; }
QT_END_NAMESPACE

class QubePlus : public QMainWindow
{
    Q_OBJECT

public:
    QubePlus(QWidget *parent = nullptr);
    ~QubePlus();

    QString Name_current_project;

public slots:


private slots:

    void copyFile(const QString &source, const QString &destination);

    void keyPressEvent(QKeyEvent *event);

    void CreateProject(QString mcu);

private:
    Ui::QubePlus *ui;

    MCU *m_mcu;

    Periph *m_Periph;

    Builder *m_Builder;

    QWidget *wdgNewProject;

    QList<Pin*> m_Pins;
    uint16_t m_counter_Pin = 0;
};
#endif // QUBEPLUS_H
