#ifndef PUBLIC_DATA_H
#define PUBLIC_DATA_H
#include <QString>
#include <QDataStream>
#include <QProcess>
enum Role{LOGIN_BUTTON,LOGOUT_BUTTON};
enum Infofiled{ACCOUNT,PASSWD,ISAUTO,ISREM};

struct UserInfo{
    QString account;
    QString passwd;
    bool isAuto;
    bool isRem;
};
Q_DECLARE_METATYPE(UserInfo)

inline QDataStream &operator <<(QDataStream & out,const UserInfo &u){
    out<<u.account<<u.passwd<<u.isAuto<<u.isRem;
    return out;
}
inline QDataStream &operator >>(QDataStream & in,UserInfo &u){
    in>>u.account>>u.passwd>>u.isAuto>>u.isRem;
    return in;
}

inline bool Ping(){
    QProcess process;
    process.start("ping www.baidu.com -n 1 -w 1500");
    process.waitForFinished();
    return process.exitCode()==0;
}

struct responseResult{
    int resultCode;
    //QString totalflow;

    QString user_name;
    QString ip_addr;
    QString sum_seconds;
    QString usedflow;
    QString surplusmoney;
};

#endif // PUBLIC_DATA_H
