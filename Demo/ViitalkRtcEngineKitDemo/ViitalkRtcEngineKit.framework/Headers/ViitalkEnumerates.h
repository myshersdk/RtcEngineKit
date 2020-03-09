//
//  ViitalkEnumerates.h
//  ViitalkRtcEngineKit
//
//  Created by mysher on 2020/2/20.
//  Copyright © 2020 mysher. All rights reserved.
//

#import <Foundation/Foundation.h>

/** log in state error codes
 */
typedef NS_ENUM(NSInteger, ViitalkLoginStatusCode) {
    /** success */
    VIITALK_LOGIN_SUCCESS = 0,
    /** network error */
    VIITALK_LOGIN_ERROR_NETWORK = 1,
    /** both accounts log in at the same time */
    VIITALK_LOGIN_ERROR_CONFLICT = 2,
    /** password mistake */
    VIITALK_LOGIN_ERROR_UNAUTHORIZED = 3,
    /** other errors */
    VIITALK_LOGIN_ERROR_OTHER = 100,
};

/** call state error codes
 */
typedef NS_ENUM(NSInteger, ViitalkCallStatusCode) {
    /** success */
    VIITALK_CALL_SUCCESS = 0,
    /** the user has joined a room */
    VIITALK_CALL_ERROR_INROOM = 1,
    /** calling */
    VIITALK_CALL_ERROR_CALLING = 2,
    /** off line */
    VIITALK_CALL_ERROR_OFFLINE = 3,
    /** upgrading */
    VIITALK_CALL_ERROR_UPGRADE = 4,
    /** the user is not exist */
    VIITALK_CALL_ERROR_NOTEXIST = 5,
    /** the user is forbiddened */
    VIITALK_CALL_ERROR_FORBIDDEN = 6,
    /** the user is  logout */
    VIITALK_CALL_ERROR_LOGOUT = 7,
    /** call flow is wrong */
    VIITALK_CALL_ERROR_FLOW = 8,
    /** error params */
    VIITALK_CALL_ERROR_PARAM = 9,
    /** the other errors */
    VIITALK_CALL_ERROR_OTHER = 100,
};

/** the audio and video mode when join room
 */
typedef NS_ENUM(NSInteger, ViitalkCallMediaMode) {
    /** audio and video */
    VIITALK_CALL_MEDIA_MODE_AV = 0,
    /** audio only */
    VIITALK_CALL_MEDIA_MODE_AUDIO = 1,
    /** receive only, no send */
    VIITALK_CALL_MEDIA_MODE_NOPUBLISH = 2,
    /** mute the mic first off */
    VIITALK_CALL_MEDIA_MODE_AV_MUTE_MIC = 3,
};

/** the media connection state code
 */
typedef NS_ENUM(NSInteger, ViitalkConnectionStateCode) {
    /** connected */
    VIITALK_CONNECTION_STATE_CONNECTED = 0,
    /** disconnected */
    VIITALK_CONNECTION_STATE_DISCONNECTED = 1,
};

typedef NS_ENUM(NSInteger, ViitalkMediaContentType) {
    /** mic  */
    VIITALK_MEDIA_CONTENT_TYPE_MIC = 0,
    /** video  */
    VIITALK_MEDIA_CONTENT_TYPE_VIDEO = 1,
    /** speaker  */
    VIITALK_MEDIA_CONTENT_TYPE_SPEAKER = 2,
};

typedef NS_ENUM(NSInteger, ViitalkMediaContentDirection) {
    /** send  */
    VIITALK_MEDIA_CONTENT_DIR_SEND = 0,
    /** send and recv  */
    VIITALK_MEDIA_CONTENT_DIR_BOTH = 1,
};

typedef NS_ENUM(NSInteger, ViitalkMediaContentOperator) {
    /** remove  */
    VIITALK_MEDIA_CONTENT_OPE_REMOVE = 0,
    /** recover  */
    VIITALK_MEDIA_CONTENT_OPE_RECOVER = 1,
};

/** create and join room error codes
 */
typedef NS_ENUM(NSInteger, ViitalkRoomStatusCode) {
    /** success */
    VIITALK_ROOM_SUCCESS = 0,
    /** room has exist */
    VIITALK_ROOM_ERROR_EXIST = 1,
    /** create room error */
    VIITALK_ROOM_ERROR_CREATE = 2,
    /** join room error */
    VIITALK_ROOM_ERROR_JOIN = 50,
    /** join not exist room error */
    VIITALK_ROOM_ERROR_NOTEXIST = 51,
    /** password is wrong */
    VIITALK_ROOM_ERROR_PASSWORD = 52,
    /** the room is full */
    VIITALK_ROOM_ERROR_FULL = 53,
    /** the other errors */
    VIITALK_ROOM_ERROR_OTHER = 100,
};

typedef NS_ENUM(NSInteger, ViitalkRoomIdentifyType) {
    /** create the room  */
    VIITALK_ROOM_IDENTIFY_TYPE_HOST = 0,
    /** send and recv  */
    VIITALK_ROOM_IDENTIFY_TYPE_PUBLISHER = 1,
    /** recv only  */
    VIITALK_ROOM_IDENTIFY_TYPE_SUBSCRIBER = 2,
};

/** command code in room
 */
typedef NS_ENUM(NSInteger, ViitalkRoomCommandCode) {
    /** invited by other */
    VIITALK_ROOM_CMD_INVITED = 0,
    /** the room has closed */
    VIITALK_ROOM_CMD_ROOM_CLOSED = 1,
    /** should leave the room */
    VIITALK_ROOM_CMD_LEAVE_ROOM = 2,
    /** open the video */
    VIITALK_ROOM_CMD_OPEN_VIDEO = 3,
    /** close the video */
    VIITALK_ROOM_CMD_CLOSE_VIDEO = 4,
    /** open the mic */
    VIITALK_ROOM_CMD_OPEN_MIC = 5,
    /** close the mic */
    VIITALK_ROOM_CMD_CLOSE_MIC = 6,
    /** open the speaker */
    VIITALK_ROOM_CMD_OPEN_SPEAKER = 7,
    /** close the speaker */
    VIITALK_ROOM_CMD_CLOSE_SPEAKER = 8,
    /** change the emcee */
    VIITALK_ROOM_CMD_TRANSFER = 9,
};
