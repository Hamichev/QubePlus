#include "qubeplus.h"
#include "ui_qubeplus.h"

#include <QDebug>
#include <QAbstractButton>


QubePlus::QubePlus(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QubePlus)
{
    ui->setupUi(this);

    m_mcu = new MCU();

    m_Periph = new Periph();

    m_Builder = new Builder();
    m_Builder->Init(this, m_mcu, &m_Pins);

    //ui->LE_MCU

    connect(ui->LE_MCU, SIGNAL(textChanged(QString)), this, SLOT(CreateProject(QString)));

    //----------------------Create_wdgNewProject-----------
    wdgNewProject = new QWidget;
    wdgNewProject->setFixedSize(300,90);
    wdgNewProject->setWindowTitle("Create new project");

    QLineEdit *LE_NameProject = new QLineEdit(wdgNewProject);
    LE_NameProject->setFixedSize(160,20);
    LE_NameProject->move(70,5);
    LE_NameProject->show();

    QComboBox *CB_MCU = new QComboBox(wdgNewProject);
    CB_MCU->setFixedSize(160,20);
    CB_MCU->move(70,30);
    CB_MCU->addItem("MDR32F9Q2I");
    CB_MCU->show();

    QPushButton *PB_Create = new QPushButton(wdgNewProject);
    PB_Create->setText("Create");
    PB_Create->setFixedSize(75,20);
    PB_Create->move(70,65);
    PB_Create->show();

    QPushButton *PB_Cancel = new QPushButton(wdgNewProject);
    PB_Cancel->setText("Cancel");
    PB_Cancel->setFixedSize(75,20);
    PB_Cancel->move(155,65);
    PB_Cancel->show();

    connect(PB_Create, &QPushButton::clicked, [=](){
                if(!QDir("projects\\" + LE_NameProject->text()).exists()){
                    Name_current_project = LE_NameProject->text();
                    this->CreateProject(CB_MCU->currentText());
                    WriteProject(m_mcu, &m_Pins, m_Periph, Name_current_project);
                    copyFile("Base_project", "projects\\"+Name_current_project);
                    wdgNewProject->close();
                }
                else{
                    QMessageBox::warning(this, "Project name error", "A project with the current name has already been created!", QMessageBox::Cancel);
                    wdgNewProject->close();
                }
            });

    connect(PB_Cancel, &QPushButton::clicked, [=](){
        wdgNewProject->close();
    });
    //------------------END_Create_wdgNewProject-----------
}

QubePlus::~QubePlus()
{
    delete ui;
}

void QubePlus::copyFile(const QString &source, const QString &destination)
{
    if ( QFileInfo( source ).isDir() ) {
            QDir().mkdir( destination );
            foreach ( const QString & entry, QDir( source ).entryList( QDir::AllDirs | QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot ) )
                copyFile( source + QDir::separator() + entry, destination + QDir::separator() + entry );
        } else {
            if ( QFile::exists(destination) ) {
                QFileInfo infoS = QFileInfo(source);
                QFileInfo infoD = QFileInfo (destination);
                if ( infoS.lastModified() > infoD.lastModified() ) {
                    QFile::remove(destination);
                    bool ok = QFile::copy( source, destination );
                }
            } else {
                bool ok = QFile::copy( source, destination );
            }
        }
}

void QubePlus::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() & Qt::ControlModifier){
        if(event->key() == 83){ //ctr+s
            WriteProject(m_mcu, &m_Pins, m_Periph, Name_current_project);
            ui->statusbar->showMessage("Ctrl+s", 2000);
        }
        else if(event->key() == 79){ //ctr+o
            QString path_project;
            path_project = QFileDialog::getOpenFileName();

            if(path_project != ""){
                ui->LE_openProject->setText(path_project);

                ReadProject(path_project, m_mcu, &m_Pins, m_Periph, &Name_current_project, ui->LE_MCU);
            }
            ui->statusbar->showMessage("Ctrl+o", 2000);
        }
        else if(event->key() == 78){ //ctr+n
            wdgNewProject->show();
            ui->statusbar->showMessage("Ctrl+n", 2000);
        }
        else if(event->key() == 66){ //ctr+b

            m_Builder->buildCurrentProject(Name_current_project);
            ui->statusbar->showMessage("Ctrl+b", 2000);
        }
    }
}
//if("PLZ1" != Name_current_project)
//    ReadProject("C:/Qt_project/build-QubePlus-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/projects/PLZ1/PLZ1.json", m_mcu, &m_Pins, m_Periph, &Name_current_project, ui->LE_MCU);

void QubePlus::CreateProject(QString mcu)
{

#define INDEX_FIRST_PIN    64
#define REVERSE 1

#define CLEAR_LIST(_LIST_)  { \
                                for(uint16_t i=0; i<(_LIST_.size()); i++){ \
                                    delete _LIST_[i]; \
                                } \
                                _LIST_.clear(); \
                            }

#define CLEAR_SPACE()       { \
                                for(uint16_t i=0; i<(m_counter_Pin); i++){ \
                                    delete m_Pins[i]; \
                                } \
                                m_Pins.clear(); \
                                m_counter_Pin = 0; \
                             \
                                m_mcu->ClearAllModeSettingsUi(); \
                             \
                                CLEAR_LIST(m_Periph->ButtonPeriph); \
                                CLEAR_LIST(m_Periph->ButtonDetail); \
                                CLEAR_LIST(m_mcu->L_DATA); \
                                CLEAR_LIST(m_mcu->L_ADC); \
                                CLEAR_LIST(m_mcu->L_EXT); \
                                CLEAR_LIST(m_mcu->L_I2C); \
                                CLEAR_LIST(m_mcu->L_TIM); \
                                CLEAR_LIST(m_mcu->L_UART); \
                                 \
                            }



    if("MDR32F9Q2I" == mcu){
        CLEAR_SPACE();

        //qDebug() << Name_current_project;
        this->setWindowTitle("QubePlus. Project " + Name_current_project);

        m_mcu->CreateMCU(this, m_mcu, &m_Pins, &m_counter_Pin, "MDR32F9Q2I", 64, INDEX_FIRST_PIN, REVERSE);
        ReadConfigMCU(m_mcu, &m_Pins);

        m_Periph->CreatePeriphButton(this, m_mcu, ui->GB_Periph->x(), ui->GB_Periph->y());
        m_Periph->CreateConnectPeriphDetailButtonConnectDetail(this, m_mcu, ui->GB_Detail->x() + ui->SA_Detail->x(), ui->GB_Detail->y() + ui->SA_Detail->y(),
                                                               ui->GB_Mode->x() + ui->SA_Mode->x(), ui->GB_Mode->y() + ui->SA_Mode->y(),
                                                               ui->GB_Settings->x() + ui->SA_Settings->x(), ui->GB_Settings->y() + ui->SA_Settings->y());

        m_mcu->SetConnectClickedPin(m_mcu, &m_Periph->ButtonPeriph, &m_Periph->ButtonDetail, &m_Pins);
        m_mcu->SetConnectClickedMCU(m_mcu, m_Pins[0]);

        m_mcu->isReady = 1;
    }
    else{
        ;
    }

    //qDebug() << disconnect(ui->LE_MCU, SIGNAL(textChanged(QString)), this, SLOT(CreateProject(QString)));
}
