#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include "public_data.h"

class Settings : public QSettings
{
public:
    explicit Settings(QObject *parent = 0);
    ~Settings();
    bool isParameterValidate() const;       //判断和网络控制器相关的参数是否还有效
    int getDBCount() const;                 //返回账号个数
    UserInfo getUserInfo(int index) const;        //返回index的用户信息
    void addUserInfo(const UserInfo &u);             //添加用户信息
    void modifyUserInfo(int index,Infofiled filedname,QVariant value);//修改index用户的fildname的值
    void removeUserInfo(int index); //移除index的用户信息
    int getLastIndex() const;
    void setLastIndex(const int);
private:
    void updateDB();        //内部用，当db变更时用来将变化更新回文件
private:
    int lastindex;
    QList<QVariant> db;
};

#endif // SETTINGS_H
