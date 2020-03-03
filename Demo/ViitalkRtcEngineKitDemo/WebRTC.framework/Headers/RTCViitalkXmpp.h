/*
 company：mysher
 author：mandy
 time：2019-06-19
 */

#import "RTCMacros.h"
#import "RTCViitalkUserInfo.h"
#import "RTCViitalkSdp.h"
#import "RTCViitalkCandidate.h"
#import "RTCViitalkContact.h"


NS_ASSUME_NONNULL_BEGIN



RTC_EXPORT
@interface RTCViitalkXmpp : NSObject

/*
 函数: 加载ViitalkXmpp SDK
 参数: 无
 结果: YES:     函数调用成功
       NO:     函数调用失败
 备注:
 */
+ (BOOL)loadViitalkXmpp;

/*
 函数: 卸载ViitalkXmpp SDK
 参数: 无
 结果: YES:     函数调用成功
       NO:     函数调用失败
 备注:
 */
+ (BOOL)unloadViitalkXmpp;

/*
 函数: 用户登录
 参数: serverIp:      服务IP
      user:          用户名
      pwd:           密码
      source:        资源名
      version:       软件版本号
 completionHandler   登录回调(state:登录状态 error:登录错误类型 errorDesc:错误详情)
 结果: YES:     函数调用成功
       NO:     函数调用失败，传参出错
 备注:
 */
+ (BOOL)Login:(NSString *)serverIp
         user:(NSString *)user
          pwd:(NSString *)pwd
       source:(NSString *)source
      version:(NSString *)version
completionHandler:(nullable void (^)(RTCLoginState state,
                                     RTCLoginError error,
                                     NSString *_Nullable errorDesc))completionHandler;

/*
 函数: 用户退出登录
 参数: 无
 结果: YES:     函数调用成功
       NO:     函数调用失败
 备注:
 */
+ (BOOL)Logoff;

/*
 函数: 设置用户状态
 参数: available: 是否可获取
      show:      用户状态类型
      state:    用户出席状态（如：正在升级中等状态，目前只使用下面三种状态）
                在线 = "online";
                通话中 = "call";
                升级中 = "upgrade";
 结果: YES:     函数调用成功
       NO:     函数调用失败，传参出错
 备注:
 */
+ (BOOL)SetUserPresence:(BOOL)available
                   show:(RTCPresenceState)show
                  state:(NSString *)state;

/*
 函数: 查询本人和他人的用户信息
 参数: numbers:    查询本人信息，为空值(@"")
                  查询他人信息，用户麦哲号码集合,以,号隔开（8010014733,8010013638,8010014994,...)
 completionHandlera: 查询用户回调函数（type:查询类型 info:用户信息）
 结果: YES:     函数调用成功
       NO:     函数调用失败，传参出错
 备注:
 */
+ (BOOL)QueryUserInfo:(NSString *)numbers
    completionHandler:(nullable void (^)(RTCUserQueryType type,
                                          RTCViitalkUserInfo *_Nullable info))completionHandler;

/*
 函数: 发送SDP
 参数: sdp:       SDP信息
                 一对一通话(p2p)，发送通话邀请(sdpType=@"offer")，必须传入的值(initiator,conference,autoAccept,conntype,jid,
                 mediaType,sid,stun,turn,mznumber,sdpType,sdp)，剩下的值(BOOL为NO，枚举型为第一个值，字符串则为nil)
                 一对一通话(p2p)，发送通话应答(sdpType=@"answer")，必须传入的值(initiator,conference,autoAccept,jid,mediaType,
                 sid,mznumber,sdpType,sdp)，剩下的值(BOOL为NO，枚举型为第一个值，字符串则为nil)
                 多人会议(conference)，发送通话邀请（无通话应答），需要传入的值(initiator,conference,mediaType,sid,mznumber,sdpType,sdp,room)，剩下的值(BOOL为NO，枚举型为第一个值，字符串则为nil)
 结果: YES:       函数调用成功
       NO:       函数调用失败，传参出错
 
 备注:
 */
+ (BOOL)SendSdp:(RTCViitalkSendSdp *)sdp;
/*
 函数：注册接收SDP回调
 sdp:  接收的SDP信息
 */
+ (void)RegisterRecvSdp:(nullable void (^)(RTCViitalkRecvSdp *_Nullable sdp))completionHandler;

