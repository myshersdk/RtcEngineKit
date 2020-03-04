//
//  RTCViitalkSdp.h
//  sources
//
//  Created by mandy on 2019/6/24.
//

#import <Foundation/Foundation.h>
#import "RTCMacros.h"
#import "RTCViitalkXmppCommon.h"


NS_ASSUME_NONNULL_BEGIN

RTC_EXPORT
@interface RTCViitalkSendSdp : NSObject

- (instancetype)initSdp:(BOOL)callInitiator
callConference:(BOOL)callConference
callAutoAccept:(BOOL)callAutoAccept
  callConntype:(RTCConnectType)callConntype
       callJid:(NSString *)callJid
 callMediaType:(NSString *)callMediaType
       callSid:(NSString *)callSid
      callStun:(NSString *)callStun
      callTurn:(NSString *)callTurn
      callRoom:(NSString *)callRoom
  callNickName:(NSString *)callNickName
  callMzNumber:(NSString *)callMzNumber
   callSdpType:(NSString *)callSdpType
       callSdp:(NSString *)callSdp;

- (instancetype)initSdp:(BOOL)callInitiator
         callConference:(BOOL)callConference
         callAutoAccept:(BOOL)callAutoAccept
           callConntype:(RTCConnectType)callConntype
                callJid:(NSString *)callJid
         callPeerNumber:(NSString *)callPeerNumber
          callMediaType:(NSString *)callMediaType
                callSid:(NSString *)callSid
               callStun:(NSString *)callStun
               callTurn:(NSString *)callTurn
               callRoom:(NSString *)callRoom
           callNickName:(NSString *)callNickName
           callMzNumber:(NSString *)callMzNumber
            callSdpType:(NSString *)callSdpType
                callSdp:(NSString *)callSdp;

//是否是通话的发起者
@property(nonatomic, readonly) BOOL initiator;
//是否多人会议
@property(nonatomic, readonly) BOOL conference;
//是否自动接听
@property(nonatomic, readonly) BOOL autoAccept;
//链接类型
@property(nonatomic, readonly) RTCConnectType conntype;
//发送者或接收者jid
@property(nonatomic, readonly) NSString *jid;
//发送者或接收者麦哲号码
@property(nonatomic, readonly) NSString *peerNumber;
//通话多媒体类型，audio/video/stream
@property(nonatomic, readonly) NSString *mediaType;
//邀请者sid
@property(nonatomic, readonly) NSString *sid;
//stun信息
@property(nonatomic, readonly) NSString *stun;
//turn信息
@property(nonatomic, readonly) NSString *turn;
//多人视频，房间号码
@property(nonatomic, readonly) NSString *room;
//本人昵称
@property(nonatomic, readonly) NSString *nickname;
//本人麦哲号码
@property(nonatomic, readonly) NSString *mznumber;
//sdp的类型
@property(nonatomic, readonly) NSString *sdpType;
//sdp
@property(nonatomic, readonly) NSString *sdp;

@end


RTC_EXPORT
@interface RTCViitalkRecvSdp : NSObject

- (instancetype)initSdp:(BOOL)callInitiator
         callConference:(BOOL)callConference
         callAutoAccept:(BOOL)callAutoAccept
           callConntype:(RTCConnectType)callConntype
               callIqId:(NSString *)callIqId
                callJid:(NSString *)callJid
         callPeerNumber:(NSString *)callPeerNumber
             callIqType:(NSString *)callIqType
         callActionType:(NSString *)callActionType
        callXmppVersion:(NSString *)callXmppVersion
          callMediaType:(NSString *)callMediaType
                callSid:(NSString *)callSid
               callStun:(NSString *)callStun
               callTurn:(NSString *)callTurn
           callNickName:(NSString *)callNickName
           callMzNumber:(NSString *)callMzNumber
            callSdpType:(NSString *)callSdpType
                callSdp:(NSString *)callSdp;

//是否是通话的发起者
@property(nonatomic, readonly) BOOL initiator;
//是否多人会议
@property(nonatomic, readonly) BOOL conference;
//是否自动接听
@property(nonatomic, readonly) BOOL autoAccept;
//链接类型
@property(nonatomic, readonly) RTCConnectType conntype;
//iq消息id
@property(nonatomic, readonly) NSString *iqId;
//发送者或接收者jid
@property(nonatomic, readonly) NSString *jid;
//发送者或接收者麦哲号码
@property(nonatomic, readonly) NSString *peerNumber;
//iq消息最上层类型（set/result/get/error等)
@property(nonatomic, readonly) NSString *iqType;
//jingle消息类型（session-initiate,session-accept)
@property(nonatomic, readonly) NSString *actionType;
//xmpp version
@property(nonatomic, readonly) NSString *xmppVersion;
//通话多媒体类型，audio/video/stream
@property(nonatomic, readonly) NSString *mediaType;
//邀请者sid
@property(nonatomic, readonly) NSString *sid;
//stun信息
@property(nonatomic, readonly) NSString *stun;
//turn信息
@property(nonatomic, readonly) NSString *turn;
//本人昵称
@property(nonatomic, readonly) NSString *nickname;
//本人麦哲号码
@property(nonatomic, readonly) NSString *mznumber;
//sdp的类型
@property(nonatomic, readonly) NSString *sdpType;
//sdp
@property(nonatomic, readonly) NSString *sdp;

@end

NS_ASSUME_NONNULL_END
