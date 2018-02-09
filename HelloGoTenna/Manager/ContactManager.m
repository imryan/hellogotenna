//
//  ContactManager.m
//  HelloGoTenna
//
//  Created by Ryan Cohen on 7/25/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import "ContactManager.h"
#import <GoTennaSDK/UserDataStore.h>
#import <GoTennaSDK/User.h>

NSString * const kGroupCreatedNotification = @"kGroupCreatedNotification";

@interface ContactManager ()

@property (nonatomic, strong) NSMutableArray<Contact *> *contacts;
@property (nonatomic, strong) NSMutableArray<Group *> *groups;

@end

@implementation ContactManager

# pragma mark - Init

+ (instancetype)sharedManager {
    static ContactManager *manager = nil;
    static dispatch_once_t onceToken;
    
    dispatch_once(&onceToken, ^{
        manager = [self new];
    });
    
    return manager;
}

- (instancetype)init {
    self = [super init];
    
    if (self) {
        _contacts = [NSMutableArray arrayWithCapacity:4];
        _groups = [NSMutableArray array];
        
        [self.contacts addObject:[[Contact alloc] initWithName:@"Alice" gid:@8123456789]];
        [self.contacts addObject:[[Contact alloc] initWithName:@"Bob"   gid:@89876543211]];
        [self.contacts addObject:[[Contact alloc] initWithName:@"Carol" gid:@811235813211]];
        [self.contacts addObject:[[Contact alloc] initWithName:@"Doug"  gid:@83141592651]];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(createdGroup:) name:kGroupCreatedNotification object:nil];
    }
    
    return self;
}

# pragma mark - Queries

- (Contact *)findContactWithGID:(NSNumber *)gid {
    for (Contact *contact in self.contacts) {
        if ([contact.gid isEqualToNumber:gid]) {
            return contact;
        }
    }
    
    return nil;
}

- (NSArray<Group *> *)allGroups {
    return [self.groups copy];
}

- (NSArray<Contact *> *)allDemoContacts {
    return [self.contacts copy];
}

- (NSArray<Contact *> *)allDemoContactsExcludingSelf {
    NSMutableArray *contactsExcludingSelf = [NSMutableArray arrayWithCapacity:4];
    NSNumber *currentUserGID = [[UserDataStore shared] currentUser].gId ?: 0;
    
    for (Contact *contact in self.contacts) {
        if (![contact.gid isEqualToNumber:currentUserGID]) {
            [contact setInvitationState:GroupInvitationStateNone];
            [contactsExcludingSelf addObject:contact];
        }
    }
    
    return contactsExcludingSelf;
}

# pragma mark - Helpers

- (void)createdGroup:(NSNotification *)notification {
    if ([notification.name isEqualToString:kGroupCreatedNotification]) {
        Group *group = notification.userInfo[@"group"];
        
        if (![self.groups containsObject:group]) {
            [self.groups addObject:group];
        }
    }
}

@end
