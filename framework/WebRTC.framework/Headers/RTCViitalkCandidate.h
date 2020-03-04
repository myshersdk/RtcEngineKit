//
//  RTCViitalkCandidate.h
//  sources
//o//  Created by mandy on 2019/6/24.
//

#import <Foundation/Foundation.h>
#import "RTCMacros.h"


NS_ASSUME_NONNULL_BEGIN

RTC_EXPORT
@interface RTCViitalkSendCandidate : NSObject

- (instancetype)initCandidate:(NSString *)callSdp
                      callMid:(NSString *)callMid
                    callIndex:(NSString *)callIndex;

//sdp
@property(nonatomic, readonly) NSString *sdp;
//mid
@property(nonatomic, readonly) NSString *mid;
//index
@property(nonatomic, readonly) NSString *index;

@end

RTC_EXPORT
@interface RTCViitalkRecvCandidate : NSObject

- (instancetype)initCandidate:(NSString *)callIqId
                      callJid:(NSString *)callJid
               callPeerNumber:(NSString *)callPeerNumber
                   callIqType:(NSString *)callIqType
               callActionType:(NSString *)callActionType
                      callSdp:(NSString *)callSdp
                      callMid:(NSString *)callMid
                    callIndex:(NSString *)callIndex;

//iq消息id
@property(nonatomic, readonly) NSString *iqId;
//接收jid
@property(nonatomic, readonly) NSString *jid;
//接收的麦哲号码
@property(nonatomic, readonly) NSString *peerNumber;
//iq消息最上层类型（set/result/get/error等)
@property(nonatomic, readonly) NSString *iqType;
//jingle消息类型（transport-info,transport-add)
@property(nonatomic, readonly) NSString *actionType;
//sdp
@property(nonatomic, readonly) NSString *sdp;
//mid
@property(nonatomic, readonly) NSString *mid;
//index
@property(nonatomic, readonly) NSString *index;

@end

NS_ASSUME_NONNULL_END
