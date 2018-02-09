//
//  GTMeshAckHandler.h
//  goTenna SDK
//
//  Created by Ryan Cohen on 3/17/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

@class GTSendCommand;
@class GTResponse;
@class TLVSection;

#import <Foundation/Foundation.h>

@interface GTMeshAckHandler : NSObject

/**
 Shared instance of the class
 */
+ (instancetype)sharedInstance;

/**
 Adds a send command along with its response pending an ack to our list
 */
- (void)addCommandPendingAck:(GTSendCommand *)sendCommand response:(GTResponse *)response;

/**
 Removes the send command from our list on time out
 */
- (void)removeCommandPendingAck:(GTSendCommand *)sendCommand;

/**
 Called after the get message call has returns our hop count
 */
- (void)receivedMeshAck:(TLVSection *)tlvSection;

/**
 Returns true if there are commands pending acks in our list
 */
- (BOOL)hasPendingAcks;

/**
 Returns true if there are commands pending acks for the given GID
 */
- (BOOL)hasAckForGID:(NSNumber *)gid;

@end
