//
//  GroupSecretManager.h
//  goTenna SDK
//
//  Created by Thomas Colligan on 1/12/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GroupSecretManager : NSObject

+ (instancetype)shared;
+ (NSData *)generateSharedSecret;

- (void)saveSecret:(NSData *)sharedSecret forGroup:(NSNumber *)groupGID;
- (NSData *)createAndSaveSecretForGroup:(NSNumber *)groupGID;
- (NSData *)getSharedSecretForGroup:(NSNumber *)groupGID;

@end
