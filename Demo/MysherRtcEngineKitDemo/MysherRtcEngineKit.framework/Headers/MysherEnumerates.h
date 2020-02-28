//
//  MysherEnumerates.h
//  MysherRtcEngineKit
//
//  Created by mysher on 2020/2/20.
//  Copyright © 2020 mysher. All rights reserved.
//

#import <Foundation/Foundation.h>

/** log in state error codes
 */
typedef NS_ENUM(NSInteger, MysherLoginStatusCode) {
    /** success */
    MYSHER_LOGIN_SUCCESS = 0,
    /** network error */
    MYSHER_LOGIN_ERROR_NETWORK = 1,
    /** both accounts log in at the same time */
    MYSHER_LOGIN_ERROR_CONFLICT = 2,
    /** password mistake */
    MYSHER_LOGIN_ERROR_UNAUTHORIZED = 3,
    /** other errors */
    MYSHER_LOGIN_ERROR_OTHER = 100,
};

/** call state error codes
 */
typedef NS_ENUM(NSInteger, MysherCallStatusCode) {
    /** success */
    MYSHER_CALL_SUCCESS = 0,
    /** the user has joined a room */
    MYSHER_CALL_ERROR_INROOM = 1,
    /** calling */
    MYSHER_CALL_ERROR_CALLING = 2,
    /** off line */
    MYSHER_CALL_ERROR_OFFLINE = 3,
    /** upgrading */
    MYSHER_CALL_ERROR_UPGRADE = 4,
    /** the user is not exist */
    MYSHER_CALL_ERROR_NOTEXIST = 5,
    /** the user is forbiddened */
    MYSHER_CALL_ERROR_FORBIDDEN = 6,
    /** the user is  logout */
    MYSHER_CALL_ERROR_LOGOUT = 7,
    /** call flow is wrong */
    MYSHER_CALL_ERROR_FLOW = 8,
    /** error params */
    MYSHER_CALL_ERROR_PARAM = 9,
    /** the other errors */
    MYSHER_CALL_ERROR_OTHER = 100,
};

/** the audio and video mode when join room
 */
typedef NS_ENUM(NSInteger, MysherCallMediaMode) {
    /** audio and video */
    MYSHER_CALL_MEDIA_MODE_AV = 0,
    /** audio only */
    MYSHER_CALL_MEDIA_MODE_AUDIO = 1,
    /** receive only, no send */
    MYSHER_CALL_MEDIA_MODE_NOPUBLISH = 1,
};

typedef NS_ENUM(NSInteger, MysherMediaContentType) {
    /** mic  */
    MYSHER_MEDIA_CONTENT_TYPE_MIC = 0,
    /** video  */
    MYSHER_MEDIA_CONTENT_TYPE_VIDEO = 1,
    /** speaker  */
    MYSHER_MEDIA_CONTENT_TYPE_SPEAKER = 2,
};

typedef NS_ENUM(NSInteger, MysherMediaContentDirection) {
    /** send  */
    MYSHER_MEDIA_CONTENT_DIR_SEND = 0,
    /** send and recv  */
    MYSHER_MEDIA_CONTENT_DIR_BOTH = 1,
};

typedef NS_ENUM(NSInteger, MysherMediaContentOperator) {
    /** remove  */
    MYSHER_MEDIA_CONTENT_OPE_REMOVE = 0,
    /** recover  */
    MYSHER_MEDIA_CONTENT_OPE_RECOVER = 1,
};

/** create and join room error codes
 */
typedef NS_ENUM(NSInteger, MysherRoomStatusCode) {
    /** success */
    MYSHER_ROOM_SUCCESS = 0,
    /** room has exist */
    MYSHER_ROOM_ERROR_EXIST = 1,
    /** create room error */
    MYSHER_ROOM_ERROR_CREATE = 2,
    /** join room error */
    MYSHER_ROOM_ERROR_JOIN = 3,
    /** join not exist room error */
    MYSHER_ROOM_ERROR_NOTEXIST = 4,
    /** password is wrong */
    MYSHER_ROOM_ERROR_PASSWORD = 5,
    /** the other errors */
    MYSHER_ROOM_ERROR_OTHER = 100,
};

typedef NS_ENUM(NSInteger, MysherRoomIdentifyType) {
    /** create the room  */
    MYSHER_ROOM_IDENTIFY_TYPE_HOST = 0,
    /** send and recv  */
    MYSHER_ROOM_IDENTIFY_TYPE_PUBLISHER = 1,
    /** recv only  */
    MYSHER_ROOM_IDENTIFY_TYPE_SUBSCRIBER = 2,
};

/** command code in room
 */
typedef NS_ENUM(NSInteger, MysherRoomCommandCode) {
    /** invited by other */
    MYSHER_ROOM_CMD_INVITED = 0,
    /** the room has closed */
    MYSHER_ROOM_CMD_ROOM_CLOSED = 1,
    /** should leave the room */
    MYSHER_ROOM_CMD_LEAVE_ROOM = 2,
    /** open the video */
    MYSHER_ROOM_CMD_OPEN_VIDEO = 3,
    /** close the video */
    MYSHER_ROOM_CMD_CLOSE_VIDEO = 4,
    /** open the mic */
    MYSHER_ROOM_CMD_OPEN_MIC = 5,
    /** close the mic */
    MYSHER_ROOM_CMD_CLOSE_MIC = 6,
    /** open the speaker */
    MYSHER_ROOM_CMD_OPEN_SPEAKER = 7,
    /** close the speaker */
    MYSHER_ROOM_CMD_CLOSE_SPEAKER = 8,
};
