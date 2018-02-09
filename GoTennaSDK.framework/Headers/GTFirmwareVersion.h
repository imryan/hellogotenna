//
// Created by Julietta Yaunches on 1/13/15.
// Copyright (c) 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GTFirmwareVersion : NSObject <NSCoding>

@property (nonatomic) double firmwareVersion;
@property (nonatomic, copy) NSString *filename;
@property (nonatomic, strong) NSDate *installedDate;

+ (instancetype)initWithFilename:(NSString *)filename andFirmwareVersion:(double)firmwareVersion;

- (NSData *)featureVersionData;
- (NSData *)producationVersionData;

- (NSString *)printableVersion;

@end
