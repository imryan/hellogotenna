//
//  GTSystemInfo.h
//  goTenna SDK
//

#import <Foundation/Foundation.h>

@class SystemInfoResponseData;

typedef enum {
    BatteryGoodGreen,
    BatterySlightlyLowYellow,
    BatteryLowRed
} GTBatteryStatusLevel;

@interface GTSystemInfo : NSObject <NSCoding>

@property (nonatomic) double firmwareVersion;
@property (nonatomic) NSNumber *majorRevision;
@property (nonatomic) NSNumber *minorRevision;
@property (nonatomic) NSNumber *buildRevision;
@property (nonatomic) NSNumber *batteryLevel;
@property (nonatomic, copy) NSString *goTennaSerialNumber;

+ (instancetype)initWithSystemInfo:(SystemInfoResponseData *)incomingData;
- (GTBatteryStatusLevel)currentBatteryStatus;

- (NSString *)printableVersion;
- (NSString *)printableRevisionVersion;

@end
