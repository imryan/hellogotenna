//
//  BinaryLogLogger.h
//  goTenna SDK
//
//  Created by JOSHUA M MAKINDA on 7/6/15.
//  Copyright (c) 2015 goTenna. All rights reserved.
//

#import "GTFileLogger.h"
#import "GTLogExportProtocol.h"

@interface BinaryLogLogger : GTFileLogger <GTLogExportProtocol>

+ (instancetype)shared;

- (void)logRecievedBinaryLogs:(NSArray *)binaryArrays;

@end
