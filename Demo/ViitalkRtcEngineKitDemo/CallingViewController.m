//
//  CallingViewController.m
//  ViitalkRtcEngineKitDemo
//
//  Created by mysher on 2020/2/20.
//  Copyright © 2020 mysher. All rights reserved.
//

#import "CallingViewController.h"
#import "ViitalkRtcEngineKit/ViitalkRtcEngineKit.h"
#import "ViitalkRtcEngineKit/ViitalkLocalVideoView.h"
#import "ViitalkRtcEngineKit/ViitalkRemoteVideoView.h"

#import <AVFoundation/AVUtilities.h>

@interface CallingViewController () <ViitalkRtcEngineDelegate, ViitalkRemoteVideoViewDelegate>

@property (nonatomic, strong) ViitalkRtcEngineKit *kit;

@property (nonatomic, strong) UIButton* logoutButton;

@property (nonatomic, strong) UITextField *callNumberTextField;
@property (nonatomic, strong) UIButton *videoCallButton;
@property (nonatomic, strong) UIButton *audioCallButton;
@property (nonatomic, strong) UIButton *createConferenceButton;
@property (nonatomic, strong) UIButton *switchCameraButton;
@property (nonatomic, strong) UIButton *hangupButton;
@property (nonatomic, strong) UIButton *speakerMuteButton;
@property (nonatomic, strong) UIButton *micMuteButton;
@property (nonatomic, strong) UIButton *videoMuteButton;
@property (nonatomic, strong) UIButton *inviteButton;
@property (nonatomic, strong) UIView* callView;

@property (nonatomic, strong) ViitalkRemoteVideoView* p2pRemoteView;
@property (nonatomic, strong) NSMutableArray<ViitalkRemoteVideoView*>* remoteViews;
@property (nonatomic, strong) NSMutableArray<NSDictionary*>* peerNumbers;

@property (nonatomic) int currentPage;

@property (nonatomic) BOOL hasMuteSpeaker;
@property (nonatomic) BOOL hasMuteMic;
@property (nonatomic) BOOL hasMuteVideo;

@property (nonatomic) BOOL isConference;
@property (nonatomic) BOOL isCalling;

@end

@implementation CallingViewController

@synthesize kit = _kit;
@synthesize logoutButton = _logoutButton;
@synthesize callNumberTextField = _callNumberTextField;
@synthesize videoCallButton = _videoCallButton;
@synthesize audioCallButton = _audioCallButton;
@synthesize createConferenceButton = _createConferenceButton;
@synthesize switchCameraButton = _switchCameraButton;
@synthesize hangupButton = _hangupButton;
@synthesize speakerMuteButton = _speakerMuteButton;
@synthesize micMuteButton = _micMuteButton;
@synthesize videoMuteButton = _videoMuteButton;
@synthesize inviteButton = _inviteButton;
@synthesize callView = _callView;
@synthesize p2pRemoteView = _p2pRemoteView;
@synthesize remoteViews = _remoteViews;
@synthesize peerNumbers = _peerNumbers;
@synthesize currentPage = _currentPage;
@synthesize hasMuteSpeaker = _hasMuteSpeaker;
@synthesize hasMuteMic = _hasMuteMic;
@synthesize hasMuteVideo = _hasMuteVideo;
@synthesize isConference = _isConference;
@synthesize isCalling = _isCalling;

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self.view setBackgroundColor:[UIColor whiteColor]];

    // Do any additional setup after loading the view.
    [self.view addSubview:self.callNumberTextField];
    [self.view addSubview:self.videoCallButton];
    [self.view addSubview:self.audioCallButton];
    [self.view addSubview:self.createConferenceButton];
    [self.view addSubview:self.logoutButton];
    
    _callNumberTextField.text = @"8010019153";
    // _callNumberTextField.text = @"8010016778";
    
    self.kit = [ViitalkRtcEngineKit sharedEngineWithDelegate:self];
    self.remoteViews = [NSMutableArray array];
    self.peerNumbers = [NSMutableArray array];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self.kit removeDelegate:self];
    [super viewWillDisappear:animated];
}

#pragma mark - get

- (UITextField*)callNumberTextField {
    if(!_callNumberTextField) {
        _callNumberTextField = [[UITextField alloc] initWithFrame:CGRectMake(40, 30, CGRectGetWidth(self.view.frame) - 80, 28)];
        _callNumberTextField.backgroundColor = [UIColor lightGrayColor];
        _callNumberTextField.keyboardType = UIKeyboardTypeNumberPad;
    }
    return _callNumberTextField;
}

