#ifndef PROFILE_H
#define PROFILE_H

#include <QMap>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>
#include <QDebug>
#include <QObject>

struct Parameter{
    QString name;
    int code;
    QString dataType;
    QString unit;

    void read(const QJsonObject &json){
        name = json["name"].toString();
        code = json["doc"].toInt();
        dataType = json["data_type"].toString();
        unit = json["unit"].toString();
    }
};

struct FidObject{
    QString name;
    int code;
    QMap<unsigned int, Parameter> params;

    void read(const QJsonObject &json){
        name = json["name"].toString();
        code = json["code"].toInt();

        QJsonArray paramsArray = json["params"].toArray();
        for(int i = 0; i < paramsArray.size(); ++i){
            QJsonObject paramObject = paramsArray[i].toObject();
            Parameter parameter;
            parameter.read(paramObject);
            params.insert(parameter.code, parameter);
        }
    }
};

class Profile : public QObject
{
    Q_OBJECT

public:
    Profile();

    QString name;
    int profileID;
    int profileSubID;
    int LRUCode;
    int fid;
    QMap<unsigned int, QString> rciMap;
    QMap<unsigned int, QString> lccMap;
    QMap<unsigned int, FidObject> fidMap;

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
public slots:
    void loadProfile(QString fileName);
signals:
    void profileChanged();
};

#endif // PROFILE_H
