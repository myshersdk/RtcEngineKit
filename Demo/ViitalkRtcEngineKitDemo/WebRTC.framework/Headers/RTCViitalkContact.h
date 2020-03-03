//
//  RTCViitalkContact.h
//  sources
//o//  Created by mandy on 2019/6/24.
//

#import <Foundation/Foundation.h>
#import "RTCMacros.h"


NS_ASSUME_NONNULL_BEGIN

RTC_EXPORT
@interface RTCViitalkContact : NSObject

- (instancetype)initContact:(NSString *)contactName
              contactNumber:(NSString *)contactNumber
          contactAutoAccept:(BOOL)contactAutoAccept;

//name
@property(nonatomic, readonly) NSString *name;
//mysher number
@property(nonatomic, readonly) NSString *number;
//auto accept
@property(nonatomic, readonly) BOOL autoAccept;

@end


NS_ASSUME_NONNULL_END
