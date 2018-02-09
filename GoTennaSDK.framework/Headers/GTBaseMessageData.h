//
// Created by Julietta Yaunches on 11/18/14.
// Copyright (c) 2014 goTenna-inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTLocationMessageData.h"

@class TLVSection;

@interface GTBaseMessageData : NSObject

@property (nonatomic) NSString *messageType;
@property (nonatomic, strong) NSNumber *senderGID;
@property (nonatomic, strong) NSString *senderInitials;
@property (nonatomic, strong) NSNumber *addresseeGID;
@property (nonatomic, strong) NSNumber *receivingGID;
@property (nonatomic, strong) GTLocationMessageData *locationMessageData;
@property (nonatomic, copy) NSString *text;
@property (nonatomic, strong) NSArray *baseDataComponents;
@property (nonatomic, strong) GTLocationMessageData *senderLocationData;
@property (nonatomic, strong) NSDate *messageSentDate;
@property (nonatomic, assign) NSUInteger hopCount;

- (instancetype)initOutgoingOnError:(NSError **)pError;
- (instancetype)initIncoming:(NSArray<TLVSection *> *)array withSenderGID:(NSNumber *)senderGID;

- (void)setAddressedGID:(NSNumber *)number;
- (NSNumber *)getGIDNumber:(id)value;

- (NSArray<TLVSection *> *)buildTLVSections;
- (NSArray<TLVSection *> *)getTLVSections;

- (NSData *)serializeToBytes;

@end
