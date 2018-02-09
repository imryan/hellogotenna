//
//  BatteryPercentageParser.h
//  MessageLoadingProgress
//
//  Created by JOSHUA M MAKINDA on 8/14/15.
//  Copyright (c) 2015 JOSHUA M MAKINDA. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BatteryPercentageParser : NSObject

+ (instancetype)parser;

- (NSNumber *)percentageForBatteryLevel:(NSNumber *)batteryLevel;

@end