- (UIButton*)videoCallButton {
    if(!_videoCallButton) {
        _videoCallButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [_videoCallButton addTarget:self action:@selector(OnVideoCall:) forControlEvents:UIControlEventTouchUpInside];
        _videoCallButton.frame = CGRectMake(40, CGRectGetMaxY(self.callNumberTextField.frame) + 10, 80, 36);
        [_videoCallButton setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
        _videoCallButton.layer.borderWidth = .5;
        [_videoCallButton setTitle:@"视频拨打" forState:UIControlStateNormal];
    }
    return _videoCallButton;
}

- (UIButton*)audioCallButton {
    if(!_audioCallButton) {
        _audioCallButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [_audioCallButton addTarget:self action:@selector(OnAudioCall:) forControlEvents:UIControlEventTouchUpInside];
        _audioCallButton.frame = CGRectMake(CGRectGetMaxX(self.videoCallButton.frame) + 20, CGRectGetMaxY(self.callNumberTextField.frame) + 10, 80, 36);
        [_audioCallButton setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
        _audioCallButton.layer.borderWidth = .5;
        [_audioCallButton setTitle:@"语音拨打" forState:UIControlStateNormal];
    }
    return _audioCallButton;
}

- (UIButton*)createConferenceButton {
    if(!_createConferenceButton) {
        _createConferenceButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [_createConferenceButton addTarget:self action:@selector(OnCreateConference:) forControlEvents:UIControlEventTouchUpInside];
        _createConferenceButton.frame = CGRectMake(CGRectGetMaxX(self.audioCallButton.frame) + 20, CGRectGetMaxY(self.callNumberTextField.frame) + 10, 80, 36);
        [_createConferenceButton setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
        _createConferenceButton.layer.borderWidth = .5;
        [_createConferenceButton setTitle:@"创建会议" forState:UIControlStateNormal];
    }
    return _createConferenceButton;
}

- (UIButton*)logoutButton {
    if(!_logoutButton) {
        _logoutButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [_logoutButton addTarget:self action:@selector(OnLogoutButtonEvent:) forControlEvents:UIControlEventTouchUpInside];
        _logoutButton.frame = CGRectMake(CGRectGetWidth(self.view.frame) / 2 - 80, CGRectGetHeight(self.view.frame) - 50, 180, 45);
        [_logoutButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
        _logoutButton.layer.borderColor = [UIColor blackColor].CGColor;
        _logoutButton.layer.borderWidth = .5;
        [_logoutButton setTitle:@"退出登陆" forState:UIControlStateNormal];
    }
    return _logoutButton;
}

- (void)OnLogoutButtonEvent:(UIButton*)sender
{
    [self.kit logout];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(.1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self.navigationController popViewControllerAnimated:YES];
    });
}

- (void)OnVideoCall:(UIButton*)sender
{
    [self startCall:_callNumberTextField.text andMode:VIITALK_CALL_MEDIA_MODE_AV];
}

- (void)OnAudioCall:(UIButton*)sender
{
    [self startCall:_callNumberTextField.text andMode:VIITALK_CALL_MEDIA_MODE_AUDIO];
}

- (void)OnCreateConference:(UIButton*)sender
{
    [self.kit createRoom:VIITALK_CALL_MEDIA_MODE_AV completionHandler:^(ViitalkRoomStatusCode status, NSDictionary * _Nullable extra) {
        if(status == VIITALK_ROOM_SUCCESS)
        {
            NSLog(@"创建房间成功");
            self.isConference = YES;
            [self processStartCallSuccess:extra];
        }
        else
        {
            if(status == VIITALK_ROOM_ERROR_EXIST)
            {
                NSLog(@"创建房间失败，房间已经存在");
            }
            else if(status == VIITALK_ROOM_ERROR_PERMISSION)
            {
                NSLog(@"创建房间失败，没有权限");
            }
            else if(status == VIITALK_ROOM_ERROR_CREATE)
            {
                NSLog(@"创建房间失败， 其它原因");
            }
            else if(status == VIITALK_ROOM_ERROR_JOIN)
            {
                NSLog(@"创建房间成功后，加入房间失败");
            }
        }
    }];
}

- (void)OnSwitchCamera:(UIButton*)sender
{
    [self.kit switchCamera];
}

- (void)OnHangup:(UIButton*)sender
{
    if(self.isConference)
    {
        // 解散房间
        // [self.kit closeRoom];

        // 离开房间
        [self.kit leaveRoom];
    }
    else
    {
        [self.kit stopCall];
        self.isCalling = NO;
    }
    [self.callView removeFromSuperview];
    self.callView = nil;
}

- (void)OnSpeakerMute:(UIButton*)sender
{
    _hasMuteSpeaker = !_hasMuteSpeaker;
    self.kit.muteSpeaker = _hasMuteSpeaker;
    
    // 测试会议模式下关闭对方的设备
    // [self.kit sendRoomCommand:_hasMuteSpeaker ? VIITALK_ROOM_CMD_CLOSE_SPEAKER : VIITALK_ROOM_CMD_OPEN_SPEAKER toUser:_peerNumbers[0][@"peerNumber"]];
}

- (void)OnMicMute:(UIButton*)sender
{
    _hasMuteMic = !_hasMuteMic;
    self.kit.muteMic = _hasMuteMic;
    
    // 测试会议模式下关闭对方的设备
    // [self.kit sendRoomCommand:_hasMuteMic ? VIITALK_ROOM_CMD_CLOSE_MIC : VIITALK_ROOM_CMD_OPEN_MIC toUser:_peerNumbers[0][@"peerNumber"]];
}

- (void)OnVideoMute:(UIButton*)sender
{
    _hasMuteVideo = !_hasMuteVideo;
    self.kit.muteVideo = _hasMuteVideo;
    
    // 测试会议模式下关闭对方的设备
    // [self.kit sendRoomCommand:_hasMuteVideo ? VIITALK_ROOM_CMD_CLOSE_VIDEO : VIITALK_ROOM_CMD_OPEN_VIDEO toUser:_peerNumbers[0][@"peerNumber"]];
}

- (void)OnInvite:(UIButton*)sender
{
    if(self.isConference)
    {
        [self.kit inviteUser:@[@"8010016778"]];
        
        // 测试踢人
        // [self.kit sendRoomCommand:VIITALK_ROOM_CMD_LEAVE_ROOM toUser:_peerNumbers[0][@"peerNumber"]];
        
        // 测试翻页
        // _currentPage += 1;
        // [self resetRemoteVideoData];
    }
    else
    {
        // P2P转会议模式
        [self.kit createRoom:VIITALK_CALL_MEDIA_MODE_AV completionHandler:^(ViitalkRoomStatusCode status, NSDictionary * _Nullable extra) {
            if(status == VIITALK_ROOM_SUCCESS)
            {
                NSLog(@"创建房间成功");
                self.isConference = YES;
                [self processStartCallSuccess:extra];

                // 成功创建房间后，再邀请对方加入会议
                [self.kit inviteUser:@[@"8010016778"]];
            }
            else
            {
                if(status == VIITALK_ROOM_ERROR_EXIST)
                {
                    NSLog(@"创建房间失败，房间已经存在");
                }
                else if(status == VIITALK_ROOM_ERROR_CREATE)
                {
                    NSLog(@"创建房间失败， 其它原因");
                }
                else if(status == VIITALK_ROOM_ERROR_JOIN)
                {
                    NSLog(@"创建房间成功后，加入房间失败");
                }
            }
        }];
    }
}


- (void)startCall:(NSString*)number andMode:(ViitalkCallMediaMode)mode
{
    [self.kit startCall:number andAVMode:mode completionHandler:^(ViitalkCallStatusCode status, NSDictionary *extra) {
        switch (status) {
            case VIITALK_CALL_SUCCESS:
                self.isConference = NO;
                self.isCalling = YES;
                [self processStartCallSuccess:extra];
                break;
                
            case VIITALK_CALL_ERROR_INROOM:
                NSLog(@"在会议中，直接加入");
                [self processJoinRoom:extra[@"room"] withPassword:extra[@"roompwd"] andAVMode:mode];
                break;
                
            case VIITALK_CALL_ERROR_CALLING:
                NSLog(@"正在通话中");
                break;
                
            case VIITALK_CALL_ERROR_OFFLINE:
                NSLog(@"不在线");
                break;
                
            case VIITALK_CALL_ERROR_UPGRADE:
                NSLog(@"正在升级中");
                break;
                
            case VIITALK_CALL_ERROR_NOTEXIST:
                NSLog(@"该用户不存在");
                break;
                
            case VIITALK_CALL_ERROR_FORBIDDEN:
                NSLog(@"该用户被封禁");
                break;
                
            case VIITALK_CALL_ERROR_LOGOUT:
                NSLog(@"该用户已注销");
                break;
                
            case VIITALK_CALL_ERROR_OTHER:
                NSLog(@"sdk内部错误");
                break;
                
            default:
                break;
        }
    }];
}

- (void)processStartCallSuccess:(NSDictionary*)extra
{
    dispatch_async(dispatch_get_main_queue(), ^{
        if(self.callView)
        {
            // 简单处理，直接全部移除，p2p转会议模式后会跑这里
            [self.callView removeFromSuperview];
        }

        self.callView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, CGRectGetWidth(self.view.frame), CGRectGetHeight(self.view.frame))];
        self.callView.backgroundColor = [UIColor whiteColor];

        self.p2pRemoteView = extra[@"remote"];
        if(self.p2pRemoteView)
        {
            self.p2pRemoteView.delegate = self;
            UIView* remoteVideoView = self.p2pRemoteView.view;
            if(remoteVideoView)
            {
                [self.callView addSubview:remoteVideoView];
            }
        }
        
        ViitalkLocalVideoView* local = extra[@"local"];
        UIView* localVideoView = local.view;
        if(localVideoView)
        {
            localVideoView.frame = CGRectMake(CGRectGetWidth(self.view.frame) / 2 - 90, CGRectGetHeight(self.view.frame) - 60 - 320, 180, 320);
            [self.callView addSubview:localVideoView];
        }
        
        self.switchCameraButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [self.switchCameraButton addTarget:self action:@selector(OnSwitchCamera:) forControlEvents:UIControlEventTouchUpInside];
        self.switchCameraButton.frame = CGRectMake(6, CGRectGetHeight(self.callView.frame) - 46, 58, 36);
        [self.switchCameraButton setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
        self.switchCameraButton.titleLabel.font = [UIFont systemFontOfSize: 14.0];
        self.switchCameraButton.layer.borderWidth = .5;
        [self.switchCameraButton setTitle:@"Camera" forState:UIControlStateNormal];
        [self.callView addSubview:self.switchCameraButton];
        
        self.hangupButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [self.hangupButton addTarget:self action:@selector(OnHangup:) forControlEvents:UIControlEventTouchUpInside];
        self.hangupButton.frame = CGRectMake(CGRectGetMaxX(self.switchCameraButton.frame) + 12, CGRectGetHeight(self.callView.frame) - 46, 58, 36);
        [self.hangupButton setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
        self.hangupButton.titleLabel.font = [UIFont systemFontOfSize: 14.0];
        self.hangupButton.layer.borderWidth = .5;
        [self.hangupButton setTitle:@"Hang up" forState:UIControlStateNormal];
        [self.callView addSubview:self.hangupButton];
        
        self.speakerMuteButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [self.speakerMuteButton addTarget:self action:@selector(OnSpeakerMute:) forControlEvents:UIControlEventTouchUpInside];
        self.speakerMuteButton.frame = CGRectMake(CGRectGetMaxX(self.hangupButton.frame) + 12, CGRectGetHeight(self.callView.frame) - 46, 58, 36);
        [self.speakerMuteButton setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
        self.speakerMuteButton.titleLabel.font = [UIFont systemFontOfSize: 14.0];
        self.speakerMuteButton.layer.borderWidth = .5;
        [self.speakerMuteButton setTitle:@"Speaker" forState:UIControlStateNormal];
        [self.callView addSubview:self.speakerMuteButton];
        
        self.micMuteButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [self.micMuteButton addTarget:self action:@selector(OnMicMute:) forControlEvents:UIControlEventTouchUpInside];
        self.micMuteButton.frame = CGRectMake(CGRectGetMaxX(self.speakerMuteButton.frame) + 12, CGRectGetHeight(self.callView.frame) - 46, 40, 36);
        [self.micMuteButton setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
        self.micMuteButton.titleLabel.font = [UIFont systemFontOfSize: 14.0];
        self.micMuteButton.layer.borderWidth = .5;
        [self.micMuteButton setTitle:@"Mic" forState:UIControlStateNormal];
        [self.callView addSubview:self.micMuteButton];
        
        self.videoMuteButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [self.videoMuteButton addTarget:self action:@selector(OnVideoMute:) forControlEvents:UIControlEventTouchUpInside];
        self.videoMuteButton.frame = CGRectMake(CGRectGetMaxX(self.micMuteButton.frame) + 12, CGRectGetHeight(self.callView.frame) - 46, 44, 36);
        [self.videoMuteButton setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
        self.videoMuteButton.titleLabel.font = [UIFont systemFontOfSize: 14.0];
        self.videoMuteButton.layer.borderWidth = .5;
        [self.videoMuteButton setTitle:@"Video" forState:UIControlStateNormal];
        [self.callView addSubview:self.videoMuteButton];
        
        self.inviteButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [self.inviteButton addTarget:self action:@selector(OnInvite:) forControlEvents:UIControlEventTouchUpInside];
        self.inviteButton.frame = CGRectMake(CGRectGetMaxX(self.videoMuteButton.frame) + 12, CGRectGetHeight(self.callView.frame) - 46, 48, 36);
        [self.inviteButton setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
        self.inviteButton.titleLabel.font = [UIFont systemFontOfSize: 14.0];
        self.inviteButton.layer.borderWidth = .5;
        [self.inviteButton setTitle:@"Invite" forState:UIControlStateNormal];
        [self.callView addSubview:self.inviteButton];
        
        [self.view addSubview:self.callView];
    });
}

- (void)processJoinRoom:(NSString*)room withPassword:(NSString*)pwd andAVMode:(ViitalkCallMediaMode)mode
{
    [self.kit joinRoom:room password:pwd andAVMode:mode completionHandler:^(ViitalkRoomStatusCode status, NSDictionary * _Nullable extra) {
        if(status == VIITALK_ROOM_SUCCESS)
        {
            NSLog(@"加入房间成功");
            self.isConference = YES;
            [self processStartCallSuccess:extra];
        }
        else
        {
            if(status == VIITALK_ROOM_ERROR_JOIN)
            {
                NSLog(@"加入房间失败，其它原因");
            }
            else if(status == VIITALK_ROOM_ERROR_NOTEXIST)
            {
                NSLog(@"加入房间失败，房间不存在");
            }
            else if(status == VIITALK_ROOM_ERROR_PASSWORD)
            {
                NSLog(@"加入房间失败，密码错误");
            }
            else if(status == VIITALK_ROOM_ERROR_FULL)
            {
                NSLog(@"加入房间失败，房间人数已满");
            }
        }
    }];
}

- (void)processInvitedJoinRoom:(NSDictionary*)extra
{
    NSString* room = extra[@"room"];
    NSString* inviter = extra[@"inviter"];
    BOOL hasVideo = [extra[@"video"] boolValue];
    NSString* content = [NSString stringWithFormat:@"被%@邀请加入%@房间%@", inviter, hasVideo ? @"视频" : @"语音", room];
    dispatch_async(dispatch_get_main_queue(), ^{
        if(self.isCalling)
        {
            NSLog(@"正在与对方P2P通话，直接转会议模式，加入其房间就可以");
            [self processJoinRoom:room withPassword:nil andAVMode:hasVideo ? VIITALK_CALL_MEDIA_MODE_AV : VIITALK_CALL_MEDIA_MODE_AUDIO];
            
        }
        else
        {
            UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:@"会议邀请" message:content preferredStyle:UIAlertControllerStyleAlert];
            UIAlertAction *cancle = [UIAlertAction actionWithTitle:@"拒绝" style:UIAlertActionStyleCancel handler:^(UIAlertAction *action) {
              [self.kit refuseJoin:room];
            }];
            UIAlertAction *confirm = [UIAlertAction actionWithTitle:@"加入" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
                [self processJoinRoom:room withPassword:nil andAVMode:hasVideo ? VIITALK_CALL_MEDIA_MODE_AV : VIITALK_CALL_MEDIA_MODE_AUDIO];
            }];
            [alertVc addAction:cancle];
            [alertVc addAction:confirm];
            [self presentViewController:alertVc animated:YES completion:^{}];
        }
    });
}

- (void)processLeaveRoom
{
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.kit leaveRoom];
        [self.callView removeFromSuperview];
        self.callView = nil;
    });
}

- (void)resetRemoteVideoData
{
    NSMutableArray<NSString*>* peerNumbers = [NSMutableArray array];
    int maxPerPage = 4;
    for(int i = self.currentPage * maxPerPage, j = 0; j < maxPerPage && i < (int)self.peerNumbers.count; i++, j++)
    {
        [peerNumbers addObject:self.peerNumbers[i][@"peerNumber"]];
    }
    [self.kit wantVideoData:peerNumbers];
}

#pragma mark - ViitalkRemoteVideoViewDelegate

- (void)remoteVideoView:(ViitalkRemoteVideoView*)view didChangeVideoViewSize:(CGSize)size
{
    CGRect bounds = CGRectMake(CGRectGetMinX(view.view.frame), CGRectGetMinY(view.view.frame), CGRectGetWidth(view.view.frame), CGRectGetHeight(view.view.frame));
    if(view == self.p2pRemoteView)
    {
        // full screen
        bounds = CGRectMake(0, 0, CGRectGetWidth(self.view.frame), CGRectGetHeight(self.view.frame) - 50);
    }
    
    CGRect remoteVideoFrame = AVMakeRectWithAspectRatioInsideRect(size, bounds);
    CGFloat scale = 1;
    if (remoteVideoFrame.size.width > remoteVideoFrame.size.height) {
        // Scale by height.
        scale = bounds.size.height / remoteVideoFrame.size.height;
    } else {
        // Scale by width.
        scale = bounds.size.width / remoteVideoFrame.size.width;
    }
    remoteVideoFrame.size.height *= scale;
    remoteVideoFrame.size.width *= scale;
    view.view.frame = remoteVideoFrame;
    view.view.center = CGPointMake(CGRectGetMidX(bounds), CGRectGetMidY(bounds));
}

- (void)remoteVideoView:(ViitalkRemoteVideoView*)videoView didChangeVideoViewSourceNumber:(uint64_t)sourceNumber
{
    NSLog(@"+++++sourceNumberChange:%@", @(sourceNumber));
}

#pragma mark - ViitalkRtcEngineDelegate

- (BOOL)rtcEngine:(ViitalkRtcEngineKit * _Nonnull)engine didMediaConnectionState:(ViitalkConnectionStateCode)status withPeerNumber:(NSString * _Nullable)number
{
    if(status == VIITALK_CONNECTION_STATE_CONNECTED)
    {
        NSLog(@"与%@已成功建立数据连接通道", number);
    }
    else if(status == VIITALK_CONNECTION_STATE_DISCONNECTED)
    {
        NSLog(@"与%@的数据连接通道已断开", number);
    }
    return YES;
}

- (BOOL)rtcEngine:(ViitalkRtcEngineKit * _Nonnull)engine didAnswerCall:(NSString * _Nullable)number
{
    NSLog(@"%@已接接听电话", number);
    return YES;
}

- (BOOL)rtcEngine:(ViitalkRtcEngineKit * _Nonnull)engine didIncomingCall:(NSString * _Nullable)number hasVideo:(BOOL)video
{
    NSLog(@"%@来电话啦", number);
    NSString* msg = @"来语音电话啦";
    if(video)
    {
        msg = @"来视频电话啦";
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:number message:msg preferredStyle:UIAlertControllerStyleAlert];
            UIAlertAction *cancle = [UIAlertAction actionWithTitle:@"拒接" style:UIAlertActionStyleCancel handler:^(UIAlertAction *action) {
              [self.kit refuseCall];
            }];
            UIAlertAction *confirm = [UIAlertAction actionWithTitle:@"接听" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
                [self.kit answerCall:video ? VIITALK_CALL_MEDIA_MODE_AV : VIITALK_CALL_MEDIA_MODE_AUDIO completionHandler:^(ViitalkCallStatusCode status, NSDictionary * _Nullable extra) {
                   switch (status) {
                       case VIITALK_CALL_SUCCESS:
                           [self processStartCallSuccess:extra];
                           break;
                           
                       case VIITALK_CALL_ERROR_FLOW:
                           NSLog(@"流程出错，还未收到来电通知");
                           break;
                           
                       case VIITALK_CALL_ERROR_PARAM:
                           NSLog(@"参数设置出错");
                           break;
                           
                       case VIITALK_CALL_ERROR_OTHER:
                           NSLog(@"sdk内部错误");
                           break;
                           
                       default:
                           break;
                   }
               }];
            }];
            [alertVc addAction:cancle];
            [alertVc addAction:confirm];
        [self presentViewController:alertVc animated:YES completion:^{
        }];
    });
    return YES;
}

