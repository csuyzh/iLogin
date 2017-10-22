#include "net_contral.h"
#include "settings.h"
#include <QNetworkReply>
#include <QNetworkCookie>
#include <QScriptEngine>
#include <QJsonDocument>
#include <QVariant>
#include <QRegExp>
#include <QStringList>
#include <QJsonObject>
#include <QFile>
#include <QEventLoop>
#include <QMessageBox>
QString errMsg = "network paramenters error !\n";
NetContral::NetContral(QObject *parent):
    QNetworkAccessManager(parent),
    _isOnline(false),
    replyflag(0)
{
    eventloop = new QEventLoop(this);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded;charset=utf-8");
    connect(this,SIGNAL(finished(QNetworkReply*)),this,SLOT(handleNetReply(QNetworkReply*)));
}

void NetContral::login(QString account, QString passwd){
    replyflag = 0;
    request.setUrl(QUrl("http://10.0.0.55:803/include/auth_action.php"));
    QString postBody = QString("action=login&username=%1&password=%2&ac_id=1&user_ip=&nas_ip=&user_mac=&save_me=%3&ajax=1").arg(account)
                .arg(passwd).arg(1);
    this->post(request,postBody.toUtf8());
    accounttemp = account;
    passwdtemp = passwd;


    //if(Ping()==true){
    //    emit error("当前网络无需登录");
        //qDebug()<<"no need to login";
    //    return;
    //}
//    if(_isConditionAvailable==false)
//        makeCookieAvalable();
//    if(_isConditionAvailable==true){
//        request.setUrl(QUrl("http://61.137.86.87:8080/portalNat444/AccessServices/login"));
//        request.setRawHeader(QByteArray("Referer"),QByteArray("http://61.137.86.87:8080/portalNat444/index.jsp"));
//        QString postBody = QString("accountID=%1\%40zndx.inter&password=%2&brasAddress=%3&userIntranetAddress=%4").arg(account)
//                    .arg(this->encrytPassword(passwd)).arg(brasAddress).arg(userIntranetAddress);
//        this->post(request,postBody.toUtf8());
//        //eventloop->exec();
//    }

}
void NetContral::login2(){
    replyflag = 1;
    request.setUrl(QUrl("http://10.0.0.55:803/srun_portal_pc_succeed.php"));
    this->get(request);
}
void NetContral::logout(){

    replyflag = 2;
    request.setUrl(QUrl("http://10.0.0.55:803/srun_portal_pc_succeed.php"));
    QString postBody = QString("");
    this->post(request,postBody.toUtf8());
}

void NetContral::logout2(QString account, QString passwd){
    replyflag = 3;
    request.setUrl(QUrl("http://10.0.0.55:803/srun_portal_pc_succeed.php"));
    QString postBody = QString("action=logout&username=%1&password=%2&ajax=%3").arg(account).arg(passwd).arg(1);
     this->post(request,postBody.toUtf8());
}
void NetContral::logout3(QString account){
    replyflag = 4;
    request.setUrl(QUrl("http://10.0.0.55:80/cgi-bin/srun_portal"));
    QString postBody = QString("action=logout&ac_id=1&username=%1&mac=&type=2").arg(account);
     this->post(request,postBody.toUtf8());
}
bool NetContral::isOnline()const{
    return _isOnline;
}

//bool NetContral::isConditionAvailable() const{
//    return _isConditionAvailable;
//}

QString NetContral::getUserIntranetAddress() const{
    return userIntranetAddress;
}

QString NetContral::getBrasAddress()const{
    return brasAddress;
}

//QByteArray NetContral::getCurrentCookies()const{
//    return cookies;
//}


void NetContral::loadLastState(const Settings *config){
     _isOnline = true;
     userIntranetAddress = config->value("NetContral/userIntranetAddress",QString()).toString();
     brasAddress = config->value("NetContral/brasAddress",QString()).toString();

}

void NetContral::saveCurrentState(Settings *config){
    if(_isOnline==true){
        config->setValue("recordeflag",1);
        config->beginGroup("NetContral");
        config->endGroup();
    }
    else{
        config->remove("recordeflag");
        config->beginGroup("NetContral");
        config->remove("");
        config->endGroup();
    }
}


void NetContral::handleNetReply(QNetworkReply *reply){
    if(reply->error()!=QNetworkReply::NoError){
        emit error(reply->errorString());
        return;
    }
    switch(replyflag){
    case 0:
        replyLogin(reply);
        break;
    case 1:
        replyLogin2(reply);
        break;
    case 2:
        replyLogout(reply);
        break;
    case 3:
        replyLogout2(reply);
        break;
    case 4:
        replyLogout3(reply);
        break;
    }
    return;
}

