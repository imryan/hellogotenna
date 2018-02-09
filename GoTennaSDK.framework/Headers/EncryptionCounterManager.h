//
//  EncryptionCounterManager.h
//  goTenna
//
//  Created by JOSHUA M MAKINDA on 2/1/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface EncryptionCounterManager : NSObject

+ (EncryptionCounterManager *)shared;

- (void)load;
- (void)save;
- (void)clear;
- (void)incrementCounterforGID:(NSNumber*)gid;

- (short)retrieveAndIncrementCounterForGID:(NSNumber*)gid;

@end
