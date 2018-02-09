//
//  ContactManager.h
//  HelloGoTenna
//
//  Created by Ryan Cohen on 7/25/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Contact.h"
#import "Group.h"

@interface ContactManager : NSObject

+ (instancetype)sharedManager;

- (Contact *)findContactWithGID:(NSNumber *)gid;

- (NSArray<Group *> *)allGroups;

- (NSArray<Contact *> *)allDemoContacts;
- (NSArray<Contact *> *)allDemoContactsExcludingSelf;

@end
