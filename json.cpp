#include "json.h"

#include <QObject>
#include <QPushButton>

QJsonObject ReadJson(QString name_file)
{
    QFile file(name_file);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open the file" << file.fileName() << "for reading:" << file.errorString();
    }

    QByteArray jsonData = file.readAll();
    if (file.error() != QFile::NoError) {
        qDebug() << QString("Failed to read from file %1, error: %2").arg(file.fileName()).arg(file.errorString());
    }

    file.close();

    if (jsonData.isEmpty()) {
        qDebug() << "No data was currently available for reading from file" << file.fileName();
    }

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(jsonData, &jsonError);

    if (!document.isObject()) {
        qDebug() << "Document is not an object";
    }
    return document.object();
}


void ReadConfigMCU(MCU *mcu, QList<Pin*> *list_Pin)
{

    QJsonObject jsonObject = ReadJson(QDir::currentPath() + "\\mcu\\" + mcu->Name + ".json");

    QString name_Pin;

    QJsonValue jsonValue;

    QJsonValue jsonValuePin;
    QJsonValue jsonValueFunctional;

    QJsonValue jsonValueString;
    QJsonArray jsonArray;

    for(uint16_t i=0; i < (mcu->Number_Pins + 1); i++){
        name_Pin = "Pin_" + QString::number(i);
        jsonValue = jsonObject["Pins"].toObject();
        jsonValuePin = jsonValue.toObject().value(name_Pin);
        jsonValueString = jsonValuePin.toObject().value("Name");

        (*list_Pin)[i]->setText(jsonValueString.toString());
        (*list_Pin)[i]->Name = jsonValueString.toString();

        QFont font = (*list_Pin)[i]->font();
        font.setPointSize(7);
        (*list_Pin)[i]->setFont(font);


        jsonValueFunctional = jsonValuePin.toObject().value("Functional");

        if(0 != i){
            if(QJsonValue::Undefined != jsonValueFunctional.toObject().value("NONE").type())
                continue;

            if(QJsonValue::Undefined != jsonValueFunctional.toObject().value("DATA").type()){
                jsonValue = jsonValueFunctional.toObject().value("DATA");

                foreach(QString t, jsonValue.toObject().keys()){
                    (*list_Pin)[i]->LS_DATA_Name.append(t);
                    jsonValue = jsonValue.toObject().value(t);
                    (*list_Pin)[i]->LS_DATA_Modification.append(jsonValue.toObject().value("Modification").toString());
                }
            }

            if(QJsonValue::Undefined != jsonValueFunctional.toObject().value("ADC").type()){
                jsonValue = jsonValueFunctional.toObject().value("ADC");

                foreach(QString t, jsonValue.toObject().keys()){
                    (*list_Pin)[i]->LS_ADC_Name.append(t);
                    jsonValue = jsonValue.toObject().value(t);
                    (*list_Pin)[i]->LS_ADC_Modification.append(jsonValue.toObject().value("Modification").toString());

                    for(uint16_t j=0; j<(*mcu).L_ADC.size(); j++){
                        if((*list_Pin)[i]->LS_ADC_Name[(*list_Pin)[i]->LS_ADC_Name.size()-1] == (*mcu).L_ADC[j]->Name){
                            (*mcu).L_ADC[j]->SL_channel.append((*list_Pin)[i]->LS_ADC_Modification[(*list_Pin)[i]->LS_ADC_Modification.size()-1]);
                        }
                    }

                }
            }

            if(QJsonValue::Undefined != jsonValueFunctional.toObject().value("EXT").type()){
                jsonValue = jsonValueFunctional.toObject().value("EXT");

                foreach(QString t, jsonValue.toObject().keys()){
                    (*list_Pin)[i]->LS_EXT_Name.append(t);
                    jsonValue = jsonValue.toObject().value(t);
                    (*list_Pin)[i]->LS_EXT_Modification.append(jsonValue.toObject().value("Modification").toString());
                }
            }

            if(QJsonValue::Undefined != jsonValueFunctional.toObject().value("I2C").type()){
                jsonValue = jsonValueFunctional.toObject().value("I2C");

                foreach(QString t, jsonValue.toObject().keys()){
                    (*list_Pin)[i]->LS_I2C_Name.append(t);
                    jsonValue = jsonValue.toObject().value(t);
                    (*list_Pin)[i]->LS_I2C_Modification.append(jsonValue.toObject().value("Modification").toString());
                }
            }

            if(QJsonValue::Undefined != jsonValueFunctional.toObject().value("TIM").type()){
                jsonValue = jsonValueFunctional.toObject().value("TIM");

                foreach(QString t, jsonValue.toObject().keys()){
                    (*list_Pin)[i]->LS_TIM_Name.append(t);
                    jsonValue = jsonValue.toObject().value(t);
                    (*list_Pin)[i]->LS_TIM_Modification.append(jsonValue.toObject().value("Modification").toString());
                }
            }

            if(QJsonValue::Undefined != jsonValueFunctional.toObject().value("UART").type()){
                jsonValue = jsonValueFunctional.toObject().value("UART");

                foreach(QString t, jsonValue.toObject().keys()){
                    (*list_Pin)[i]->LS_UART_Name.append(t);
                    jsonValue = jsonValue.toObject().value(t);
                    (*list_Pin)[i]->LS_UART_Modification.append(jsonValue.toObject().value("Modification").toString());
                    (*list_Pin)[i]->LS_UART_Func_PIN.append(jsonValue.toObject().value("Func_PIN").toString());

                    for(uint16_t j=0; j<(*mcu).L_UART.size(); j++){
                        if((*list_Pin)[i]->LS_UART_Name[(*list_Pin)[i]->LS_UART_Name.size()-1] == (*mcu).L_UART[j]->Name){
                            if((*list_Pin)[i]->LS_UART_Modification[(*list_Pin)[i]->LS_UART_Modification.size()-1] == "TX"){
                                (*mcu).L_UART[j]->SL_TX_pin.append((*list_Pin)[i]->Name);
                                (*mcu).L_UART[j]->SL_TX_func.append((*list_Pin)[i]->LS_UART_Func_PIN[(*list_Pin)[i]->LS_UART_Func_PIN.size()-1]);
                            }
                            else if((*list_Pin)[i]->LS_UART_Modification[(*list_Pin)[i]->LS_UART_Modification.size()-1] == "RX"){
                                (*mcu).L_UART[j]->SL_RX_pin.append((*list_Pin)[i]->Name);
                                (*mcu).L_UART[j]->SL_RX_func.append((*list_Pin)[i]->LS_UART_Func_PIN[(*list_Pin)[i]->LS_UART_Func_PIN.size()-1]);
                            }
                        }
                    }
                }
            }
        }
        else{
            if(QJsonValue::Undefined != jsonValueFunctional.toObject().value("DATA").type()){
                jsonArray = (jsonValueFunctional.toObject().value("DATA")).toArray();

                foreach(QJsonValue t, jsonArray){
                    (*mcu).L_DATA.append(new DATA());

                    (*mcu).L_DATA[(*mcu).L_DATA.size() - 1]->Name = t.toString();
                }

            }

            if(QJsonValue::Undefined != jsonValueFunctional.toObject().value("ADC").type()){
                jsonArray = (jsonValueFunctional.toObject().value("ADC")).toArray();

                foreach(QJsonValue t, jsonArray){
                    (*mcu).L_ADC.append(new ADC());

                    (*mcu).L_ADC[(*mcu).L_ADC.size() - 1]->Name = t.toString();
                }

            }

            if(QJsonValue::Undefined != jsonValueFunctional.toObject().value("EXT").type()){
                jsonArray = (jsonValueFunctional.toObject().value("EXT")).toArray();

                foreach(QJsonValue t, jsonArray){
                    (*mcu).L_EXT.append(new EXT());

                    (*mcu).L_EXT[(*mcu).L_EXT.size() - 1]->Name = t.toString();
                }

            }

            if(QJsonValue::Undefined != jsonValueFunctional.toObject().value("I2C").type()){
                jsonArray = (jsonValueFunctional.toObject().value("I2C")).toArray();

                foreach(QJsonValue t, jsonArray){
                    (*mcu).L_I2C.append(new I2C());

                    (*mcu).L_I2C[(*mcu).L_I2C.size() - 1]->Name = t.toString();
                }

            }

            if(QJsonValue::Undefined != jsonValueFunctional.toObject().value("TIM").type()){
                jsonArray = (jsonValueFunctional.toObject().value("TIM")).toArray();

                foreach(QJsonValue t, jsonArray){
                    (*mcu).L_TIM.append(new TIM());

                    (*mcu).L_TIM[(*mcu).L_TIM.size() - 1]->Name = t.toString();
                }

            }

            if(QJsonValue::Undefined != jsonValueFunctional.toObject().value("UART").type()){
                jsonArray = (jsonValueFunctional.toObject().value("UART")).toArray();

                foreach(QJsonValue t, jsonArray){
                    (*mcu).L_UART.append(new UART());

                    (*mcu).L_UART[(*mcu).L_UART.size() - 1]->Name = t.toString();
                }

            }

        }

    }
}

