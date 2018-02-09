//
//  GoTennaSDK.h
//  goTenna SDK
//

#import <Foundation/Foundation.h>
#import "NSNumber+Utilities.h"
#import "GTDataTypes.h"
#import "GTBaseMessageData.h"
#import "GTMessageDataProtocol.h"
#import "GTPairingManager.h"
#import "GTCommand.h"
#import "GTCommandCenter.h"
#import "GTGroupCreationMessageData.h"
#import "GTLocationMessageData.h"
#import "GTResponse.h"
#import "GTMessageData.h"

@interface GoTenna : NSObject

/**
 Set goTenna SDK token
 
 @param token SDK token
 */
+ (void)setApplicationToken:(NSString *)token;

/**
 Get goTenna SDK token data
 
 @return App token used to authenticate SDK
 */
+ (NSData *)applicationToken;

/**
 Token verified
 
 @return True if the SDK token is valid
 */
+ (BOOL)tokenIsVerified;

/**
 Super token
 
 @return True if the token is super
 */
+ (BOOL)hasSuperToken;

@end
