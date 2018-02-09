//
//  BinaryLog.h
//  goTenna SDK
//
//  Created by JOSHUA M MAKINDA on 7/2/15.
//  Copyright (c) 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BinaryLog : NSObject

- (instancetype)initWithLogData:(NSData *)logData;

- (NSArray *)binaryLogArray;

@end
