//
//  MessagingManager.h
//  HelloGoTenna
//
//  Created by Ryan Cohen on 7/26/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GoTennaSDK/GTGroupCreationMessageData.h>
#import "Message.h"
#import "Group.h"

typedef void (^MessagingManagerResponse)(Message *message, NSError *error);

@class MessagingManager;

@protocol MessagingManagerProtocol <NSObject>

@required
- (void)messagingManager:(MessagingManager *)manager didReceiveIncomingShout:(Message *)message;
- (void)messagingManager:(MessagingManager *)manager didReceiveIncomingMessage:(Message *)message;
- (void)messagingManager:(MessagingManager *)manager didSendOutgoingMessage:(Message *)message;
- (void)messagingManager:(MessagingManager *)manager didFailSendingMessage:(Message *)message;

@optional
- (void)messagingManager:(MessagingManager *)manager didReceiveIncoming:(GTBaseMessageData *)messageData;

@end

@interface MessagingManager : NSObject

@property (nonatomic, weak) id<MessagingManagerProtocol> delegate;

+ (instancetype)sharedManager;

- (void)sendBroadcastMessage:(Message *)message;
- (void)sendMessage:(Message *)message encrypt:(BOOL)encrypt;

@end
