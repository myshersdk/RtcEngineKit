//
//  MysherRtcEngineKit.h
//  MysherRtcEngineKit
//
//  Created by mysher on 2020/2/19.
//  Copyright © 2020 mysher. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MysherEnumerates.h"

@class MysherRtcEngineKit;

/*!
@protocol MysherRtcEngineDelegate
@abstract
   一些状态回调的接口
@discussion
    可以添加多个接口，后添加的先调用，方法的返回值为YES时，前面的接口就不会被调用
*/
@protocol MysherRtcEngineDelegate <NSObject>
@optional

#pragma mark Delegate Methods

/*!
@method rtcEngine:didLoginStatus
@abstract
 登陆状态的通知

@param status
 相应的状态
*/
- (BOOL)rtcEngine:(MysherRtcEngineKit * _Nonnull)engine didLoginStatus:(MysherLoginStatusCode)status;

/*!
@method rtcEngine:didAnswerCall
@abstract
 拔打P2P电话后对方已接听

@param number
 对方号码
*/
- (BOOL)rtcEngine:(MysherRtcEngineKit * _Nonnull)engine didAnswerCall:(NSString * _Nullable)number;

/*!
@method rtcEngine:didIncomingCall
@abstract
 来了P2P电话

@param number
 对方号码
*/
- (BOOL)rtcEngine:(MysherRtcEngineKit * _Nonnull)engine didIncomingCall:(NSString * _Nullable)number;

/*!
@method rtcEngine:didHangupCall
@abstract
 对方已挂断P2P电话

@param number
 对方号码
*/
- (BOOL)rtcEngine:(MysherRtcEngineKit * _Nonnull)engine didHangupCall:(NSString * _Nullable)number;

/*!
@method rtcEngine:didMediaContentChange:direction:operate
@abstract
 P2P通话时，对方扬声器、麦克风、视频画面的开关状态

@param type
 扬声器、麦克风、视频画面
 
@param dir
 单方、双方
 
@param ope
 打开、关闭
*/
- (BOOL)rtcEngine:(MysherRtcEngineKit * _Nonnull)engine didMediaContentChange:(MysherMediaContentType)type direction:(MysherMediaContentDirection)dir operate:(MysherMediaContentOperator)ope;

/*!
@method rtcEngine:didNewParticipant
@abstract
 有新的人员加入会议

@param extra
 配置信息
*/
- (BOOL)rtcEngine:(MysherRtcEngineKit * _Nonnull)engine didNewParticipant:(NSArray<NSDictionary*>* _Nullable)extra;

/*!
@method rtcEngine:didRemoveParticipant
@abstract
 有人退出会议

@param peerNumbers
 退出人员的号码
*/
- (BOOL)rtcEngine:(MysherRtcEngineKit * _Nonnull)engine didRemoveParticipant:(NSArray<NSString*>* _Nullable)peerNumbers;

/*!
@method rtcEngine:didParticipantStatusChange
@abstract
 参会人员的扬声器、麦克风、视频画面的开关状态改变等

@param extra
 状态信息
*/
- (BOOL)rtcEngine:(MysherRtcEngineKit * _Nonnull)engine didParticipantStatusChange:(NSArray<NSDictionary*>* _Nullable)extra;

/*!
@method rtcEngine:didRoomStatusChange:maxWindow:windowMode
@abstract
 会议一些信息的改变，nil表示相应的参数没有改变

@param host
 房主
 
@param user
 当前最大窗显示的用户
 
@param mode
 窗口排例模式
*/
- (BOOL)rtcEngine:(MysherRtcEngineKit * _Nonnull)engine didRoomStatusChange:(NSString * _Nullable)host maxWindow:(NSString * _Nullable)user windowMode:(NSString * _Nullable)mode;

/*!
@method rtcEngine:didRecvRoomCommand:extra
@abstract
 会议房间的一些控制命令

@param cmd
 命令
 
@param extra
 相应参数
*/
- (BOOL)rtcEngine:(MysherRtcEngineKit * _Nonnull)engine didRecvRoomCommand:(MysherRoomCommandCode)cmd extra:(NSDictionary * _Nullable)extra;

@end

typedef void (^CallCompletionHandler)(MysherCallStatusCode status, NSDictionary * _Nullable extra);
typedef void (^RoomCompletionHandler)(MysherRoomStatusCode status, NSDictionary * _Nullable extra);


#pragma mark - MysherRtcEngineKit

/*!
@class MysherRtcEngineKit
@abstract
 MysherRtcEngineKit提供P2P以及视频会议通话的相关接口

@discussion
 MysherRtcEngineKit使用的是单例模式，可以有多个MysherRtcEngineDelegate接口
*/
@interface MysherRtcEngineKit : NSObject

/*!
@method sharedEngineWithDelegate
@abstract
 获取MysherRtcEngineKit实例，并设置MysherRtcEngineDelegate接口

@param delegate
 一些状态等的通知接口
*/
+ (instancetype _Nonnull)sharedEngineWithDelegate:(id<MysherRtcEngineDelegate> _Nullable)delegate;

