//
//  GTFirmwareUpdater.h
//  GoTenna
//
//  Created by Julietta Yaunches on 1/7/15.
//  Copyright (c) 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTFirmwareInstallationProgressProtocol.h"

@class GTCommandCenter;
@class GTFirmwareVersion;
@class GTCommand;

@protocol GTFirmwareInstallationProgressProtocol;

@interface GTFirmwareWriter : NSObject

@property (nonatomic) BOOL isDownloading;

- (instancetype)initWithVersionToWrite:(GTFirmwareVersion *)version
                      progressDelegate:(id <GTFirmwareInstallationProgressProtocol>)progressDelegate
                        onFinalizeSent:(void (^)())onFinalizeSent;

- (void)writeFirmware;
- (void)abortCurrentCommand:(GTFirmwareWriterFailureState)failState;
- (void)resolveInProgressWrite:(double)currentInstalledVersion;

@end
