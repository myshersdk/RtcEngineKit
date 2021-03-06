//
//  ViitalkRemoteVideoView.h
//  ViitalkRtcEngineKit
//
//  Created by mysher on 2020/2/24.
//  Copyright © 2020 mysher. All rights reserved.
//

#import <UIKit/UIView.h>

@class ViitalkRemoteVideoView;

@protocol ViitalkRemoteVideoViewDelegate <NSObject>
@required
- (void)remoteVideoView:(ViitalkRemoteVideoView * _Nonnull)view didChangeVideoViewSize:(CGSize)size;

- (void)remoteVideoView:(ViitalkRemoteVideoView * _Nonnull)view didChangeVideoViewSourceNumber:(NSString* _Nullable)sourceNumber;

@end

@interface ViitalkRemoteVideoView : NSObject

@property (nonatomic, readonly) UIView* _Nonnull view;
@property (nonatomic, assign) id<ViitalkRemoteVideoViewDelegate> _Nullable delegate;

@end
