//
//  GTEncryptionInfo.h
//  goTenna SDK
//
//  Created by Ryan Cohen on 3/17/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

@class EncryptionInfoHeader;

#import <Foundation/Foundation.h>

@interface GTEncryptionInfo : NSObject

@property (nonatomic, readonly) NSData *messagePayload;
@property (nonatomic, readonly) EncryptionInfoHeader *encryptionInfoHeader;

- (instancetype)initWithEncryptionInfoHeader:(EncryptionInfoHeader *)encryptionInfoHeader
                              messagePayload:(NSData *)messagePayload;

- (NSString *)calculatePacketIdHash;
- (int)getResendId;

@end