/*
 函数: 一对一通话,发送candidates
 参数: sdp:         SDP信息(见发送SDP）
      candidate    candidate信息（sdp,mid,index三个都不能为空值）
 结果: YES:       函数调用成功
       NO:       函数调用失败，传参出错
 备注:
 */
+ (BOOL)SendCandidates:(RTCViitalkSendSdp *)sdp
                candidate:(RTCViitalkSendCandidate *)candidate;
/*
 函数：注册接收Candidate回调
 candidate:  接收的candidate信息
 */
+ (void)RegisterRecvCandidate:(nullable void (^)(RTCViitalkRecvCandidate *_Nullable candidate))completionHandler;

/*
 函数: 发送通话终止信息
 参数: reason:   终止原因(sucess 用户主动挂断 busy 用户通话中 decline 用户拒接 incompatible-parameters 音视频参数不兼容
 failed-application 应用链接失败 connectivity-error 链接失败)
      sid:      邀请者sid
      jid:       发送方Jid
      data:     扩展（暂未使用）
 结果: YES:       函数调用成功
       NO:       函数调用失败，传参出错
 备注: 无
 */
+ (BOOL)SendTerminal:(NSString *)reason
                    sid:(NSString *)sid
                    jid:(NSString *)jid;
/*
 函数：注册接收通话终止信息回调
 参数：reason:                接收到对方挂断电话原因,原因如下：
                             sucess                       用户主动挂断
                             busy                         用户通话中
                             decline                         用户拒接
                             incompatible-parameters         音视频参数不兼容
                             failed-application             应用链接失败
                             connectivity-error             链接失败
     sid:                    邀请者sid
     jid:                    接收Jid
 */
+ (void)RegisterRecvTerminal:(nullable void (^)(NSString *_Nullable reason, NSString *_Nullable sid, NSString *_Nullable jid))completionHandler;

/*
 函数: 发送多媒体移除或恢复信息
 参数: type:     类型 0为音频， 1为视频， 2为扬声器
      both:     0移除或恢复发送方，1移除或恢复两方
      removeOrRecover:0为移除，1为恢复
      jid:      发送方JID
      sid:     邀请者sid
 结果: YES:       函数调用成功
       NO:       函数调用失败，传参出错
 备注: 无
 */
+ (BOOL)SendMediaContentChange:(int)type
                             both:(int)both
                  removeOrRecover:(int)removeOrRecover
                              jid:(NSString *)jid
                              sid:(NSString *)sid;
/*
 函数：注册接收多媒体内容修改回调
 参数：type              0为音频，1为视频，2为扬声器
      both              0发送方，1两方
      removeOrRecover   0为移除，1为恢复
      jid:              接收Jid
 */
+ (void)RegisterRecvMediaContentChange:(nullable void (^)(int type, int both, int removeOrRecover, NSString *_Nullable jid))completionHandler;

/*
 函数: 增加、删除、修改单个联系人
 参数: name:          用户昵称
      mzNumber:      用户麦哲号码
      newMzNumber:   用户新麦哲号码
      autoAccept:    是否自动接听
      type:          更新类型（增加、删除、更改）
 completionHandler:  更新单个联系人回调（type:更新类型（增加、删除、更改）version:成功后，生成的最新的联系人版本号
 number:联系人麦哲号码 success:是否成功）
 结果: YES:        函数调用成功
       NO:        函数调用失败，传参出错
 备注: 无
 */
+ (BOOL)UpdateSingleContact:(NSString *)name
                    mzNumber:(NSString *)mzNumber
                 newMzNumber:(NSString *)newMzNumber
                  autoAccept:(BOOL)autoAccept
                  updateType:(RTCContactUpdateType)updateType
           completionHandler:(nullable void (^)(RTCContactUpdateType type,
                                                NSString *_Nullable version,
                                                NSString *_Nullable number, BOOL success))completionHandler;
/*
 函数: 注册其他设备修改联系人通知回调
 参数: version:           最新的联系人版本号
      type:              联系人修改类型
      name:              联系人昵称
      number:            联系人旧麦哲号码
      newNumber:         联系人新麦哲号码
      autoAccept:        自动接听
 */
