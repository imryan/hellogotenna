//
//  ChatTableDataSource.m
//  HelloGoTenna
//
//  Created by Ryan Cohen on 8/1/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import "ChatTableDataSource.h"
#import <GoTennaSDK/GoTennaSDK.h>
#import "ContactManager.h"
#import "MessagingManager.h"

@interface ChatTableDataSource ()

@property (nonatomic, assign) GTGIDType conversationType;
@property (nonatomic, weak) id<ChatTableProtocol> delegate;

@property (nonatomic, strong) NSMutableArray<Message *> *messages;

@end

@implementation ChatTableDataSource

# pragma mark - Init

- (instancetype)initWithConversationType:(GTGIDType)conversationType delegate:(id<ChatTableProtocol>)delegate {
    self = [super init];
    
    if (self) {
        _conversationType = conversationType;
        _messages = [NSMutableArray array];
        _recipients = [NSMutableArray arrayWithCapacity:4];
        
        if (delegate) {
            _delegate = delegate;
        }
    }
    
    return self;
}

# pragma mark - Functions

- (void)addMessage:(Message *)message {
    if (![self.messages containsObject:message]) {
        [self.messages addObject:message];
    }
}

# pragma mark - Data Source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return [self sectionCount];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    NSUInteger rows = 0;
    
    // Recipients/Messages
    if (section == 0) {
        if ([self recipientsNotDisplayed]) {
            rows = [self.messages count];
        } else {
            rows = [self.recipients count];
        }
    }
    
    // Messages
    if (section == 1) {
        if (![self recipientsNotDisplayed]) {
            rows = [self.messages count];
        }
    }
    
    // Send button
    if (section == [self sectionCount] - 1) rows = 1;
    
    return rows;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    NSString *title = nil;
    
    if (section == 0) {
        if ([self recipientsNotDisplayed]) {
            title = ([self.messages count] > 0) ? @"Messages" : nil;
        } else {
            title = @"Recipients";
        }
    }
    
    if (section == 1) {
        if (![self recipientsNotDisplayed]) {
            title = ([self.messages count] > 0) ? @"Messages" : nil;
        }
    }
    
    return title;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"CellId" forIndexPath:indexPath];
    NSString *key = nil, *value = nil;
    
    if (indexPath.section == 0) {
        if ([self recipientsNotDisplayed]) {
            Message *message = self.messages[indexPath.row];
            key = ([[UserDataStore shared] isMyGID:message.senderGID]) ? @"Me" : message.senderInfo;
            value = (message.hopCount > 0) ? [NSString stringWithFormat:@"%@ (%lu hop%@)", message.text, (unsigned long)message.hopCount, (message.hopCount > 1) ? @"s" : @""] : message.text;
        } else {
            Contact *contact = self.recipients[indexPath.row];
            key = contact.name;
            value = (self.conversationType == GroupGID) ? @"" : [NSString presentGID:contact.gid];
        }
    }
    else if (indexPath.section == 1) {
        if (![self recipientsNotDisplayed]) {
            Message *message = self.messages[indexPath.row];
            key = ([[UserDataStore shared] isMyGID:message.senderGID]) ? @"Me" : message.senderInfo;
            value = (message.hopCount > 0) ? [NSString stringWithFormat:@"%@ (%lu hop%@)", message.text, (unsigned long)message.hopCount, (message.hopCount > 1) ? @"s" : @""] : message.text;
        }
    }
    
    // Send button
    if (indexPath.section == [self sectionCount] - 1) key = @"Send Message";
    
    cell.textLabel.text = key;
    cell.detailTextLabel.text = value;
    cell.accessoryType = (value) ? UITableViewCellAccessoryNone : UITableViewCellAccessoryDisclosureIndicator;
    cell.selectionStyle = (indexPath.section == [self sectionCount] - 1) ? UITableViewCellSelectionStyleDefault : UITableViewCellSelectionStyleNone;
    
    return cell;
}

# pragma mark - Delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
    
    // Select 1-to-1 recipient
    if (indexPath.section == 0 && self.conversationType == OneToOneGID) {
        Contact *selectedRecipient = self.recipients[indexPath.row];
        
        for (UITableViewCell *cell in [tableView visibleCells]) {
            cell.accessoryType = UITableViewCellAccessoryNone;
        }
        
        cell.accessoryType = UITableViewCellAccessoryCheckmark;
        
        if ([self.delegate respondsToSelector:@selector(chatTable:didSelectContact:)]) {
            [self.delegate chatTable:self didSelectContact:selectedRecipient];
        }
    }
    
    if ([self.delegate respondsToSelector:@selector(chatTable:didSelectCell:)]) {
        [self.delegate chatTable:self didSelectCell:cell];
    }
    
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

# pragma mark - Helpers

- (NSUInteger)sectionCount {
    NSUInteger sections = 0;
    
    switch (self.conversationType) {
        case ShoutGID:
            sections = 2;
            break;
        case OneToOneGID:
            sections = 3;
            break;
        case GroupGID:
            sections = 3;
            break;
        case EmergencyGID:
            sections = 2;
            break;
    }
    
    return sections;
}

- (NSUInteger)rowsForSection:(NSUInteger)section {
    NSUInteger rows = 0;
    
    switch (section) {
        case 0:
            rows = 1;
            break;
        default:
            break;
    }
    
    return rows;
}

- (BOOL)recipientsNotDisplayed {
    return (self.conversationType == ShoutGID);
}

@end
