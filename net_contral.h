#ifndef NET_CONTRAL_H
#define NET_CONTRAL_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include "public_data.h"

class Settings;
class QEventLoop;

class NetContral : public QNetworkAccessManager
{
    Q_OBJECT
public:
    NetContral(QObject *parent =0);
    void login(QString account,QString passwd);     //登陆操作
    void login2();
    void logout();                                  //注销操作
    void logout2(QString account, QString passwd);
    void logout3(QString account);
    bool isOnline() const;                          //是否在线
    bool isConditionAvailable() const;              //是否满足登陆条件
    QString getUserIntranetAddress() const;
    QString getBrasAddress() const;
    //QByteArray getCurrentCookies() const;
    void loadLastState(const Settings *);           //加载上一次的状态
    void saveCurrentState(Settings*);              //保存当前状态
signals:
    void responseInfo(responseResult);
    void error(QString);
private slots:
    void handleNetReply(QNetworkReply*);            //响应相关操作里的get / post操作
private:
    QString encrytPassword(QString rawPassword);    //用户原始密文加密
    void makeCookieAvalable();                      //获取登陆用的条件
    void replyCookieSet(QNetworkReply*);            //获取登陆条件操作中响应get
    void replyLogin(QNetworkReply*);                //响应登陆里的post
    void replyLogin2(QNetworkReply*);                //响应登陆里的get
    void replyLogout(QNetworkReply*);               //响应注销里的logout
    void replyLogout2(QNetworkReply*);               //响应注销里的logconfig
    void replyLogout3(QNetworkReply*);               //响应注销里的logconfig
private:
    QEventLoop *eventloop;
    QNetworkRequest request;
//    QByteArray cookies;
    QString userIntranetAddress;
    QString brasAddress;
    bool _isOnline;
    int replyflag;
    QString accounttemp;
    QString passwdtemp;
    //以下属性不将被添加入移动版，只存在桌面版
#ifndef Q_OS_ANDROID
    bool _autoConnect;                      //与保持自动连接有关
#endif
};

#endif // NET_CONTRAL_H
