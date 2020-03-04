//
//  RTCViitalkUserInfo.h
//  sources
//
//  Created by mandy on 2019/6/24.
//

#import <Foundation/Foundation.h>
#import "RTCMacros.h"


NS_ASSUME_NONNULL_BEGIN

RTC_EXPORT
@interface RTCViitalkUserInfo : NSObject

- (instancetype)initUserInfo:(NSString *)userNum
                     userJid:(NSString *)userJid
                    userName:(NSString *)userName
                 userSigning:(NSString *)userSigning
              userAvatarHash:(NSString *)userAvatarHash
                 userVersion:(NSString *)userVersion
          userContactVersion:(NSString *)userContactVersion
           userPresenceState:(NSString *)userPresenceState
            userPresenceShow:(NSString *)userPresenceShow
                    userStun:(NSString *)userStun
                    userTurn:(NSString *)userTurn
                userPeerStun:(NSString *)userPeerStun
                userPeerTurn:(NSString *)userPeerTurn
                    userRoom:(NSString *)userRoom
                 userRoomPwd:(NSString *)userRoomPwd
                   userState:(int)userState
                  userOnline:(int)userOnline
               userAvailable:(BOOL)userAvailable
            userConntectType:(int)userConntectType;

//麦哲号码
@property(nonatomic, readonly) NSString *mzNumber;
//jid
@property(nonatomic, readonly) NSString *jid;
//昵称
@property(nonatomic, readonly) NSString *name;
//个性签名
@property(nonatomic, readonly) NSString *signing;
//用户图片哈希值
@property(nonatomic, readonly) NSString *avatarHash;
//APP版本号#信令协议版本号
@property(nonatomic, readonly) NSString *version;
//通讯录版本号
@property(nonatomic, readonly) NSString *contactVersion;
//用户出席状态  call为通话中,upgrade为升级中
@property(nonatomic, readonly) NSString *presenceState;
//出席状态的显示，可任意设置
@property(nonatomic, readonly) NSString *presenceShow;
//stun服务器信息
@property(nonatomic, readonly) NSString *stun;
//turn服务器信息
@property(nonatomic, readonly) NSString *turn;
//peer stun服务器信息
@property(nonatomic, readonly) NSString *peerStun;
//peer turn服务器信息
@property(nonatomic, readonly) NSString *peerTurn;
//room id
@property(nonatomic, readonly) NSString *room;
//room pwd
@property(nonatomic, readonly) NSString *roomPwd;
//用户的帐号状态:1正常; 2封停; 3注销, -1不存在
@property(nonatomic, readonly) int state;
//用户在线,大于0表示在线
@property(nonatomic, readonly) int online;
//是否可获取
@property(nonatomic, readonly) BOOL available;
//链接类型 0=p2p+relay; 1=p2p; 2=relay
@property(nonatomic, readonly) int connectType;

@end

NS_ASSUME_NONNULL_END
