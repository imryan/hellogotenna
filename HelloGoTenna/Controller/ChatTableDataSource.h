//
//  ChatTableDataSource.h
//  HelloGoTenna
//
//  Created by Ryan Cohen on 8/1/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GoTennaSDK/GTDataTypes.h>

@class ChatTableDataSource;
@class Contact;

@protocol ChatTableProtocol <NSObject>

@required;
- (void)chatTable:(ChatTableDataSource *)chatTable didSelectCell:(UITableViewCell *)cell;
- (void)chatTable:(ChatTableDataSource *)chatTable didSelectContact:(Contact *)contact;

@end

@class Message;

@interface ChatTableDataSource : NSObject <UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, strong) NSArray<Contact *> *recipients;

- (instancetype)initWithConversationType:(GTGIDType)conversationType delegate:(id<ChatTableProtocol>)delegate;

- (void)addMessage:(Message *)message;

@end
