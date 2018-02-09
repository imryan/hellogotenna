//
//  Contact.m
//  HelloGoTenna
//
//  Created by Ryan Cohen on 7/25/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import "Contact.h"

@implementation Contact

- (instancetype)initWithName:(NSString *)name gid:(NSNumber *)gid {
    self = [super init];
    
    if (self) {
        _name = name;
        _gid = gid;
    }
    
    return self;
}

- (NSString *)invitationStateString {
    NSString *state = nil;
    
    switch (self.invitationState) {
        case GroupInvitationStateNone:
            state = @"Awaiting Invite";
            break;
        case GroupInvitationStateSending:
            state = @"Sending...";
            break;
        case GroupInvitationStateReceived:
            state = @"Received";
            break;
        case GroupInvitationStateNotReceived:
            state = @"Not Received";
            break;
    }
    
    return state;
}

@end
