//
//  EncryptionInfoHeaderV2.h
//  goTenna SDK
//
//  Created by JOSHUA M MAKINDA on 5/5/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import "EncryptionInfoHeader.h"

@interface EncryptionInfoHeaderV2 : EncryptionInfoHeader

- (void)reassignMessageId;

- (NSString *)calculatePacketIdHash;
+ (int)encryptionInfoBufferSize;
- (int)getResendId;

@end
