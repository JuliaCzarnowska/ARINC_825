#include "profile.h"

Profile::Profile()
{
}

void Profile::loadProfile()
{
    QFile loadFile("C:/Users/Julia/Documents/ARINC_825/profile.json");
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject asd = loadDoc.object();
    read(loadDoc.object());
}

void Profile::read(const QJsonObject &json)
{
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