- (BOOL)rtcEngine:(ViitalkRtcEngineKit * _Nonnull)engine didHangupCall:(NSString * _Nullable)number
{
    NSLog(@"对方已经挂断电话");
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.callView removeFromSuperview];
        self.callView = nil;
        self.isCalling = NO;
    });
    return YES;
}

- (BOOL)rtcEngine:(ViitalkRtcEngineKit * _Nonnull)engine didMediaContentChange:(ViitalkMediaContentType)type direction:(ViitalkMediaContentDirection)dir operate:(ViitalkMediaContentOperator)ope
{
    NSLog(@"%@%@%@",
          (dir == VIITALK_MEDIA_CONTENT_DIR_SEND) ? @"对方" : @"双方",
          (ope == VIITALK_MEDIA_CONTENT_OPE_REMOVE) ? @"关闭" : @"打开",
          (type == VIITALK_MEDIA_CONTENT_TYPE_SPEAKER) ? @"扬声器" : ((type == VIITALK_MEDIA_CONTENT_TYPE_MIC) ? @"麦克风" : @"视频"));
    return YES;
}

- (BOOL)rtcEngine:(ViitalkRtcEngineKit * _Nonnull)engine didNewParticipant:(NSArray<NSDictionary*>* _Nullable)extra
{
    for(NSDictionary* participant in extra)
    {
        NSString* peerNumber = participant[@"peerNumber"];
        ViitalkRemoteVideoView* remoteView = participant[@"remoteView"];
        if(remoteView)
        {
            remoteView.delegate = self;
            UIView* remoteVideoView = remoteView.view;
            if(remoteVideoView)
            {
                CGFloat x = 0;
                CGFloat y = 0;
                if(self.remoteViews.count > 0)
                {
                    if((self.remoteViews.count % 2) == 0)
                    {
                        x = 0;
                        y = CGRectGetMaxY(self.remoteViews.lastObject.view.frame);
                    }
                    else
                    {
                        x = CGRectGetMaxX(self.remoteViews.lastObject.view.frame);
                        y = CGRectGetMinY(self.remoteViews.lastObject.view.frame);
                    }
                }
                remoteVideoView.frame = CGRectMake(x, y, CGRectGetWidth(self.view.frame) / 2, 120);
                [self.callView addSubview:remoteVideoView];
            }
            [self.remoteViews addObject:remoteView];
        }
        int idType = [participant[@"idType"] intValue];
        int joinIndex = [participant[@"joinIndex"] intValue];
        BOOL isCloseVideo = [participant[@"isCloseVideo"] boolValue];
        BOOL isCloseMic = [participant[@"isCloseMic"] boolValue];
        BOOL isCloseSpeaker = [participant[@"isCloseSpeaker"] boolValue];
        [self.peerNumbers addObject:@{@"peerNumber": peerNumber,
                                      @"joinIndex": @(joinIndex),
                                      @"isCloseVideo": @(isCloseVideo),
                                      @"isCloseMic": @(isCloseMic),
                                      @"isCloseSpeaker": @(isCloseSpeaker)}];

        NSString* mode = @"";
        if(idType == VIITALK_ROOM_IDENTIFY_TYPE_HOST)
        {
            mode = @"房主";
        }
        else if(idType == VIITALK_ROOM_IDENTIFY_TYPE_PUBLISHER)
        {
            mode = @"参会者";
        }
        else if(idType == VIITALK_ROOM_IDENTIFY_TYPE_SUBSCRIBER)
        {
            mode = @"观众";
        }
        NSLog(@"%@加入房间，模式:%@ 序号:%d 视频%@ 麦克风%@ 扬声器%@", peerNumber, mode, joinIndex, isCloseVideo ? @"关闭" : @"打开", isCloseMic ? @"关闭" : @"打开", isCloseSpeaker ? @"关闭" : @"打开");
    }
    [self.peerNumbers sortedArrayUsingComparator:^NSComparisonResult(id  _Nonnull obj1, id  _Nonnull obj2) {
        NSNumber *number1 = obj1[@"joinIndex"];
        NSNumber *number2 = obj2[@"joinIndex"];
        return [number1 compare:number2];
    }];
    [self resetRemoteVideoData];
    return YES;
}

