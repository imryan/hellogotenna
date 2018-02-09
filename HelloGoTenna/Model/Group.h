//
//  Group.h
//  HelloGoTenna
//
//  Created by Ryan Cohen on 8/1/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class Contact;

@interface Group : NSObject

@property (nonatomic, readonly) NSNumber *groupGID;
@property (nonatomic, readonly) NSArray<Contact *> *groupMembers;

- (instancetype)initWithGID:(NSNumber *)gid groupMembers:(NSArray<Contact *> *)groupMembers;

@end