#pragma mark - signalling

/*!
@method login:password
@abstract
 登陆默认的信令服务器

@param userName
 帐号
 
@param password
 密码，没有可以为空
*/
- (void)login:(NSString * _Nonnull)userName
     password:(NSString * _Nonnull)password;

/*!
@method login:password:server
@abstract
 登陆指定的信令服务器

@param userName
 帐号
 
@param password
 密码，没有可以为空
 
@param server
 信令服务器URL
*/
- (void)login:(NSString * _Nonnull)userName
     password:(NSString * _Nonnull)password
       server:(NSString * _Nullable)server;

/*!
@method logout
@abstract
 退出信令服务器
*/
- (void)logout;

#pragma mark - common core

/*!
@method switchCamera
@abstract
 翻转摄像头
*/
- (void)switchCamera;

/*!
@property muteSpeaker
@abstract
   YES: 关掉扬声器 NO: 打开扬声器
*/
@property (nonatomic, assign) BOOL muteSpeaker;

/*!
@property muteMic
@abstract
   YES: 关掉麦克风 NO: 打开麦克风
*/
@property (nonatomic, assign) BOOL muteMic;

/*!
@property muteVideo
@abstract
   YES: 关掉视频画面 NO: 打开视频画面
*/
@property (nonatomic, assign) BOOL muteVideo;

#pragma mark - p2p

/*!
@method startCall:andAVMode:completionHandler
@abstract
 拔打P2P电话

@param number
 对方号码
 
@param mode
 设置纯语音还是音视频通话模式
 
@param completion
 成功或失败的回调
*/
- (void)startCall:(NSString * _Nonnull)number
        andAVMode:(MysherCallMediaMode)mode
completionHandler:(CallCompletionHandler _Nullable)completion;

/*!
@method stopCall
@abstract
 挂掉P2P电话
*/
- (void)stopCall;

/*!
@method answerCall:completionHandler
@abstract
 接听P2P电话

@param mode
 设置纯语音还是音视频通话模式
 
@param completion
 成功或失败的回调
*/
- (void)answerCall:(MysherCallMediaMode)mode completionHandler:(CallCompletionHandler _Nullable)completion;

/*!
@method refuseCall
@abstract
 拒接P2P电话
*/
- (void)refuseCall;

#pragma mark - conference

/*!
@method createRoom:completionHandler
@abstract
 创建音视频会议房间

@param mode
 设置纯语音还是音视频通话模式
 
@param completion
 成功或失败的回调
*/
- (void)createRoom:(MysherCallMediaMode)mode completionHandler:(RoomCompletionHandler _Nullable)completion;

/*!
@method createRoom:completionHandler
@abstract
 创建音视频会议房间

@param config
 附带的一些配置 {@"suffix": 房间号的后缀}
 
@param mode
 设置纯语音还是音视频通话模式
 
@param completion
 成功或失败的回调
*/
- (void)createRoom:(MysherCallMediaMode)mode withConfig:(NSDictionary * _Nullable)config completionHandler:(RoomCompletionHandler _Nullable)completion;

/*!
@method joinRoom:andAVMode:completionHandler
@abstract
 加入会议房间

@param number
 房间号码
 
@param mode
 设置纯语音还是音视频通话模式
 
@param completion
 成功或失败的回调
*/
- (void)joinRoom:(NSString * _Nonnull)number andAVMode:(MysherCallMediaMode)mode completionHandler:(RoomCompletionHandler _Nullable)completion;

/*!
@method joinRoom:password:andAVMode:completionHandler
@abstract
 加入设置了密码的会议房间

@param number
 房间号码
 
@param pwd
 房间密码
 
@param mode
 设置纯语音还是音视频通话模式
 
@param completion
 成功或失败的回调
*/
- (void)joinRoom:(NSString * _Nonnull)number password:(NSString * _Nullable)pwd andAVMode:(MysherCallMediaMode)mode completionHandler:(RoomCompletionHandler _Nullable)completion;

/*!
@method refuseJoin
@abstract
 拒绝加入会议房间

@param number
 房间号码
*/
- (void)refuseJoin:(NSString * _Nonnull)number;

/*!
@method leaveRoom
@abstract
 离开会议房间
*/
- (void)leaveRoom;

/*!
@method closeRoom
@abstract
 解散会议房间
*/
- (void)closeRoom;

/*!
@method inviteUser
@abstract
 邀请别人加入会议房间

@param inviteNumbers
 被邀请人的号码
*/
- (void)inviteUser:(NSArray<NSString*>* _Nonnull)inviteNumbers;

/*!
@method wantVideoData
@abstract
 设置获取指定参会者的视频数据

@param peerNumbers
 需要获取视频数据的参会者号码
*/
- (void)wantVideoData:(NSArray<NSString*>* _Nullable)peerNumbers;

@end