- (BOOL)rtcEngine:(ViitalkRtcEngineKit * _Nonnull)engine didRemoveParticipant:(NSArray<NSString*>* _Nullable)peerNumbers
{
    for(NSString* peerNumber in peerNumbers)
    {
        for(NSDictionary* p in self.peerNumbers)
        {
            if([peerNumber isEqualToString:p[@"peerNumber"]])
            {
                [self.peerNumbers removeObject:p];
                break;
            }
        }
        NSLog(@"%@离开房间", peerNumber);
    }
    [self resetRemoteVideoData];
    return YES;
}

- (BOOL)rtcEngine:(ViitalkRtcEngineKit * _Nonnull)engine didParticipantStatusChange:(NSArray<NSDictionary*>* _Nullable)extra
{
    for(NSDictionary* participant in extra)
    {
        NSString* peerNumber = participant[@"peerNumber"];
        int idType = [participant[@"idType"] intValue];
        int joinIndex = [participant[@"joinIndex"] intValue];
        BOOL isCloseVideo = [participant[@"isCloseVideo"] boolValue];
        BOOL isCloseMic = [participant[@"isCloseMic"] boolValue];
        BOOL isCloseSpeaker = [participant[@"isCloseSpeaker"] boolValue];

        NSString* mode = @"";
        if(idType == VIITALK_ROOM_IDENTIFY_TYPE_HOST)
        {
            mode = @"房主";
        }
        else if(idType == VIITALK_ROOM_IDENTIFY_TYPE_PUBLISHER)
        {
            mode = @"参会者";
        }
        else if(idType == VIITALK_ROOM_IDENTIFY_TYPE_SUBSCRIBER)
        {
            mode = @"观众";
        }
        NSLog(@"%@状态改变，模式:%@ 序号:%d 视频%@ 麦克风%@ 扬声器%@", peerNumber, mode, joinIndex, isCloseVideo ? @"关闭" : @"打开", isCloseMic ? @"关闭" : @"打开", isCloseSpeaker ? @"关闭" : @"打开");
    }
    return YES;
}

