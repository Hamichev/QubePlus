#include "builder.h"

Builder::Builder()
{

}

void Builder::Init(QMainWindow *pointer_class_Ui, MCU *mcu, QList<Pin*> *list_Pin)
{
    m_pointer_class_Ui = pointer_class_Ui;
    m_mcu = mcu;
    m_list_Pin = list_Pin;
}

void Builder::buildCurrentProject(QString Name_project)
{
    QFile file(QString("projects\\") + Name_project + QString("\\") + QString("main.c"));

    if(!file.exists()){
        QMessageBox::information(m_pointer_class_Ui, "Ошибка чтения файла main.c", "Файл не обнаружен");
        qWarning() << "FILE NOT FOUND";
        return;
    }

    if(!file.open(QIODevice::ReadWrite)){
        QMessageBox::information(m_pointer_class_Ui, "Ошибка чтения файла main.c", "Приложение не может корректно прочитать данный файл");
        qWarning() << file.errorString();
        return;
    }

    QTextStream stream(&file);

    QString line;

    QStringList SL_newMain;

    readDATAconfig();
    readADCconfig();
    readUARTconfig();

    while(!stream.atEnd()){
        line = stream.readLine();

        if(line.count("//Begin_Include")){
            SL_newMain.append(line);
            for(uint32_t i=0; i<(uint32_t)m_Include.size();i++){
                SL_newMain.append(m_Include[i]);
            }
            while(!line.count("//End_Include")) line = stream.readLine();
            SL_newMain.append(line);
        }
        else if(line.count("//Begin_prototype_Func")){
            SL_newMain.append(line);
            for(uint32_t i=0; i<(uint32_t)m_Prototype_Func.size();i++){
                SL_newMain.append(m_Prototype_Func[i]);
            }
            while(!line.count("//End_prototype_Func")) line = stream.readLine();
            SL_newMain.append(line);
        }
        else if(line.count("//Begin_Init_struct")){
            SL_newMain.append(line);
            for(uint32_t i=0; i<(uint32_t)m_Init_struct.size();i++){
                SL_newMain.append(m_Init_struct[i]);
            }
            while(!line.count("//End_Init_struct")) line = stream.readLine();
            SL_newMain.append(line);

        }
        else if(line.count("//Begin_Init_config")){
            SL_newMain.append(line);
            for(uint32_t i=0; i<(uint32_t)m_Init_config.size();i++){
                SL_newMain.append(m_Init_config[i]);
            }
            while(!line.count("//End_Init_config")) line = stream.readLine();
            SL_newMain.append(line);

        }
        else if(line.count("//Begin_call_Func")){
            SL_newMain.append(line);
            for(uint32_t i=0; i<(uint32_t)m_Call_Func.size();i++){
                SL_newMain.append(m_Call_Func[i]);
            }
            while(!line.count("//End_call_Func")) line = stream.readLine();
            SL_newMain.append(line);

        }
        else if(line.count("//Begin_Result")){
            SL_newMain.append(line);
            for(uint32_t i=0; i<(uint32_t)m_Result.size();i++){
                SL_newMain.append(m_Result[i]);
            }
            while(!line.count("//End_Result")) line = stream.readLine();
            SL_newMain.append(line);

        }
        else if(line.count("//Begin_Func")){
            SL_newMain.append(line);
            for(uint32_t i=0; i<(uint32_t)m_Func.size();i++){
                SL_newMain.append(m_Func[i]);
            }
            while(!line.count("//End_Func")) line = stream.readLine();
            SL_newMain.append(line);

        }
        else{
            SL_newMain.append(line);
        }
    }

    file.resize(0);

    for(uint32_t i=0; i<(uint32_t)SL_newMain.size();i++){
        stream << SL_newMain[i] << "\n";
    }

    file.close();

    ClearAllList();
}

void Builder::addNewBuild()
{

}

