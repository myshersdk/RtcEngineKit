/*
 company：mysher
 author：mandy
 time：2019-06-19
 */

#import <Foundation/Foundation.h>
#import "RTCMacros.h"


NS_ASSUME_NONNULL_BEGIN

// login state
typedef NS_ENUM(int, RTCLoginState) {
    RTCLOGIN_STATE_NONE = 0,                  //无状态
    RTCLOGIN_STATE_START,                     //登录初始化
    RTCLOGIN_STATE_OPENING,                   //登录授权中
    RTCLOGIN_STATE_OPEN,                      //登录成功
    RTCLOGIN_STATE_CLOSED,                    //登录失败
};

// login error type
typedef NS_ENUM(int, RTCLoginError) {
    RTCLOGIN_ERROR_NONE = 0,                   //没有错误
    RTCLOGIN_ERROR_XML,                        //xml错误
    RTCLOGIN_ERROR_STREAM,                     //流错误
    RTCLOGIN_ERROR_VERSION,                    //xmpp版本错误
    RTCLOGIN_ERROR_UNAUTHORIZED,               //用户未授权
    RTCLOGIN_ERROR_TLS,                        //TLS连接失败
    RTCLOGIN_ERROR_AUTH,                       //授权失败
    RTCLOGIN_ERROR_BIND,                       //资源绑定失败
    RTCLOGIN_ERROR_CONNECTION_CLOSED,          //连接关闭
    RTCLOGIN_ERROR_DOCUMENT_CLOSED,            //流关闭
    RTCLOGIN_ERROR_SOCKET,                     //socket错误
    RTCLOGIN_ERROR_NETWORK_TIMEOUT,            //连接超时
    RTCLOGIN_ERROR_MISSING_USERNAME,           //用户名错误
    RTCLOGIN_ERROR_STREAM_CONFLICT,            //异地登录
    RTCLOGIN_ERROR_XMPP_THREAD_NEW_FAILURE,    //xmpp_thread new失败
    RTCLOGIN_ERROR_PING_TIME_OUT               //心跳超时
};

//user presence state
typedef NS_ENUM(int, RTCPresenceState) {
    RTCPRESENCE_SHOW_NONE = 0,                  //无状态
    RTCPRESENCE_SHOW_OFFLINE,                   //离线
    RTCPRESENCE_SHOW_XA,                        //悠闲
    RTCPRESENCE_SHOW_AWAY,                      //离开
    RTCPRESENCE_SHOW_DND,                       //忙碌
    RTCPRESENCE_SHOW_ONLINE,                    //在线
    RTCPRESENCE_SHOW_CHAT                       //交谈中
};

//user query type
typedef NS_ENUM(int, RTCUserQueryType) {
    RTCUSER_QUERY_OWN = 0,                      //本人信息
    RTCUSER_QUERY_USER,                         //他人信息
    RTCUSER_QUERY_OWN_NOTIFY,                   //其他设备修改本用户信息
    RTCUSER_QUERY_ADAPTER                       //投屏器绑定的适配盒子信息
};

//联系人修改（增加、删除、更改）结构体
typedef NS_ENUM(int, RTCContactUpdateType) {
    RTCCONTACT_ADD,                             //联系人增加
    RTCCONTACT_DELETE,                          //联系人删除
    RTCCONTACT_UPDATE                           //联系人更改
};

//链接类型
typedef NS_ENUM(int, RTCConnectType) {
    RTCCONNECT_AUTO,                            //自动选择P2P或Relay链接
    RTCCONNECT_P2P,                             //P2P链接
    RTCCONNECT_RELAY                            //Relay链接
};

NS_ASSUME_NONNULL_END
