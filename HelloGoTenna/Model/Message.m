//
//  Message.m
//  HelloGoTenna
//
//  Created by Ryan Cohen on 7/25/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import "Message.h"
#import "ContactManager.h"

@implementation Message

# pragma mark - Init

- (instancetype)initWithSenderGID:(NSNumber *)senderGID
                      receiverGID:(NSNumber *)receiverGID
                             text:(NSString *)text
                         sentDate:(NSDate *)sentDate
                           status:(MessageStatus)status
                       senderInfo:(NSString *)senderInfo {
    
    self = [super init];
    
    if (self) {
        _senderGID = senderGID;
        _receiverGID = receiverGID;
        _text = text;
        _sentDate = sentDate;
        _status = status;
        _senderInfo = senderInfo;
    }
    
    return self;
}

- (instancetype)initWithText:(NSString *)text
                   senderGID:(NSNumber *)senderGID
                 receiverGID:(NSNumber *)receiverGID {
    
    return [self initWithSenderGID:senderGID
                       receiverGID:receiverGID
                              text:text
                          sentDate:[NSDate date]
                            status:MessageStatusSending
                        senderInfo:nil];
}

- (instancetype)initWithData:(GTTextOnlyMessageData *)messageData {
    self = [self initWithSenderGID:messageData.senderGID
                       receiverGID:messageData.addresseeGID
                              text:messageData.text
                          sentDate:messageData.messageSentDate
                            status:MessageStatusSent
                        senderInfo:[self getSenderInfo:messageData]];
    
    if (self) {
        _hopCount = messageData.hopCount;
    }
    
    return self;
}

# pragma mark - Helpers

- (NSData *)toBytes {
    NSError *error = nil;
    GTTextOnlyMessageData *messageData = [[GTTextOnlyMessageData alloc] initOutgoingWithText:self.text onError:&error];
    
    if (error) {
        NSLog(@"[GoTenna] Error in: %@ %@", NSStringFromSelector(_cmd), error.localizedDescription);
    }
    
    return (messageData) ? [messageData serializeToBytes] : nil;
}

- (NSString *)getSenderInfo:(GTBaseMessageData *)messageData {
    Contact *contact = [[ContactManager sharedManager] findContactWithGID:messageData.senderGID];
    NSString *senderInitials = messageData.senderInitials;
    
    if (contact) {
        return contact.name;
    }
    else if (senderInitials) {
        return senderInitials;
    }
    
    return [messageData.senderGID stringValue];
}

@end
