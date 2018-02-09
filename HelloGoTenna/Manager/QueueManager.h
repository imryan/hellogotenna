//
//  QueueManager.h
//  HelloGoTenna
//
//  Created by Ryan Cohen on 8/3/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class QueueManager;
@class QueueItem;
@class Message;

@protocol QueueManagerProtocol <NSObject>

- (void)queueManager:(QueueManager *)manager didResendMessage:(Message *)message;

@end

@interface QueueManager : NSObject

@property (nonatomic, weak) id<QueueManagerProtocol> delegate;

/**
 Shared manager
 
 @return Manager singleton instance
 */
+ (instancetype)sharedManager;

/**
 Add message to queue
 
 Called when a send message fails with a data rate
 limit exceeded error.
 
 @param message @c Message object
 */
- (void)addMessageToQueue:(Message *)message;

/**
 Remove message from queue
 
 @param message @c Message object
 */
- (void)removeMessageFromQueue:(Message *)message;

@end
