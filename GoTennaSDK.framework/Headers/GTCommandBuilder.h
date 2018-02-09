//
// Created by Julietta Yaunches on 11/4/14.
// goTenna SDK
//

#import <Foundation/Foundation.h>
#import "RegionBound.h"

@protocol GTMessageDataProtocol;

@class GTCommand;
@class GTResponse;
@class SystemInfoResponseData;
@class GTFirmwareVersion;
@class GTGid;
@class GTGroupCreationMessageData;
@class GTMessageData;
@class GTError;
@class FrequencyMode;

@interface GTCommandBuilder : NSObject

- (GTCommand *)buildResetGotenna;
- (GTCommand *)buildDeleteLastMessage;
- (GTCommand *)buildSetPublicKey:(NSData *)publicKey;
- (GTCommand *)buildSetGID:(GTGid *)number onError:(void (^)(NSError *))error;

- (GTCommand *)buildSendMessageCommand:(NSData *)outgoingData
                                 toGID:(GTGid *)addresseeGID
                            onResponse:(void (^)(GTResponse *))onResponse
                               onError:(void (^)(NSError *))onError
                           willEncrypt:(BOOL)willEncrypt;

- (GTCommand *)buildSendMessageCommand:(NSData *)outgoingData
                                 toGID:(GTGid *)addresseeGID
                            onResponse:(void (^)(GTResponse *))onResponse
                               onError:(void (^)(NSError *))onError
                           willEncrypt:(BOOL)willEncrypt
                           maxHopCount:(NSUInteger)maxHopCount
           shouldNotResendWithMoreHops:(BOOL)shouldNotResendWithMoreHops
                              resendID:(int)resendId;

- (GTCommand *)buildGetMessageWithOnSuccess:(void (^)(GTMessageData *))onIncomingMessage
                             onGroupCreated:(void (^)(GTGroupCreationMessageData *))onGroupAdded
                 onSuccessLastMessageDelete:(void (^)())lastMessageDelete;

- (GTCommand *)buildEchoCommandOnResponse:(void (^)(GTResponse *))onResponse onError:(void (^)(NSError *))error;
- (GTCommand *)buildDisconnectGotenna;
- (GTCommand *)buildDeleteGID:(GTGid *)number onError:(void (^)(NSError *))error;
- (GTCommand *)buildGetSystemInfoOnError:(void (^)(NSError *))pFunction;

- (GTCommand *)buildSetGeoRegion:(RegionID)region onResponse:(void (^)(GTResponse *response))onResponse onError:(void (^)(NSError *))onError;
- (GTCommand *)buildGetGeoRegionOnResponse:(void (^)(GTResponse *response))onResponse onError:(void (^)(NSError *))onError;

// Update firmware commands
- (GTCommand *)buildInitiateFirmware:(int)numCommands totalNumOfBytesSending:(int)numBytes;
- (GTCommand *)buildWriteFirmware:(NSData *)data;
- (GTCommand *)buildAbortFirmwareUpdate:(GTFirmwareVersion *)version;
- (GTCommand *)buildFinalizeFirmwareUpdateForVersion:(GTFirmwareVersion *)version;

- (GTCommand *)buildAntennaSweep:(BOOL)on;
- (GTCommand *)buildFrequencyMode:(FrequencyMode *)mode;
- (GTCommand *)buildHardwareTransmit;
- (GTCommand *)buildGetBinaryLog;
- (GTCommand *)buildDeleteBinaryLog;
- (GTCommand *)buildBERTestWithData:(NSData*)berData;
- (GTCommand *)buildStoreDateTime:(NSString *)emergencyMessage;
- (GTCommand *)buildPowerSavingTransmit:(BOOL)on;
- (GTCommand *)buildHardReset;
- (GTCommand *)buildActivateEmergencyBeaconCommand:(BOOL)isActive onResponse:(void (^)(GTResponse *response))onResponse onError:(void (^)(NSError *))onError;
- (GTCommand *)buildGetEmergencyBeaconStatusOnResponse:(void (^)(GTResponse *response))onResponse onError:(void (^)(NSError *))onError;

@end
