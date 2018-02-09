//
// Created by Julietta Yaunches on 21/10/2014.
// goTenna SDK
//

#import <Foundation/Foundation.h>

@interface GTConfig : NSObject

+ (NSString *)retrieveCurrentVersion;
+ (NSString *)retrieveVersionDescription;
+ (NSString *)forgetThisDeviceKey;

+ (NSInteger)maxGIDlength;
+ (NSInteger)maxNameLength;
+ (NSInteger)maxGroupMembers;
+ (NSInteger)minTLVlength;
+ (NSInteger)minHopCount;
+ (NSInteger)maxHopCount;
+ (NSInteger)meshMessageTimeoutForHopCount:(NSUInteger)hopCount packetCount:(NSUInteger)packetCount;
+ (NSInteger)reconnectionScanTimeout;
+ (NSInteger)initialConnectionScanTimeout;
+ (NSUInteger)privateGIDByteLength;
+ (NSUInteger)broadcastGIDByteLength;
+ (NSInteger)maxDataPayloadLength;
+ (NSInteger)firmwareUpdateCommandTimeoutAmount;
+ (NSTimeInterval)finalizeFirmwareCommandTimeout;
+ (NSInteger)normalCommandTimeoutAmount;
+ (NSInteger)resetCommandTimeoutAmount;
+ (NSInteger)packetDataPayloadLimit;
+ (NSInteger)systemInfoQueryInterval;
+ (NSInteger)sendMessageTimeout;

+ (BOOL)isRSSILoggingOn;
+ (BOOL)shouldWriteLocationToFieldTestLog;
+ (BOOL)shouldLogPackets;
+ (BOOL)shouldNotifyAnalyticsEvents;
+ (BOOL)connectionNotRequired;
+ (BOOL)connectionRetryEnabled;
+ (BOOL)firmwareUpdateinEnabled;
+ (BOOL)shouldAllowChatOneToOneVisualQueue;

+ (NSBundle *)configBundle;

@end