QString NetContral::encrytPassword(QString rawPassword){//这个方法日后需要变更其内部的加密机制，脱离js执行引擎
    QScriptEngine engine;                       //脚本解析引擎
    QScriptValueList args;                      //脚本执行参数列表
    args<<rawPassword;                               //以下先将传入的密码原文进行URI编码
    QScriptValue encodePasswd = engine.evaluate("encodeURIComponent").call(QScriptValue(),args);
    args.clear();
    QFile jsFile("://img/security.js");
    jsFile.open(QIODevice::ReadOnly);
    //从此处开始，开始解析脚本文件
    QString jsBody = QString(jsFile.readAll());
    args<<"10001"<<""<<"a8a02b821d52d3d0ca90620c78474b78435423be99da83cc190ab5cb5b9b922a4c8ba6b251e78429757cf11cde119e1eacff46fa3bf3b43ef68ceb29897b7aa6b5b1359fef6f35f32b748dc109fd3d09f3443a2cc3b73e99579f3d0fe6a96ccf6a48bc40056a6cac327d309b93b1d61d6f6e8f4a42fc9540f34f1c4a2e053445";
    QScriptValue RSAUtil = engine.evaluate(jsBody);             //获取RSAUtil对象
    //利用获取的对象获取公钥
    QScriptValue pubkey = RSAUtil.property("getKeyPair").call(QScriptValue(),args);
    args.clear();
    args<<pubkey<<encodePasswd;
    //将公钥与编码过的密码进行RSA公钥加密，然后返回
    QString encrytoPasswd = RSAUtil.property("encryptedString").call(QScriptValue(),args).toString();
    return encrytoPasswd;
}


//响应登录,根据返回值，判断不同的情况
void NetContral::replyLogin(QNetworkReply *reply){
    QByteArray array = reply->readAll();
    if(!array.isEmpty()){
        //成功
        if(array.contains("login_ok")){
            replyflag = 1;
            login2();
            return;
        }
        //执行注销操作
        else if(array.contains("IP has been online, please logout")){
            replyflag = 3;
            logout2(accounttemp,passwdtemp);
            return;
        }
        else if(array.contains("Portal not resopnse"))
        {
            logout();
            return;
        }
        else if(array.contains("Password is error"))
        {

            responseResult result;
            result.resultCode = 1;
            emit error("Password is error");
        }
        else
            emit error("Unknown cases!Try again later.");
    }

}

void NetContral::replyLogin2(QNetworkReply *reply){
    QByteArray replypageinfo = reply->readAll();
    //再判断一次
    if(replypageinfo.isEmpty()){
        emit error("Unknown cases!Try again later.");
        return;
    }
    //开始解析返回的数据     "(#fd7100;\">)(\S{6,20})(</span>)"
    responseResult result;
    int indextemp = 0;
    indextemp = replypageinfo.indexOf("</span>",indextemp);
    if ( indextemp != -1)
        result.user_name = replypageinfo.mid(indextemp-10,10);
    indextemp = replypageinfo.indexOf("</span>",indextemp+15);
    if ( indextemp != -1)
        result.ip_addr = replypageinfo.mid(indextemp-11,11);
    indextemp = replypageinfo.indexOf("</span>",indextemp+15);
    if ( indextemp != -1)
        result.usedflow = replypageinfo.mid(indextemp-9,9);
    indextemp = replypageinfo.indexOf("</span>",indextemp+15);
    if ( indextemp != -1)
        result.sum_seconds = replypageinfo.mid(indextemp-18,18);
    indextemp = replypageinfo.indexOf("</span>",indextemp+30);
    if ( indextemp != -1)
        result.surplusmoney = replypageinfo.mid(indextemp-8,8);
    _isOnline = true;
    emit responseInfo(result);
    return;


}
void NetContral::replyLogout(QNetworkReply *reply){
    QByteArray array = reply->readAll();
    if(!array.isEmpty()){
        logout2(accounttemp,passwdtemp);
    }
    return;

}

void NetContral::replyLogout2(QNetworkReply *reply){
    QByteArray replypageinfo = reply->readAll();
    responseResult result;
    //再判断一次
    if(replypageinfo.isEmpty()){
        emit error("Unknown cases!Try again later.");
        return;
    }

    else if(replypageinfo.contains("网络已断开")||replypageinfo.contains("logout_ok"))
    {

        if(_isOnline == false)  //断开时应为true，但是为false，说明是一开软件的强行下线操作
        {
            login(accounttemp,passwdtemp);
        }
        else
        {
            _isOnline = false;
            emit responseInfo(result);
        }
        return;
    }
    else
    {
//        responseResult result;
//        emit responseInfo(result);
        _isOnline = false;
        emit responseInfo(result);
//        emit error("Unknown cases!Try again later.");
        return;
    }

}
void NetContral::replyLogout3(QNetworkReply *reply){
    QByteArray replypageinfo = reply->readAll();
    responseResult result;
    //再判断一次
    if(replypageinfo.isEmpty()){
        emit error("Unknown cases!Try again later.");
        return;
    }

    else if(replypageinfo.contains("logout_ok"))
    {

        if(_isOnline == false)  //断开时应为true，但是为false，说明是一开软件的强行下线操作
        {
            login(accounttemp,passwdtemp);
        }
        else
        {
            _isOnline = false;
            emit responseInfo(result);
        }
        return;
    }
    else
    {
//        responseResult result;
//        emit responseInfo(result);
//        _isOnline = false;
//        emit responseInfo(result);
        emit error("Unknown cases!Try again later.");
        return;
    }

}

