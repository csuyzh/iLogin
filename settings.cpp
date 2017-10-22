#include "settings.h"

Settings::Settings(QObject *parent) :
    QSettings("config.ini",IniFormat,parent),
    lastindex(0)
{
    if(this->contains("userinfo/list")==true){
        this->beginGroup("userinfo");
        lastindex = this->value("lastindex",0).toInt();
        db= this->value("list").toList();
        this->endGroup();
    }
}

Settings::~Settings(){
    this->beginGroup("userinfo");
    this->setValue("lastindex",lastindex);
    this->endGroup();
}

bool Settings::isParameterValidate()const{
    if(this->contains("recordeflag")==false)
        return false;
    if(Ping()==false)
        return false;
    return true;
}

int Settings::getDBCount()const{
    return db.length();
}

UserInfo Settings::getUserInfo(int index) const{
    return db.at(index).value<UserInfo>();
}

void Settings::addUserInfo(const UserInfo &u){
    QVariant tmp;
    tmp.setValue(u);
    db.append(tmp);
    updateDB();
}

void Settings::modifyUserInfo(int index, Infofiled filedname, QVariant value){
    if(index<0||index>=db.length())
        return;
    UserInfo tmpData = db[index].value<UserInfo>();
    switch(filedname){
    case ACCOUNT:
        break;
    case PASSWD:
       tmpData.passwd=value.toString();
        break;
    case ISAUTO:
        tmpData.isAuto =value.toBool();
        break;
    case ISREM:
        tmpData.isRem = value.toBool();
        if(tmpData.isRem==false)
            tmpData.passwd.clear();
        break;
    }
    db[index] = QVariant::fromValue(tmpData);
    updateDB();
}

void Settings::removeUserInfo(int index){
    db.removeAt(index);
    updateDB();
}

int Settings::getLastIndex()const{
    return lastindex;
}

void Settings::setLastIndex(const int index){
    lastindex = index;
}

void Settings::updateDB(){
    this->beginGroup("userinfo");
    this->setValue("list",db);
    this->endGroup();
}
