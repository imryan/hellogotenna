//
// Created by Julietta Yaunches on 4/8/15.
// Copyright (c) 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTFileLogger.h"
#import "GTLogExportProtocol.h"

@class GTDocumentManager;

@interface GTCommunicationLogger : GTFileLogger <GTLogExportProtocol>

+ (instancetype)shared;

- (void)log:(NSString *)logText;

@end