void WriteProject(MCU *mcu, QList<Pin*> *list_Pin, Periph *periph, QString name_Project)
{

#define CREATE_ANY_OBJECT(_LIST_,_TYPE_,_NAME_) { \
                                            if(0 != (*mcu)._LIST_.size()){ \
                                                QJsonObject DataObject; \
                                                foreach(_TYPE_ *t, (*mcu)._LIST_){ \
                                                    DataObject.insert(t->Name, t->CreateJsonObject()); \
                                                } \
                                                mainObject.insert(_NAME_, DataObject); \
                                            } \
                                         }
    QJsonObject mainObject;
    mainObject.insert("Name_MCU", QJsonValue::fromVariant(mcu->Name));
    mainObject.insert("Name_project", QJsonValue::fromVariant(name_Project));

    //-----------------------------------MCU-----------------------------------

    CREATE_ANY_OBJECT(L_DATA,DATA,"DATA");
    CREATE_ANY_OBJECT(L_ADC,ADC,"ADC");
    CREATE_ANY_OBJECT(L_EXT,EXT,"EXT");
    CREATE_ANY_OBJECT(L_I2C,I2C,"I2C");
    CREATE_ANY_OBJECT(L_TIM,TIM,"TIM");
    CREATE_ANY_OBJECT(L_UART,UART,"UART");

    //-------------------------------END_MCU-----------------------------------

    QJsonDocument doc(mainObject);
    QString jsonString = doc.toJson(QJsonDocument::Indented);
    QFile file;

    if(!QDir("projects").exists())
        QDir().mkdir("projects");

    if(!QDir("projects\\" + name_Project).exists())
        QDir().mkdir("projects\\" + name_Project);

    file.setFileName((QString)"projects\\" + (QString)name_Project + (QString)"\\" + (QString)name_Project + (QString)".json");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream( &file );
    stream << jsonString;
    file.close();
}


