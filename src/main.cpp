#include <QCoreApplication>
#include <QDebug>
#include "tcpserver.h"
#include "settingparser.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "===> Start server...";

// Загрузка настроек в структуру
    struct Settings* settings(new struct Settings);
    SettingParser * settingParser(new SettingParser(nullptr));
    settingParser->loadSettingsFromFile ("config.json", settings);

// Поднимаем TCP-SERVER
    MyTcpServer * server(new MyTcpServer(settings->serverPort));

    return a.exec();
}
