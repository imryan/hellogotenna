//
//  GTGid.h
//  goTenna SDK
//
//  Created by Julietta Yaunches on 3/2/15.
//  Copyright (c) 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTDataTypes.h"

@interface GTGid : NSObject

@property (nonatomic, strong, readonly) NSNumber *baseNumber;
@property (nonatomic) GTGIDType type;

+ (GTGid *)initWithBase:(NSNumber *)number;
+ (GTGid *)initfromData:(NSData *)data;

- (NSString *)built;
- (NSData *)asData;
- (NSData *)asDataWithType;
- (NSData *)asDataWithTypeUsingMembershipByte:(NSData *)membershipByte;

- (NSUInteger)GIDDataByteLength;

@end