void ReadProject(QString config, MCU *mcu, QList<Pin *> *list_Pin, Periph *periph, QString *Name_project, QLineEdit* LE_mcu)
{
#define READ_ANY_OBJECT(_STR_,_LIST_) { \
                                if(QJsonValue::Undefined != jsonObject.value(_STR_).type()){ \
                                    jsonValue = jsonObject.value(_STR_); \
                             \
                                    for(uint16_t i=0; i<mcu->_LIST_.size(); i++){ \
                                        if(QJsonValue::Undefined != jsonValue.toObject().value(mcu->_LIST_[i]->Name).type()){ \
                                            QJsonValue JV_Data = jsonValue.toObject().value(mcu->_LIST_[i]->Name); \
                                            mcu->_LIST_[i]->ReadJsonValue(JV_Data); \
                                        } \
                                    } \
                                } \
                            }

    QJsonObject jsonObject = ReadJson(config);
    QJsonValue jsonValue;

    mcu->Name = jsonObject.value("Name_MCU").toString();

    (*Name_project) = jsonObject.value("Name_project").toString();

    if("MDR32F9Q2I" == mcu->Name){
        LE_mcu->setText("");
        LE_mcu->setText("MDR32F9Q2I");
    }


    READ_ANY_OBJECT("DATA",L_DATA);
    READ_ANY_OBJECT("ADC",L_ADC);
    READ_ANY_OBJECT("EXT",L_EXT);
    READ_ANY_OBJECT("I2C",L_I2C);
    READ_ANY_OBJECT("TIM",L_TIM);
    READ_ANY_OBJECT("UART",L_UART);
}