void Builder::readDATAconfig()
{
    //F - flag
    bool F_include = false;
    bool F_init_struct = false;
    bool F_RST_CLK_A = false;
    bool F_RST_CLK_B = false;
    bool F_RST_CLK_C = false;
    bool F_RST_CLK_D = false;
    bool F_RST_CLK_E = false;
    bool F_RST_CLK_F = false;

    QString port;
    uint8_t pin;
    QString type;

    QFile file("builds\\DATA.txt");

    if(!file.exists()){
        QMessageBox::information(m_pointer_class_Ui, "Ошибка чтения файла DATA.txt", "Файл не обнаружен");
        qWarning() << "FILE NOT FOUND";
        return;
    }

    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(m_pointer_class_Ui, "Ошибка чтения файла DATA.txt", "Приложение не может корректно прочитать данный файл");
        qWarning() << file.errorString();
        return;
    }

    QTextStream stream(&file);

    QStringList lib;

    QString t_str;

    while(!stream.atEnd()){
        lib.append(stream.readLine());
    }

    file.close();

    foreach(DATA *t, m_mcu->L_DATA){
        if(0 != t->On){
            for(uint16_t i=1; i<m_list_Pin->size();i++){ // 0 - skip - MCU
                foreach(QString tt, (*m_list_Pin)[i]->LS_DATA_Name){
                    if(t->Name == tt){
                        port = (*m_list_Pin)[i]->Name.mid(1,1);
                        pin = (*m_list_Pin)[i]->Name.mid(2,1).toUShort();
                        type = t->type;

                        for(uint32_t i=0; i<(uint32_t)lib.size(); i++){
                           if(!F_include){
                               if("//Begin_Include" == lib[i]){
                                   F_include = true;
                                   i++;
                                   while("//End_Include" != lib[i]){
                                       if(!m_Include.count(lib[i]))
                                            m_Include.append(lib[i]);
                                       i++;
                                   }
                               }
                           }

                           if("//Begin_prototype_Func" == lib[i]){
                               i++;
                               t_str = lib[i];
                               t_str.replace("__PORT__", port);
                               t_str.replace("__PIN__", QString::number(pin));
                               m_Prototype_Func.append(t_str);
                               while("//End_prototype_Func" != lib[i]){
                                   i++;
                               }
                           }

                           if(!F_init_struct){
                               if("//Begin_Init_struct" == lib[i]){
                                   F_init_struct = true;
                                   i++;
                                   while("//End_Init_struct" != lib[i]){
                                       m_Init_struct.append(lib[i]);
                                       i++;
                                   }
                               }
                           }

                           if("//Begin_RST_CLK" == lib[i]){
                               i++;
                               if(("A" == port && !F_RST_CLK_A) ||
                                  ("B" == port && !F_RST_CLK_B) ||
                                  ("C" == port && !F_RST_CLK_C) ||
                                  ("D" == port && !F_RST_CLK_D) ||
                                  ("E" == port && !F_RST_CLK_E) ||
                                  ("F" == port && !F_RST_CLK_F)){

                                   t_str = lib[i];
                                   t_str.replace("__PORT__", port);
                                   if(!m_Init_config.count(t_str))
                                        m_Init_config.append(t_str);
                               }

                               while("//End_RST_CLK" != lib[i]){
                                   i++;
                               }
                           }

                           if("//Begin_Call_Func" == lib[i]){
                               i++;
                               t_str = lib[i];
                               t_str.replace("__PORT__", port);
                               t_str.replace("__PIN__", QString::number(pin));
                               m_Call_Func.append(t_str);
                               while("//End_Call_Func" != lib[i]){
                                   i++;
                               }
                           }

                           if("//Begin_Result" == lib[i]){
                               if("IN" == type){
                                   i++;
                                   while("//End_Result" != lib[i]){
                                       t_str = lib[i];
                                       t_str.replace("__PORT__", port);
                                       t_str.replace("__PIN__", QString::number(pin));
                                       m_Result.append(t_str);
                                       i++;
                                   }
                               }
                           }

                           if("//Begin_Init_pin" == lib[i]){
                               i++;
                               while("//End_Init_pin" != lib[i]){
                                   t_str = lib[i];
                                   t_str.replace("__PORT__", port);
                                   t_str.replace("__PIN__", QString::number(pin));
                                   t_str.replace("__TYPE__", type);
                                   m_Func.append(t_str);
                                   i++;
                               }
                           }
                        }



                    }
                }
            }
        }
    }


}

