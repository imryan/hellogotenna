//
//  GTPairingConnectionState.h
//  goTenna SDK
//
//  Created by JOSHUA M MAKINDA on 9/21/15.
//  Copyright (c) 2015 JOSHUA M MAKINDA. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    Disconnected = 1,
    Connecting,
    Connected
} GTConnectionState;

@interface GTPairingConnectionState : NSObject

//commands
- (void)setConnectionState:(GTConnectionState)connectionState;

//queries
- (BOOL)isNewState:(GTConnectionState)connectionState;
- (GTConnectionState)connectionState;

@end
