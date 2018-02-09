//
// Created by Julietta Yaunches on 11/18/14.
// goTenna SDK
//

#import <Foundation/Foundation.h>

typedef enum {
    NormalMessage,
    LocationRequestMessage,
    LogOnMessage,
    PingMessage,
    NewPublicKey,
    TipMessage,
    EmergencyLocationFirmwareTemporary,
    LocationTetheringTip,
} GTMessageType;

typedef enum {
    MessageOut,
    MessageReceived,
    MessageNotReceived,
    MessageReceivedMesh,
    MessageReceivedMeshLoading,
    MessageNotReceivedTemperatureRange,
    MessageNotReceivedRSSICrossed,
    MessageNotReceivedTimeout,
} GTOutgoingMessageStatus;

typedef enum {
    GTBatteryEmpty,
    GTBatteryFull,
    GTBatteryThreeFourths,
    GTBatteryOneHalf,
    GTBatteryOneFourth
} GTBatteryStatus;

typedef enum {
    OneToOneGID,
    GroupGID,
    ShoutGID,
    EmergencyGID
} GTGIDType;

typedef enum {
    GTResponsePositive,
    GTResponseNegative,
    GTResponseError
} GTCommandResponseType;

@interface GTDataTypes : NSObject

+ (NSData *)getDataForGIDType:(GTGIDType)type;
+ (GTGIDType)getGIDTypeFromData:(NSData *)data;

@end
