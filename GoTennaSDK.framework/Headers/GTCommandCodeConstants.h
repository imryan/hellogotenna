//
//  Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *const kMessageTypeTextOnly;
extern NSString *const kMessageTypeTextAndLocation;
extern NSString *const kMessageTypeLocationOnly;
extern NSString *const kMessageTypeLocationRequestOnly;
extern NSString *const kMessageTypeLocationRequestAndText;
extern NSString *const kMessageTypeSetGroupGID;
extern NSString *const kMessageTypeLogOnTextOnly;
extern NSString *const kMessageTypePingTextOnly;
extern NSString *const kMessageTypeFirmwarePublicKeyResponse;
extern NSString *const kMessageTypeUserPublicKeyResponse;
extern NSString *const kMessageTypePublicKeyRequest;
extern NSString *const kMessageTypeMeshPublicKeyRequest;
extern NSString *const kMessageTypeMeshPublicKeyResponse;

extern const char *gtSetGIDCommandCode;
extern const char *gtSetGIDResponseCode;
extern const char *gtSetGIDFailureCode;

extern const char *gtResetGotennaCommandCode;
extern const char *gtResetGotennaResponseCode;
extern const char *gtResetGotennaFailureCode;

extern const char *gtSetPublicKeyCommandCode;
extern const char *gtSetPublicKeyResponseCode;
extern const char *gtSetPublicKeyFailureCode;

extern const char *gtDeleteLastMessageCommandCode;
extern const char *gtDeleteLastMessageResponseCode;
extern const char *gtDeleteLastMessageFailureCode;

extern const char *gtGetMessageCommandCode;
extern const char *gtGetMessageResponseCode;
extern const char *gtGetMessageFailureCode;

extern const char *gtSendMessageCommandCode;
extern const char *gtSendMessageResponseCode;
extern const char *gtSendMessageFailureCode;

extern const char *gtGetSystemInfoCommandCode;
extern const char *gtGetSystemInfoResponseCode;
extern const char *gtGetSystemInfoFailureCode;

extern const char *gtEchoCommandCode;
extern const char *gtEchoResponseCode;
extern const char *gtEchoFailureCode;

extern const char *gtDisconnectGotennaCommandCode;
extern const char *gtDisconnectGotennaResponseCode;
extern const char *gtDisconnectGotennaFailureCode;

extern const char *gtDeleteGIDCommandCode;
extern const char *gtDeleteGIDResponseCode;
extern const char *gtDeleteGIDFailureCode;

extern const char *gtInitiateNewFirmwareWriteCommandCode;
extern const char *gtInitiateNewFirmwareWriteResponseCode;
extern const char *gtInitiateNewFirmwareWriteFailureCode;

extern const char *gtWriteFirmwareDataCommandCode;
extern const char *gtWriteFirmwareDataResponseCode;
extern const char *gtWriteFirmwareDataFailureCode;

extern const char *gtFinalizeFirmwareCommandCode;
extern const char *gtFinalizeFirmwareResponseCode;
extern const char *gtFinalizeFirmwareFailureCode;

extern const char *gtSetAppTokenCode;
extern const char *gtSetAppTokenResponseCode;
extern const char *gtSetAppTokenFailureCode;

extern const char *gtGIDTypeOneToOne;
extern const char *gtGIDTypeGroup;
extern const char *gtGIDTypeShout;
extern const char *gtGIDTypeEmergency;

extern const char *gtSetAppTokenCode;
extern const char *gtSetAppTokenResponseCode;

extern const char *gtActivateAntennaSweepCommandCode;
extern const char *gtActivateAntennaSweepResponseCode;
extern const char *gtActivateAntennaSweepFailureCode;

extern const char *gtFrequencyModeCommandCode;
extern const char *gtFrequencyModeResponseCode;
extern const char *gtFrequencyModeFailureCode;

extern const char *gtFrequencyModeNormal;
extern const char *gtFrequencyModeLow;
extern const char *gtFrequencyModeHigh;

extern const char *gtHardwareTransmitCommandCode;

extern const char *gtGetBinaryLogCommandCode;
extern const char *gtGetBinaryLogResponseCode;
extern const char *gtGetBinaryLogFailureCode;

extern const char *gtDeleteBinaryLogCommandCode;
extern const char *gtDeleteBinaryLogResponseCode;
extern const char *gtDeleteBinaryLogFailureCode;

extern const char *gtBERTestCommandCode;
extern const char *gtBERTestResponseCode;
extern const char *gtBERTestFailureCode;

extern const char *gtStoreDateTimeCommandCode;
extern const char *gtStoreDateTimeResponseCode;
extern const char *gtStoreDateTimeFailureCode;

extern const char *gtPowerSavingCommandCode;
extern const char *gtPowerSavingResponseCode;
extern const char *gtPowerSavingFailureCode;

extern const char *gtHardResetCommandCode;
extern const char *gtHardResetResponseCode;
extern const char *gtHardResetFailureCode;

extern const char *gtSetConfigPropertyCommandCode;
extern const char *gtSetConfigPropertyResponseCode;
extern const char *gtSetConfigPropertyFailureCode;

extern const char *gtSetRuntimePropertyCommandCode;
extern const char *gtSetRuntimePropertyResponseCode;
extern const char *gtSetRuntimePropertyFailureCode;

extern const char *gtGetRuntimePropertyCommandCode;
extern const char *gtGetRuntimePropertyResponseCode;
extern const char *gtGetRuntimePropertyFailureCode;

extern const char *gtDebugStatsCommandCode;
extern const char *gtDebugStatsResponseCode;
extern const char *gtDebugStatsFailureCode;

extern const char *gtResetDebugStatsCommandCode;
extern const char *gtResetDebugStatsResponseCode;
extern const char *gtResetDebugStatsFailureCode;

extern const char *gtSetGeoRegionCommandCode;
extern const char *gtSetGeoRegionResponseCode;
extern const char *gtSetGeoRegionFailureCode;

extern const char *gtGetGeoRegionCommandCode;
extern const char *gtGetGeoRegionResponseCode;
extern const char *gtGetGeoRegionFailureCode;

@interface GTCommandCodeConstants : NSObject
@end
