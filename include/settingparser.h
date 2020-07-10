#ifndef settingparser_H
#define settingparser_H

#include <QObject>
#include <QJsonDocument>

/*!
 * \brief Структура для хранения считанных из файла настроек
 * \author Малинин А.В.
 * \date июнь 2020г.
 *  В структуру записываются данные, считанные методом loadSettingsFromFile класса
 *  SettingParser из JSON-файла с настройками
*/
struct Settings{
    quint16 serverPort;      ///< Порт на котором поднимается TCP-SERVER
};

/*!
 * \brief Класс для считывания настроек из JSON-файла
 * \author Малинин А.В.
 * \date июнь 2020г.
 * Класс позволяет использовать методы для загрузки настроек из JSON-файла конфигурации
 */
class SettingParser : public QObject{
    Q_OBJECT

public:
    SettingParser(QObject *parent = nullptr);
    /*!
     * \brief Загружает данные из файла <fileName>.json и сохраняет в структуру <setting>
     * \param fileName Имя файла с настройками
     * \param setting Указатель на стуктуру, куда сохраняются настройки
     */
    void loadSettingsFromFile (QString fileName, struct Settings * setting);

private:
    /*!
     * \brief loadJSON Загружает данные из файла <fileName>.json и возвращает экземпляр класса QJsonDocument
     * \param fileName fileName Имя файла с настройками
     * \return  Экземпляр класса QJsonDocument в котором хранятся считанные поля
     * из файла настроек <fileName>.json
     */
    QJsonDocument loadJSON(QString fileName);
};

#endif // JSONParser_H
