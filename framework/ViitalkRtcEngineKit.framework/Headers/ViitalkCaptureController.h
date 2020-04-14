//
//  ViitalkCaptureController.h
//  ViitalkRtcEngineKit
//
//  Created by mysher on 2020/2/21.
//  Copyright © 2020 mysher. All rights reserved.
//

#import <UIKit/UIView.h>

// Controls the camera. Handles starting the capture, switching cameras etc.
@interface ViitalkCaptureController : NSObject

@property (nonatomic, readonly) UIView* _Nonnull view;

- (void)startCapture;
- (void)stopCapture;
- (void)switchCamera;

@end
