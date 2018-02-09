//
//  Contact.h
//  HelloGoTenna
//
//  Created by Ryan Cohen on 7/25/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, GroupInvitationState) {
    GroupInvitationStateNone,
    GroupInvitationStateSending,
    GroupInvitationStateReceived,
    GroupInvitationStateNotReceived
};

@interface Contact : NSObject

@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSNumber *gid;
@property (nonatomic, assign) GroupInvitationState invitationState;

- (instancetype)initWithName:(NSString *)name gid:(NSNumber *)gid;

- (NSString *)invitationStateString;

@end
