#include "controlfiles.h"
#include "QFile"
#include "QTextStream"
#include <QJsonObject> // { }
#include <QJsonArray> // [ ]
#include <QJsonDocument> // 解析Json
#include <QJsonValue> // int float double bool null { } [ ]
#include <QJsonParseError>
#include "QDebug"
#include <QStandardPaths>
#include "QDir"
#include "QApplication"
QString controlFiles::dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

controlFiles::controlFiles()
{

}

void controlFiles::saveUser(QString user,QString password){
     QString dir_str = QApplication::applicationDirPath()+"/data/user/";
     QDir _dir;
     if(!_dir.exists(dir_str))
     {
         _dir.mkpath(dir_str);
     }

     QFile file(QApplication::applicationDirPath()+"/data/user/"+user+".json");

    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "can't open error!";
        return;
    }
    QJsonObject rootObject;
    rootObject.insert("user",user);
    rootObject.insert("password",password);
    // 将json对象里的数据转换为字符串
    QJsonDocument doc;
    // 将object设置为本文档的主要对象
    doc.setObject(rootObject);
    QTextStream stream(&file);
    stream.setCodec("UTF-8");		// 设置写入编码是UTF8
    // 写入文件
    stream << doc.toJson();
    file.close();
}

//从文件中读取用户
void controlFiles::updateAccount(QStringList* list){
     QString dir_str = QApplication::applicationDirPath()+"/data/user/";
     QDir dir(dir_str);
     QStringList nameFilters;
     nameFilters << "*.json";
     QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);

     for(int i=0;i<files.size();i++){
        qDebug() << files[i];
        QString path = dir_str+files[i];
        QFile file(path);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            qDebug() << "can't open error!";
            return;
        }

        // 读取文件的全部内容
        QTextStream stream(&file);
        stream.setCodec("UTF-8");		// 设置读取编码是UTF8
        QString str = stream.readAll();
        file.close();
        // QJsonParseError类用于在JSON解析期间报告错误。
        QJsonParseError jsonError;
        // 将json解析为UTF-8编码的json文档，并从中创建一个QJsonDocument。
        // 如果解析成功，返回QJsonDocument对象，否则返回null
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
        // 判断是否解析失败
        if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
            qDebug() << "Json格式错误！" << jsonError.error;
            return;
        }
        QJsonObject rootObj = doc.object();
        // 根据键获取值
        QJsonValue nameValue = rootObj.value("user");
        qDebug() << "user = " << nameValue.toString();
        // 根据键获取值
        QJsonValue passValue = rootObj.value("password");
        qDebug() << "password = " << passValue.toString();
        list->push_back(nameValue.toString());
        list->push_back(passValue.toString());
     }
}
