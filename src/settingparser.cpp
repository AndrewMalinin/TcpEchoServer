#include "settingparser.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QFile>
#include <QDebug>

QT_USE_NAMESPACE

SettingParser::SettingParser(QObject *parent) : QObject(parent){}

void SettingParser::loadSettingsFromFile (QString fileName, struct Settings* settings){
    QJsonDocument loadedJSON = loadJSON(fileName);

    QJsonObject jsonObject = loadedJSON.object();
    settings->serverPort = jsonObject.value("tcpPort").toString().toUInt();
}

QJsonDocument SettingParser::loadJSON(QString fileName){

    QFile jsonFile(fileName);

// Проверка на существование файла
    if(!jsonFile.exists(fileName)){
        qDebug().noquote() << QString("> Config file not exists %1").arg(fileName);
        QJsonDocument error;
        return error;
    }


// Если файл не открывается, то возвращем пустой QJsonDocument
    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "> Config file doesn't open";
        QJsonDocument error;
        return error;
    }

    QJsonParseError jerror;
    QJsonDocument jdoc = QJsonDocument::fromJson(jsonFile.readAll(), &jerror);

    if (QJsonParseError::NoError != jerror.error)
    {
        qDebug().noquote() << "> Error parse config file" << fileName
                 << QString("with %1 error")
                    .arg(jerror.errorString());
    }
    else
         qDebug() << "> Config file was read without errors";

    jsonFile.close();

    return jdoc;
}

