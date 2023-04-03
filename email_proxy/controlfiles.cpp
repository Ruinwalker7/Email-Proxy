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
     // 检查目录是否存在，若不存在则新建
     QDir _dir;
     if(!_dir.exists(dir_str))
     {
           bool res = _dir.mkpath(dir_str);
     }

     QFile file(QApplication::applicationDirPath()+"/data/user/"+user+".json");

    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "can't open error!";
        return;
    }
    // 定义根节点	也即是最外层 { }
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
