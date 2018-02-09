//
// Created by Julietta Yaunches on 1/12/15.
// Copyright (c) 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GTDocumentManager;
@class FirmwareFileParser;
@class GTCommandCenter;
@class GTFirmwareVersion;

typedef void (^GTFirmwareOnDownloadBlock)();

extern NSString * const FIRMWARE_PRODUCTION_BUCKET_V1;
extern NSString * const FIRMWARE_PRODUCTION_BUCKET_MESH;

@interface GTFirmwareRetriever : NSObject

- (void)checkForNewFirmware:(GTFirmwareOnDownloadBlock)onDownload;
- (void)downloadNewFirmware:(NSString *)name onDownloaded:(void (^)())onDownloaded;

+ (NSString *)bucketForCurrentDevice;

@end