+ (void)RegisterContactModifyByOthers:(nullable void (^)(NSString *_Nullable version, RTCContactUpdateType type,
                                                         NSString *_Nullable name, NSString *_Nullable number, NSString *_Nullable newNumber, BOOL autoAccept))completionHandler;
/*
 函数: 批量获取联系人
 参数: contactVer:  *联系人版本号,服务器根据版本号获取联系人,当需要全部获取服务器的“联系人”时，pContactVer="0"
 completionHandler:(allClear:当all值为1时，客户端需要清空本地的联系人记录 version:最新的联系人版本号 count:联系人个数 contactArray:联系人信息列表)
 结果: YES:            函数调用成功
       NO:            函数调用失败，传参出错
 备注:
 */
+ (BOOL)GetBatchContact:(NSString *)contactVer
      completionHandler:(nullable void (^)(NSString *_Nullable allClear,
                                           NSString *_Nullable version, int count, NSArray<RTCViitalkContact *> *_Nullable contactArray))completionHandler;

/*
 函数: 秒开功能
 参数: jid:   发送者JID
      sid:   通话SID
 结果: YES:            函数调用成功
       NO:            函数调用失败，传参出错
 备注:
 */
+ (BOOL)SendSecondOpen:(NSString *)jid
                   sid:(NSString *)sid;
/*
 函数: 注册接收秒开功能回调
 参数: jid:    发送者JID
      sid:   通话SID
 */
+ (void)RegisterRecvSecondOpen:(nullable void (^)(NSString *_Nullable jid, NSString *_Nullable sid))completionHandler;
/*
 函数: 上报通话链路和turn信息到服务器
 参数: sid:            通话SID(p2p通话为
      connectionType: 链路类型（local / prflx / stun / relay)
      turn:           turn IP地址
 结果: YES:            函数调用成功
       NO:            函数调用失败，传参出错
 
 备注:
 */
+ (BOOL)ReportConnectionInfoToServer:(NSString *)sid
               connectionType:(NSString *)connectionType
                         turn:(NSString *)turn;
/*
 函数: 向服务器发送通用信息
 参数:business 业务类型
     ssource   业务源
     content   业务内容
 结果: YES:        函数调用成功
       NO:        函数调用失败，传参出错
 备注: 获取会员信息，配置信息等
 */
+ (BOOL)SendCommonInfoToServer:(NSString *)business
                       ssource:(NSString *)ssource
                       content:(NSString *)content;
/*
 函数：注册接收服务器发送通用信息回调
 参数：business 业务类型
      ssource   业务源
      content   业务内容
 */
+ (void)RegisterRecvCommonInfoFromServer:(nullable void (^)(NSString *_Nullable business, NSString *_Nullable ssource, NSString *_Nullable content))completionHandler;
/*
 函数: 一对一通话（P2P），发送通用信息给对方
 参数:jid        发送JID
     business  业务类型
     content   业务内容
 结果: YES:        函数调用成功
       NO:        函数调用失败，传参出错
 备注:
 */
+ (BOOL)SendCommonInfoToPeer:(NSString *)jid
                    business:(NSString *)business
                     content:(NSString *)content;
/*
 函数:注册一对一通话（P2P），接收通用信息回调
 参数:jid        发送JID
     business  业务类型
     content   业务内容
 */
+ (void)RegisterRecvSendCommonInfoFromPeer:(nullable void (^)(NSString *_Nullable jid, NSString *_Nullable business, NSString *_Nullable content))completionHandler;
/*
 函数: 多人通话，发送多人会议通用信息
 参数:action 业务类型
     roomId   房间号
     number   麦哲号码
     ssource   业务源
     content  业务内容
 结果:YES:        函数调用成功
      NO:        函数调用失败，传参出错
 备注:
 */
+ (BOOL)SendCommonInfoToConference:(NSString *)action
                            roomId:(NSString *)roomId
                            number:(NSString *)number
                           ssource:(NSString *)ssource
                           content:(NSString *)content;
/*
 函数: 注册多人通话，接收多人会议通用信息回调
 参数:action 业务类型
     roomId   房间号
     ssource   业务源
     content  业务内容
 */
+ (void)RegisterRecvCommonInfoFromConference:(nullable void (^)(NSString *_Nullable action, NSString *_Nullable roomId, NSString *_Nullable ssource, NSString *_Nullable content))completionHandler;
@end

NS_ASSUME_NONNULL_END
