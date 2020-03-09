//
//  ViewController.m
//  ViitalkRtcEngineKitDemo
//
//  Created by mysher on 2020/2/19.
//  Copyright © 2020 mysher. All rights reserved.
//

#import "ViewController.h"
#import "CallingViewController.h"
#import "ViitalkRtcEngineKit/ViitalkRtcEngineKit.h"

@interface ViewController () <ViitalkRtcEngineDelegate>

@property (nonatomic, strong) ViitalkRtcEngineKit *kit;

@property (nonatomic, strong) UILabel* text;
@property (nonatomic, strong) UILabel* userLabel;
@property (nonatomic, strong) UILabel* pwdLabel;
@property (nonatomic, strong) UITextField* userTextField;
@property (nonatomic, strong) UITextField* pwdTextField;
@property (nonatomic, strong) UIButton* loginButton;

@end

@implementation ViewController
{
    NSString *_user;
    NSString *_pwd;
}

@synthesize kit = _kit;
@synthesize text = _text;
@synthesize userLabel = _userLabel;
@synthesize pwdLabel = _pwdLabel;
@synthesize userTextField = _userTextField;
@synthesize pwdTextField = _pwdTextField;
@synthesize loginButton = _loginButton;

- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    self.navigationController.navigationBarHidden = YES;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self.view addSubview:self.text];
    [self.view addSubview:self.userLabel];
    [self.view addSubview:self.pwdLabel];
    [self.view addSubview:self.userTextField];
    [self.view addSubview:self.pwdTextField];
    [self.view addSubview:self.loginButton];
    
    // Give rounded corners and a light gray border.
    self.view.layer.borderWidth = 1;
    self.view.layer.borderColor = [[UIColor lightGrayColor] CGColor];
    self.view.layer.cornerRadius = 2;
    
    _kit = [ViitalkRtcEngineKit sharedEngineWithDelegate:self];
}

#pragma mark - ViitalkRtcEngineDelegate

- (BOOL)rtcEngine:(ViitalkRtcEngineKit * _Nonnull)engine didLoginStatus:(ViitalkLoginStatusCode)status
{
    dispatch_async(dispatch_get_main_queue(), ^{
        if(status == VIITALK_LOGIN_SUCCESS)
        {
            CallingViewController* call = [[CallingViewController alloc] init];
            [self.navigationController pushViewController:call animated:YES];
        }
        else if(status == VIITALK_LOGIN_ERROR_NETWORK)
        {
            self.text.text = @"没有网络";
        }
        else if(status == VIITALK_LOGIN_ERROR_CONFLICT)
        {
            self.text.text = @"异地登陆";
        }
        else if(status == VIITALK_LOGIN_ERROR_UNAUTHORIZED)
        {
            self.text.text = @"密码错误";
        }
        else
        {
            self.text.text = @"其它错误";
        }
    });
    return true;
}

#pragma mark - get

- (UILabel*)text {
    if(!_text) {
        _text = [[UILabel alloc] initWithFrame:CGRectMake(10, 20, CGRectGetMaxX(self.view.frame) - 20, 20)];
        _text.textColor = [UIColor redColor];
        _text.font = [UIFont systemFontOfSize:12];
        _text.textAlignment = NSTextAlignmentCenter;
    }
    return _text;
}

- (UILabel*)userLabel {
    if(!_userLabel) {
        _userLabel = [[UILabel alloc] initWithFrame:CGRectMake(20, 100, 80, 28)];
        _userLabel.text = @"用户名:";
    }
    return _userLabel;
}

- (UILabel*)pwdLabel {
    if(!_pwdLabel) {
        _pwdLabel = [[UILabel alloc] initWithFrame:CGRectMake(20, CGRectGetMaxY(self.userLabel.frame) + 20, 80, 28)];
        _pwdLabel.text = @"密码:";
    }
    return _pwdLabel;
}

- (UITextField*)userTextField {
    if(!_userTextField) {
        _userTextField = [[UITextField alloc] initWithFrame:CGRectMake(CGRectGetMaxX(self.userLabel.frame), 100, 200, 28)];
        _userTextField.backgroundColor = [UIColor lightGrayColor];
        _userTextField.keyboardType = UIKeyboardTypeNumberPad;
        _userTextField.text = @"13829760926";
        // _userTextField.text = @"18670046361";
        //c_userTextField.text = @"7000000377";
    }
    return _userTextField;
}

- (UITextField*)pwdTextField {
    if(!_pwdTextField) {
        _pwdTextField = [[UITextField alloc] initWithFrame:CGRectMake(CGRectGetMaxX(self.pwdLabel.frame), CGRectGetMaxY(self.userLabel.frame) + 20, 200, 28)];
        _pwdTextField.backgroundColor = [UIColor lightGrayColor];
        _pwdTextField.keyboardType = UIKeyboardTypeNumberPad;
        _pwdTextField.text = @"123456";
    }
    return _pwdTextField;
}

- (UIButton*)loginButton {
    if(!_loginButton) {
        _loginButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [_loginButton addTarget:self action:@selector(loginButtonEvent:) forControlEvents:UIControlEventTouchUpInside];
        _loginButton.frame = CGRectMake(CGRectGetWidth(self.view.frame) / 2 - 80, CGRectGetMaxY(self.pwdLabel.frame) + 20, 160, 45);
        [_loginButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
        _loginButton.layer.borderColor = [UIColor blackColor].CGColor;
        _loginButton.layer.borderWidth = .5;
        [_loginButton setTitle:@"登录" forState:UIControlStateNormal];
    }
    return _loginButton;
}

- (void)loginButtonEvent:(UIButton*)sender {
    _user = _userTextField.text;
    _pwd = _pwdTextField.text;
    NSUInteger user_len = [_user length];
    NSUInteger pwd_len = [_pwd length];
    
    if(user_len > 0 && pwd_len > 0){
        [_kit login:_user password:_pwd server:@"test.viitalk.com"];
    }
    else {
        self.text.text = @"用户名或密码为空";
    }
}


@end
