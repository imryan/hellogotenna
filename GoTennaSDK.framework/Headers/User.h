//
//  User.h
//  goTenna SDK
//
//  Created by Julietta Yaunches on 25/06/2014.
//  Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CLLocation;
@class GoTennaKeyPair;

@interface User : NSObject <NSCoding>

@property (nonatomic, retain) NSNumber *gId;
@property (nonatomic, retain) NSNumber *userId;
@property (nonatomic, retain) NSString *name;
@property (nonatomic, retain) NSString *email;
@property (nonatomic, readonly) NSDate *lastLocationTime;
@property (nonatomic, strong) NSDate *lastConnectedTime;
@property (nonatomic, strong) NSDate *lastConnectionStartedTime;

+ (instancetype)initWithUsername:(NSString *)username andGid:(NSNumber *)gId;

- (CLLocation *)lastLocation;
- (NSString *)initials;

- (void)setLastLocation:(CLLocation *)lastLocation;

- (void)addGroupGID:(NSNumber *)number;
- (void)deleteGroupGID:(NSNumber *)number;
- (BOOL)hasGroupGID:(NSNumber *)number;

- (void)addMulticastGID:(NSNumber *)number;
- (void)deleteMulticastGID:(NSNumber *)number;
- (BOOL)hasMulticastGroupGID:(NSNumber *)number;

- (BOOL)hasEmail;
- (BOOL)hasVerifiedGID;

- (NSArray<NSNumber *> *)allGroupGIDs;
- (NSArray<NSNumber *> *)allMulticastGIDs;

@end
