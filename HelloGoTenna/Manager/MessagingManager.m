//
//  MessagingManager.m
//  HelloGoTenna
//
//  Created by Ryan Cohen on 7/26/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import "MessagingManager.h"
#import "ContactManager.h"
#import "QueueManager.h"
#import "Group.h"

@import GoTennaSDK;

const int MIN_TLV = 2;

NSString * const kGroupCreatedNotificationSender = @"kGroupCreatedNotification";

@implementation MessagingManager

# pragma mark - Init

+ (instancetype)sharedManager {
    static MessagingManager *manager = nil;
    static dispatch_once_t onceToken;
    
    dispatch_once(&onceToken, ^{
        manager = [self new];
    });
    
    return manager;
}

- (instancetype)init {
    self = [super init];
    
    if (self) {
        [[GTCommandCenter shared] setOnIncomingMessage:^(GTMessageData *messageData) {
            [self handleIncomingMessage:messageData];
        }];
        
        [[GTCommandCenter shared] setOnGroupCreated:^(GTGroupCreationMessageData *messageData) {
            [self handleIncomingGroupCreation:messageData];
        }];
    }
    
    return self;
}

# pragma mark - Incoming Messages

- (void)handleIncomingMessage:(GTMessageData *)response {
    NSArray<TLVSection *> *tlvSections = [TLVSection tlvSectionsFromData:response.commandData];
    
    // Bad message
    if (tlvSections.count < MIN_TLV) {
        return;
    }
    
    GTBaseMessageData *messageData = [[GTBaseMessageData alloc] initIncoming:tlvSections withSenderGID:response.senderGID];
    GTBaseMessageData *(^buildMessageBlock)(NSArray<TLVSection *> *, NSNumber *senderGID) = [self messageDeserializationDictionary][messageData.messageType];
    
    if (buildMessageBlock) {
        GTBaseMessageData *baseMessageData = buildMessageBlock(tlvSections, messageData.senderGID);
        baseMessageData.addresseeGID = response.addressedGID;
        baseMessageData.messageSentDate = response.messageSentDate;
        
        // Public keys
        if ([baseMessageData isKindOfClass:[GTPublicKeyFirmwareResponseMessageData class]] ||
            [baseMessageData isKindOfClass:[GTPublicKeyUserResponseMessageData class]] ||
            [baseMessageData isKindOfClass:[GTPublicKeyRequestMessageData class]] ||
            [baseMessageData isKindOfClass:[GTMeshPublicKeyRequestMessageData class]] ||
            [baseMessageData isKindOfClass:[GTMeshPublicKeyResponseMessageData class]]) {
            
            [self handlePublicKeyMessage:baseMessageData];
            return;
        }
        
        // Callback generic message type
        //        if ([self.delegate respondsToSelector:@selector(messagingManager:didReceiveIncoming:)]) {
        //            [self.delegate messagingManager:self didReceiveIncoming:baseMessageData];
        //        }
        
        Message *message = [[Message alloc] initWithData:(GTTextOnlyMessageData *)baseMessageData];
        GTGIDType gidType = [GIDManager gidTypeForGID:baseMessageData.addresseeGID];
        
        switch (gidType) {
            case ShoutGID:
                if ([self.delegate respondsToSelector:@selector(messagingManager:didReceiveIncomingShout:)]) {
                    [self.delegate messagingManager:self didReceiveIncomingShout:message];
                }
                break;
            case OneToOneGID:
                if ([self.delegate respondsToSelector:@selector(messagingManager:didReceiveIncomingMessage:)]) {
                    [self.delegate messagingManager:self didReceiveIncomingMessage:message];
                }
                break;
            case GroupGID:
                if ([self.delegate respondsToSelector:@selector(messagingManager:didReceiveIncomingMessage:)]) {
                    [self.delegate messagingManager:self didReceiveIncomingMessage:message];
                }
                break;
            default:
                break;
        }
    }
}

- (void)handleIncomingGroupCreation:(GTGroupCreationMessageData *)messageData {
    NSNumber *groupGID = [messageData groupGID];
    NSMutableArray<Contact *> *groupMembers = [NSMutableArray array];
    
    for (NSNumber *gid in [messageData groupAddressees]) {
        Contact *contact = [[ContactManager sharedManager] findContactWithGID:gid];
        
        if (contact) {
            [groupMembers addObject:contact];
        }
    }
    
    Group *group = [[Group alloc] initWithGID:groupGID groupMembers:groupMembers];
    [[NSNotificationCenter defaultCenter] postNotificationName:kGroupCreatedNotificationSender object:nil userInfo:@{ @"group" : group }];
}