- (BOOL)rtcEngine:(ViitalkRtcEngineKit * _Nonnull)engine didRoomStatusChange:(NSString * _Nullable)host maxWindow:(NSString * _Nullable)user windowMode:(NSString * _Nullable)mode
{
    if(host)
    {
        NSLog(@"房主改为:%@", host);
    }
    if(user)
    {
        NSLog(@"最大窗口的用户改为:%@", user);
    }
    if(mode)
    {
        NSLog(@"窗口模式改为:%@", mode);
    }
    return YES;
}

- (BOOL)rtcEngine:(ViitalkRtcEngineKit * _Nonnull)engine didRecvRoomCommand:(ViitalkRoomCommandCode)cmd extra:(NSDictionary * _Nullable)extra
{
    switch (cmd) {
        case VIITALK_ROOM_CMD_INVITED:
            [self processInvitedJoinRoom:extra];
            break;
        
        case VIITALK_ROOM_CMD_ROOM_CLOSED:
            NSLog(@"房间已经被解散");
            [self processLeaveRoom];
            break;

        case VIITALK_ROOM_CMD_LEAVE_ROOM:
            NSLog(@"被人要求离开房间");
            [self processLeaveRoom];
            break;
            
        case VIITALK_ROOM_CMD_OPEN_VIDEO:
            NSLog(@"被人要求打开视频");
            _hasMuteVideo = NO;
            self.kit.muteVideo = NO;
            break;

        case VIITALK_ROOM_CMD_CLOSE_VIDEO:
            NSLog(@"被人要求关闭视频");
            _hasMuteVideo = YES;
            self.kit.muteVideo = YES;
            break;

        case VIITALK_ROOM_CMD_OPEN_MIC:
            NSLog(@"被人要求打开麦克风");
            _hasMuteMic = NO;
            self.kit.muteMic = NO;
            break;

        case VIITALK_ROOM_CMD_CLOSE_MIC:
            NSLog(@"被人要求关闭麦克风");
            _hasMuteMic = YES;
            self.kit.muteMic = YES;
            break;

        case VIITALK_ROOM_CMD_OPEN_SPEAKER:
            NSLog(@"被人要求打开扬声器");
            _hasMuteSpeaker = NO;
            self.kit.muteSpeaker = NO;
            break;

        case VIITALK_ROOM_CMD_CLOSE_SPEAKER:
            NSLog(@"被人要求关闭扬声器");
            _hasMuteSpeaker = YES;
            self.kit.muteSpeaker = YES;
            break;
            
        default:
            break;
    }
    return YES;
}

@end