void Builder::readADCconfig()
{
    //F - flag
    bool F_include = false;
    bool F_init_struct = false;
    bool F_RST_CLK = false;

    QString port;
    uint8_t pin;
    uint8_t num_adc;

    QFile file("builds\\ADC.txt");

    if(!file.exists()){
        QMessageBox::information(m_pointer_class_Ui, "Ошибка чтения файла ADC.txt", "Файл не обнаружен");
        qWarning() << "FILE NOT FOUND";
        return;
    }

    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(m_pointer_class_Ui, "Ошибка чтения файла ADC.txt", "Приложение не может корректно прочитать данный файл");
        qWarning() << file.errorString();
        return;
    }

    QTextStream stream(&file);

    QStringList lib;

    QString t_str;

    while(!stream.atEnd()){
        lib.append(stream.readLine());
    }

    file.close();

    foreach(ADC *t, m_mcu->L_ADC){
        if(0 != t->On){
            for(uint16_t i=1; i<m_list_Pin->size();i++){ // 0 - skip - MCU
                for(uint16_t j=0; j<(*m_list_Pin)[i]->LS_ADC_Name.size(); j++){
                    if(t->Name == (*m_list_Pin)[i]->LS_ADC_Name[j]){
                        if(t->Modify == (*m_list_Pin)[i]->LS_ADC_Modification[j]){
                            port = (*m_list_Pin)[i]->Name.mid(1,1);
                            pin = (*m_list_Pin)[i]->Name.mid(2,1).toUShort();
                            num_adc = t->Name.mid(3,1).toUShort();

                            for(uint32_t i=0; i<(uint32_t)lib.size(); i++){
                                if(!F_include){
                                    if("//Begin_Include" == lib[i]){
                                        F_include = true;
                                        i++;
                                        while("//End_Include" != lib[i]){
                                            if(!m_Include.count(lib[i]))
                                                m_Include.append(lib[i]);
                                            i++;
                                        }
                                    }
                                }

                                if("//Begin_prototype_Func" == lib[i]){
                                    i++;
                                    t_str = lib[i];
                                    t_str.replace("__ADC__", QString::number(num_adc));
                                    m_Prototype_Func.append(t_str);
                                    while("//End_prototype_Func" != lib[i]){
                                        i++;
                                    }
                                }

                                if(!F_init_struct){
                                    if("//Begin_Init_struct" == lib[i]){
                                        F_init_struct = true;
                                        i++;
                                        while("//End_Init_struct" != lib[i]){
                                            m_Init_struct.append(lib[i]);
                                            i++;
                                        }
                                    }
                                }

                                if(!F_RST_CLK){
                                    if("//Begin_RST_CLK" == lib[i]){
                                        F_RST_CLK = true;
                                        i++;
                                        while("//End_RST_CLK" != lib[i]){
                                            t_str = lib[i];
                                            t_str.replace("__PORT__", port);
                                            if(!m_Init_config.count(t_str))
                                                m_Init_config.append(t_str);
                                            i++;
                                        }
                                    }
                                }

                                if("//Begin_Call_Func" == lib[i]){
                                    i++;
                                    t_str = lib[i];
                                    t_str.replace("__ADC__", QString::number(num_adc));
                                    m_Call_Func.append(t_str);
                                    while("//End_Call_Func" != lib[i]){
                                        i++;
                                    }
                                }

                                if("//Begin_Result" == lib[i]){
                                    i++;
                                    while("//End_Result" != lib[i]){
                                        t_str = lib[i];
                                        t_str.replace("__ADC__", QString::number(num_adc));
                                        m_Result.append(t_str);
                                        i++;
                                    }
                                }

                                if("//Begin_Func" == lib[i]){
                                    i++;
                                    while("//End_Func" != lib[i]){
                                        t_str = lib[i];
                                        t_str.replace("__PORT__", port);
                                        t_str.replace("__PIN__", QString::number(pin));
                                        t_str.replace("__ADC__", QString::number(num_adc));
                                        t_str.replace("__MOD__", t->Modify.mid(2,1));
                                        m_Func.append(t_str);
                                        i++;
                                    }
                                }





                            }
                        }
                    }
                }
            }
        }
    }
}

