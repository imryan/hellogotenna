//
//  Group.m
//  HelloGoTenna
//
//  Created by Ryan Cohen on 8/1/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import "Group.h"
#import "Contact.h"
#import <GoTennaSDK/UserDataStore.h>

@interface Group ()

@property (nonatomic, strong) NSNumber *groupGID;
@property (nonatomic, strong) NSArray<Contact *> *groupMembers;

@end

@implementation Group

# pragma mark - Init

- (instancetype)initWithGID:(NSNumber *)gid groupMembers:(NSArray<Contact *> *)groupMembers {
    self = [super init];
    
    if (self) {
        _groupGID = gid;
        _groupMembers = groupMembers;
    }
    
    return self;
}

# pragma mark - Queries

- (NSArray<Contact *> *)groupMembers {
    NSMutableArray<Contact *> *mutableGroupMembers = [_groupMembers mutableCopy];
    
    // Display all contacts in group except self
    for (Contact *contact in mutableGroupMembers) {
        if ([[UserDataStore shared] isMyGID:contact.gid]) {
            [mutableGroupMembers removeObject:contact];
            break;
        }
    }
    
    return mutableGroupMembers;
}

@end
