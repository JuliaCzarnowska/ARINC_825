#include "profile.h"

Profile::Profile()
{
}

void Profile::loadProfile(QString fileName)
{
    QFile loadFile(fileName);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    read(loadDoc.object());
    emit profileChanged();
}

void Profile::read(const QJsonObject &json)
{
    QJsonArray rciArray = json["rci_list"].toArray();
    for(int i = 0; i < rciArray.size(); ++i){
        QJsonObject rciObject = rciArray[i].toObject();
        rciMap.insert(rciObject["number"].toInt(),rciObject["channel"].toString());
    }

    QJsonArray lccArray = json["lcc_list"].toArray();
    for(int i = 0; i < lccArray.size(); ++i){
        QJsonObject lccObject = lccArray[i].toObject();
        lccMap.insert(lccObject["number"].toInt(),lccObject["channel"].toString());
    }

    QJsonArray fidArray = json["fid_list"].toArray();
    for(int i = 0; i < fidArray.size(); ++i){
        QJsonObject fidObject = fidArray[i].toObject();
        FidObject fid;
        fid.read(fidObject);
        fidMap.insert(fid.code, fid);
    }

}