void Builder::readUARTconfig()
{
    bool F_include = false;
    bool F_init_struct = false;
    bool F_RST_CLK = false;
    bool F_Result = false;

    QString port_tx = "";
    QString func_tx = "";
    uint8_t pin_tx;
    QString port_rx = "";
    QString func_rx = "";
    uint8_t pin_rx;
    uint8_t num_uart;
    uint32_t baudrate;

    QFile file("builds\\UART.txt");

    if(!file.exists()){
        QMessageBox::information(m_pointer_class_Ui, "Ошибка чтения файла UART.txt", "Файл не обнаружен");
        qWarning() << "FILE NOT FOUND";
        return;
    }

    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(m_pointer_class_Ui, "Ошибка чтения файла UART.txt", "Приложение не может корректно прочитать данный файл");
        qWarning() << file.errorString();
        return;
    }

    QTextStream stream(&file);

    QStringList lib;

    QString t_str;

    while(!stream.atEnd()){
        lib.append(stream.readLine());
    }

    file.close();

    foreach(UART *t, m_mcu->L_UART){
        if(0 != t->On){

            port_tx = t->TX.mid(1,1);
            func_tx = t->Func_TX;
            pin_tx = t->TX.mid(2,1).toUShort();
            port_rx = t->RX.mid(1,1);
            func_rx = t->Func_RX;
            pin_rx = t->RX.mid(2,1).toUShort();
            num_uart = t->Name.mid(4,1).toUShort();
            baudrate = t->Baudrate;

            for(uint32_t i=0; i<(uint32_t)lib.size(); i++){
                if(!F_include){
                    if("//Begin_Include" == lib[i]){
                        F_include = true;
                        i++;
                        while("//End_Include" != lib[i]){
                            if(!m_Include.count(lib[i]))
                                m_Include.append(lib[i]);
                            i++;
                        }
                    }
                }

                if("//Begin_prototype_Func" == lib[i]){
                    i++;
                    t_str = lib[i];
                    t_str.replace("__NUM__", QString::number(num_uart));
                    m_Prototype_Func.append(t_str);
                    while("//End_prototype_Func" != lib[i]){
                        i++;
                    }
                }

                if(!F_init_struct){
                    if("//Begin_Init_struct" == lib[i]){
                        F_init_struct = true;
                        i++;
                        while("//End_Init_struct" != lib[i]){
                            m_Init_struct.append(lib[i]);
                            i++;
                        }
                    }
                }

                if(!F_RST_CLK){
                    if("//Begin_RST_CLK" == lib[i]){
                        F_RST_CLK = true;
                        i++;
                        while("//End_RST_CLK" != lib[i]){
                            t_str = lib[i];
                            t_str.replace("__NUM__", QString::number(num_uart));
                            t_str.replace("__PORTTX__", port_tx);
                            t_str.replace("__PORTRX__", port_rx);
                            if(!m_Init_config.count(t_str))
                                m_Init_config.append(t_str);
                            i++;
                        }
                    }
                }

                if("//Begin_Call_Func" == lib[i]){
                    i++;
                    t_str = lib[i];
                    t_str.replace("__NUM__", QString::number(num_uart));
                    m_Call_Func.append(t_str);
                    while("//End_Call_Func" != lib[i]){
                        i++;
                    }
                }

                if("//Begin_Result" == lib[i]){
                    i++;
                    while("//End_Result" != lib[i]){
                        t_str = lib[i];
                        t_str.replace("__NUM__", QString::number(num_uart));
                        m_Result.append(t_str);
                        i++;
                    }
                }

                if("//Begin_Func" == lib[i]){
                    i++;
                    while("//End_Func" != lib[i]){
                        t_str = lib[i];
                        t_str.replace("__NUM__", QString::number(num_uart));
                        t_str.replace("__PINTX__", QString::number(pin_tx));
                        t_str.replace("__PORTTX__", port_tx);
                        t_str.replace("__FUNCTX__", func_tx);
                        t_str.replace("__PINRX__", QString::number(pin_rx));
                        t_str.replace("__PORTRX__", port_rx);
                        t_str.replace("__FUNCRX__", func_rx);
                        t_str.replace("__BAUDRATE__", QString::number(baudrate));
                        m_Func.append(t_str);
                        i++;
                    }
                }
            }
        }
    }
}

void Builder::ClearAllList()
{
    m_Include.clear();
    m_Prototype_Func.clear();
    m_Init_struct.clear();
    m_Init_config.clear();
    m_Call_Func.clear();
    m_Result.clear();
    m_Func.clear();
}