- (void)handlePublicKeyMessage:(GTBaseMessageData *)baseMessageData {
    if ([baseMessageData isKindOfClass:[GTPublicKeyFirmwareResponseMessageData class]]) {
        GTPublicKeyFirmwareResponseMessageData *publicKeyMessageData = (GTPublicKeyFirmwareResponseMessageData *)baseMessageData;
        PublicKeyManager *keyManager = [PublicKeyManager shared];
        
        [keyManager addPublicKeyWithGID:publicKeyMessageData.senderGID publicKeyData:publicKeyMessageData.publicKey userHasMyPublicKey:YES];
        [[GTDecryptionErrorManager shared] attemptToDecryptMessagesAgain];
    }
    
    else if ([baseMessageData isKindOfClass:[GTPublicKeyRequestMessageData class]]) {
        [[GTCommandCenter shared] sendPublicKeyResponseToGID:baseMessageData.senderGID];
    }
    
    else if ([baseMessageData isKindOfClass:[GTPublicKeyUserResponseMessageData class]]) {
        GTPublicKeyUserResponseMessageData *publicKeyMessageData = (GTPublicKeyUserResponseMessageData *)baseMessageData;
        PublicKeyManager *keyManager = [PublicKeyManager shared];
        
        [keyManager addPublicKeyWithGID:publicKeyMessageData.senderGID publicKeyData:publicKeyMessageData.publicKey];
        [[GTDecryptionErrorManager shared] attemptToDecryptMessagesAgain];
    }
    
    else if ([baseMessageData isKindOfClass:[GTMeshPublicKeyRequestMessageData class]]) {
        GTMeshPublicKeyRequestMessageData *meshPublicKeyRequestMessageData = (GTMeshPublicKeyRequestMessageData *)baseMessageData;
        NSNumber *senderGID = meshPublicKeyRequestMessageData.senderGID;
        NSData *publicKey = meshPublicKeyRequestMessageData.publicKey;
        
        [[PublicKeyManager shared] addPublicKeyWithGID:senderGID publicKeyData:publicKey];
        
        [[GTCommandCenter shared] sendMyMeshPublicKeyToGID:senderGID];
        [[GTDecryptionErrorManager shared] attemptToDecryptMessagesAgain];
    }
    
    else if ([baseMessageData isKindOfClass:[GTMeshPublicKeyResponseMessageData class]]) {
        [self resendMessagesFromPreKeyExchange:baseMessageData];
        [[GTDecryptionErrorManager shared] attemptToDecryptMessagesAgain];
        
    }
}

- (void)resendMessagesFromPreKeyExchange:(GTBaseMessageData *)baseMessageData {
    GTMeshPublicKeyResponseMessageData *meshPublicKeyResponseMessageData = (GTMeshPublicKeyResponseMessageData *)baseMessageData;
    NSNumber *senderGID = meshPublicKeyResponseMessageData.senderGID;
    NSData *publicKey = meshPublicKeyResponseMessageData.publicKey;
    
    [[PublicKeyManager shared] addPublicKeyWithGID:senderGID publicKeyData:publicKey];
    [[PublicKeyManager shared] setPublicKeyStateWithGID:senderGID userHasMyPublicKey:YES];
    
    if (![[GTCommandCenter shared] hasPostKeyExchangeMeshMessagesToResend]) return;
    
    NSMutableArray<GTSendCommand *> *messagesToSend = [NSMutableArray array];
    
    for (GTSendCommand *sendMessageCommand in [[GTCommandCenter shared] meshMessageToResendList]) {
        if ([sendMessageCommand.recipientGID isEqualToNumber:senderGID]) {
            [sendMessageCommand invalidateTimeout];
            sendMessageCommand.responseReceived = YES;
            
            [messagesToSend addObject:sendMessageCommand];
        }
    }
    
    [[[GTCommandCenter shared] meshMessageToResendList] removeObjectsInArray:messagesToSend];
    
    for (GTSendCommand *sendMessageCommand in messagesToSend) {
        void (^onResponse)(GTResponse *) = ^(GTResponse *res) {
            sendMessageCommand.processResponse(res);
        };
        
        [[GTCommandCenter shared] sendMessage:sendMessageCommand.outgoingData
                                        toGID:sendMessageCommand.recipientGID
                                      fromGID:sendMessageCommand.senderGID
                                   onResponse:onResponse
                                      onError:sendMessageCommand.onError];
    }
    
    NSArray<GTSendCommand *> *removedCommands = [[GTCommandCenter shared] removedKeyExchangeMessagesRetrievalWithGID:senderGID];
    
    for (GTSendCommand *sendMessageCommand in removedCommands) {
        void (^onResponse)(GTResponse *) = ^(GTResponse *res) {
            sendMessageCommand.processResponse(res);
        };
        
        [[GTCommandCenter shared] sendMessage:sendMessageCommand.outgoingData
                                        toGID:sendMessageCommand.recipientGID
                                      fromGID:sendMessageCommand.senderGID
                                   onResponse:onResponse
                                      onError:sendMessageCommand.onError];
    }
}

