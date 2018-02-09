//
// Created by Julietta Yaunches on 3/17/15.
// Copyright (c) 2015 gotenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GTGid;
@class GTResponse;

@interface GTMessageData : NSObject

@property (nonatomic, strong) NSNumber *addressedGID;
@property (nonatomic, strong) NSData *commandData;
@property (nonatomic, strong) NSNumber *senderGID;
@property (nonatomic, strong) NSDate *messageSentDate;
@property (nonatomic, assign) NSUInteger hopCount;

- (instancetype)initWithData:(NSData *)data addressedGID:(NSNumber *)addressedGID response:(GTResponse *)response;
- (BOOL)isValid;

@end
