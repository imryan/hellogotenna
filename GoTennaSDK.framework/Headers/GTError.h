//
// Created by Julietta Yaunches on 12/2/14.
// goTenna SDK
//

#import <Foundation/Foundation.h>

@interface GTError : NSObject

+ (NSError *)invalidAppToken;
+ (NSError *)invalidInputMessageData;
+ (NSError *)invalidIncomingMessageData;
+ (NSError *)goTennaFailedToProcessCommand;
+ (NSError *)hasNotSetupGotenna;
+ (NSError *)dataLengthExceedsLimits;
+ (NSError *)dataRateLimitExceeded;
+ (NSError *)sendingMessageToReservedGID;
+ (NSError *)groupSecretNotFound;
+ (NSError *)goTennaTimedOutWithCommand;
+ (NSError *)notSuperSDKUser;

@end
