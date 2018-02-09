//
//  MeshHopRecorder.h
//  goTenna
//
//  Created by JOSHUA M MAKINDA on 5/30/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MeshHopRecorder : NSObject

+ (instancetype)sharedInstance;

- (NSUInteger)hopCountForGID:(NSNumber *)gid;
- (void)receivedHopResponseGID:(NSNumber *)gid hopCount:(NSUInteger)hopCount;

@end
