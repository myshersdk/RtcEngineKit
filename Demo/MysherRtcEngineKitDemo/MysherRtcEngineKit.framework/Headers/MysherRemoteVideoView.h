//
//  MysherRemoteVideoView.h
//  MysherRtcEngineKit
//
//  Created by mysher on 2020/2/24.
//  Copyright © 2020 mysher. All rights reserved.
//

#import <UIKit/UIView.h>

@class MysherRemoteVideoView;

@protocol MysherRemoteVideoViewDelegate <NSObject>
@required
- (void)remoteVideoView:(MysherRemoteVideoView * _Nonnull)view didChangeVideoView:(CGSize)size;

@end

@interface MysherRemoteVideoView : NSObject

@property (nonatomic, readonly) UIView* _Nonnull view;
@property (nonatomic, assign) id<MysherRemoteVideoViewDelegate> _Nullable delegate;

@end