# pragma mark - Outgoing Messages

- (void)sendBroadcastMessage:(Message *)message {
    void (^onError)(NSError *error) = ^(NSError *error) {
        if (error && [error isEqual:[GTError dataRateLimitExceeded]]) {
            [[QueueManager sharedManager] addMessageToQueue:message];
        } else {
            if ([self.delegate respondsToSelector:@selector(messagingManager:didFailSendingMessage:)]) {
                [self.delegate messagingManager:self didFailSendingMessage:message];
            }
        }
    };
    
    void (^onResponse)(GTResponse *) = ^(GTResponse *response) {
        if ([response responsePositive]) {
            // Hop count not set for broadcasts
            if ([self.delegate respondsToSelector:@selector(messagingManager:didSendOutgoingMessage:)]) {
                [self.delegate messagingManager:self didSendOutgoingMessage:message];
            }
            
            [[QueueManager sharedManager] removeMessageFromQueue:message];
        }
    };
    
    [[GTCommandCenter shared] sendBroadcast:[message toBytes] onResponse:onResponse onError:onError];
}

- (void)sendMessage:(Message *)message encrypt:(BOOL)encrypt {
    [GTUserDefaults setEncryptionEnabled:encrypt];
    
    void (^onError)(NSError *error) = ^(NSError *error) {
        if (error && [error isEqual:[GTError dataRateLimitExceeded]]) {
            [[QueueManager sharedManager] addMessageToQueue:message];
        } else {
            if ([self.delegate respondsToSelector:@selector(messagingManager:didFailSendingMessage:)]) {
                [self.delegate messagingManager:self didFailSendingMessage:message];
            }
        }
    };
    
    void (^onResponse)(GTResponse *) = ^(GTResponse *response) {
        if ([response responsePositive]) {
            GTGIDType type = [GIDManager gidTypeForGID:message.receiverGID];
            
            if (type == OneToOneGID) {
                [message setHopCount:response.hopCount];
            }
            
            if ([self.delegate respondsToSelector:@selector(messagingManager:didSendOutgoingMessage:)]) {
                [self.delegate messagingManager:self didSendOutgoingMessage:message];
            }
            
            [[QueueManager sharedManager] removeMessageFromQueue:message];
        }
    };
    
    [[GTCommandCenter shared] sendMessage:[message toBytes] toGID:message.receiverGID fromGID:message.senderGID onResponse:onResponse onError:onError];
}

# pragma mark - Helpers

- (NSDictionary *)messageDeserializationDictionary {
    return @{
             kMessageTypeTextOnly : ^GTBaseMessageData *(NSArray<TLVSection *> *dataArray, NSNumber *senderGID) {
                 return [[GTTextOnlyMessageData alloc] initFromOrderedData:dataArray withSenderGID:senderGID];
             },
             
             kMessageTypeSetGroupGID : ^GTBaseMessageData *(NSArray<TLVSection *> *dataArray, NSNumber *senderGID) {
                 return [[GTGroupCreationMessageData alloc] initFromOrderedData:dataArray withSenderGID:senderGID];
             },
             
             kMessageTypeFirmwarePublicKeyResponse : ^GTBaseMessageData *(NSArray<TLVSection *> *dataArray, NSNumber *senderGID) {
                 return [[GTPublicKeyFirmwareResponseMessageData alloc] initFromOrderedData:dataArray withSenderGID:senderGID];
             },
             
             kMessageTypeUserPublicKeyResponse : ^GTBaseMessageData *(NSArray<TLVSection *> *dataArray, NSNumber *senderGID) {
                 return [[GTPublicKeyUserResponseMessageData alloc] initFromOrderedData:dataArray withSenderGID:senderGID];
             },
             
             kMessageTypePublicKeyRequest : ^GTBaseMessageData *(NSArray<TLVSection *> *dataArray, NSNumber *senderGID) {
                 return [[GTPublicKeyRequestMessageData alloc] initFromOrderedData:dataArray withSenderGID:senderGID];
             },
             
             kMessageTypeMeshPublicKeyRequest : ^GTBaseMessageData *(NSArray<TLVSection *> *dataArray, NSNumber *senderGID) {
                 return [[GTMeshPublicKeyRequestMessageData alloc] initFromOrderedData:dataArray withSenderGID:senderGID];
             },
             
             kMessageTypeMeshPublicKeyResponse : ^GTBaseMessageData *(NSArray<TLVSection *> *dataArray, NSNumber *senderGID) {
                 return [[GTMeshPublicKeyResponseMessageData alloc] initFromOrderedData:dataArray withSenderGID:senderGID];
             } };
}

@end
