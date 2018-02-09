//
// Created by Julietta Yaunches on 5/06/2014.
// goTenna SDK
//

#import <Foundation/Foundation.h>
#import "GTDataTypes.h"
#import "GTResponse.h"
#import "GTCommand.h"
#import "GTGroupCreationMessageData.h"
#import "RegionBound.h"
#import "GTResponseDispatcher.h"

@protocol BERTestingObserverProtocol;

@class SystemInfoResponseData;
@class GTError;
@class FrequencyMode;
@class BinaryLogResponseData;
@class GTCommandArray;
@class GTSendCommand;

@interface GTCommandCenter : NSObject

/// Called on incoming message.
@property (nonatomic, copy, nonnull) void (^onIncomingMessage)(GTMessageData * _Nullable);

/**
 Shared instance
 
 @return Singleton instance
 */
+ (nonnull instancetype)shared;

/**
 Send echo
 
 Sends an echo command to the connected goTenna.
 Upon receiving an echo the goTenna's LED will flash.
 No actual message is transmitted when an echo is sent.
 
 @param onResponse Called when your goTenna responds with a postive or negative acknowledgement
 @param onError    Called when an error occurs (See error code for details)
 */
- (void)sendEchoCommand:(nullable void (^)(GTResponse * _Nullable))onResponse onError:(nullable void (^)(NSError  * _Nullable))onError;

/**
 Set goTenna GID
 
 This method is used to set a goTenna's unique GID. This GID is used for one-to-one messaging.
 When this gets set, the previous one-to-one GID for the connected goTenna will be erased and the new
 GID set.
 
 @param number   The GID to assign to the goTenna.
 @param username The name of the user who's GID this is.
 @param onError  Called when an error occurs (See error code for details)
 */
- (void)setgoTennaGID:(NSNumber * _Nonnull)number withUsername:(NSString * _Nonnull)username onError:(nullable void (^)(NSError * _Nullable))onError;

/**
 Send 1-to-1 Message
 
 With this you send a single message to another goTenna user. This is the only means of
 sending a message where you'll receive negative or positive confirmation that the receiver
 received your message
 
 NOTE: Must have set goTenna GID before calling this
 NOTE: If your receiver needs to know the sender's GID, you'll need to send it in the payload
 
 @param messageData    The message's data, such as text, preferably formatted in some easily parse-able format.
 @param destinationGID The GID of the user who will receive this private message (must be 15 digits or less and not 111-111-1111).
 @param senderGID      The response listener callback for the command.
 @param onResponse     Called when your goTenna responds with a postive or negative acknowledgement.
 @param onError        Called when an error occurs (See error code for details).
 */
- (void)sendMessage:(NSData * _Nonnull)messageData
              toGID:(NSNumber * _Nonnull)destinationGID
            fromGID:(NSNumber * _Nonnull)senderGID
         onResponse:(nullable void (^)(GTResponse * _Nullable))onResponse
            onError:(nullable void (^)(NSError * _Nullable))onError;

/**
 Send 1-to-1 Message (with options)
 
 With this you send a single message to another goTenna user. This is the only means of
 sending a message where you'll receive negative or positive confirmation that the receiver
 received your message
 
 NOTE: Must have set goTenna GID before calling this
 NOTE: If your receiver needs to know the sender's GID, you'll need to send it in the payload
 
 @param messageData                 The message's data, such as text, preferably formatted in some easily parse-able format.
 @param destinationGID              The GID of the user who will receive this private message (must be 15 digits or less and not 111-111-1111).
 @param senderGID                   The response listener callback for the command.
 @param onResponse                  Called when your goTenna responds with a postive or negative acknowledgement.
 @param onError                     Called when an error occurs (See error code for details).
 @param maxHopCount                 Maximum number of hops this message should make.
 @param shouldNotResendWithMoreHops Indicate that for this message, we should not try to resend the message with more hops if it fails the first time.
 */
- (void)sendMessage:(NSData * _Nonnull)messageData
              toGID:(NSNumber * _Nonnull)destinationGID
            fromGID:(NSNumber * _Nonnull)senderGID
         onResponse:(nullable void (^)(GTResponse * _Nonnull))onResponse
            onError:(nullable void (^)(NSError * _Nullable))onError
        maxHopCount:(NSUInteger)maxHopCount shouldNotResendWithMoreHops:(BOOL)shouldNotResendWithMoreHops
           resendID:(int)resendId willEncrypt:(BOOL)willEncrypt;

/**
 Resend Message
 
 With this you send a single message to another goTenna user. This is the only means of
 sending a message where you'll receive negative or positive confirmation that the receiver
 received your message
 
 NOTE: Must have set goTenna GID before calling this
 NOTE: If your receiver needs to know the sender's GID, you'll need to send it in the payload
 
 @param messageData    The message's data, such as text, preferably formatted in some easily parse-able format.
 @param destinationGID The GID of the user who will receive this private message (must be 15 digits or less and not 111-111-1111).
 @param senderGID      The response listener callback for the command.
 @param onResponse     Called when your goTenna responds with a postive or negative acknowledgement.
 @param onError        Called when an error occurs (See error code for details).
 @param resendId       The id of the message to resend that was returned in the previous @c GTResponse or @c GTError.
 */
- (void)resendMessage:(NSData * _Nonnull)messageData
                toGID:(NSNumber * _Nonnull)destinationGID
              fromGID:(NSNumber * _Nonnull)senderGID
           onResponse:(nullable void (^)(GTResponse * _Nonnull))onResponse
              onError:(nullable void (^)(NSError * _Nullable))onError resendID:(int)resendId;

/**
 Resend Message (with options)
 
 With this you send a single message to another goTenna user. This is the only means of
 sending a message where you'll receive negative or positive confirmation that the receiver
 received your message
 
 NOTE: Must have set goTenna GID before calling this
 NOTE: If your receiver needs to know the sender's GID, you'll need to send it in the payload
 
 @param messageData    The message's data, such as text, preferably formatted in some easily parse-able format.
 @param destinationGID The GID of the user who will receive this private message (must be 15 digits or less and not 111-111-1111).
 @param senderGID      The response listener callback for the command.
 @param onResponse     Called when your goTenna responds with a postive or negative acknowledgement.
 @param onError        Called when an error occurs (See error code for details).
 @param resendId       The id of the message to resend that was returned in the previous @c GTResponse or @c GTError.
 @param maxHopCount    Maximum number of hops this message should make.
 @param willEncrypt    Whether or not we should encrypt the message.
 */
- (void)resendMessage:(NSData * _Nonnull)messageData
                toGID:(NSNumber * _Nonnull)destinationGID
              fromGID:(NSNumber * _Nonnull)senderGID
           onResponse:(nullable void (^)(GTResponse * _Nonnull))onResponse
              onError:(nullable void (^)(NSError * _Nullable))onError
             resendID:(int)resendId
          maxHopCount:(NSUInteger)maxHopCount
          willEncrypt:(BOOL)willEncrypt;

/**
 Resend Broadcast
 
 A broadcast is also referred to as a Shout. This is because every nearby goTenna will received this message.
 Broadcast messages cannot be encrypted, their data is sent as plaintext.
 
 @param messageData The message's data, such as text, preferably formatted in some easily parse-able format.
 @param onResponse  Called when your goTenna responds with a postive or negative acknowledgement.
 @param onError     Called when an error occurs (See error code for details).
 @param resendId    The id of the message to resend that was returned in the previous @c GTResponse or @c GTError.
 */
- (void)resendBroadcast:(NSData * _Nonnull)messageData
             onResponse:(nullable void (^)(GTResponse * _Nonnull))onResponse
                onError:(nullable void (^)(NSError * _Nullable))onError
               resendID:(int)resendId;

/**
 Delete GID
 
 Use to delete Group GIDs from your goTenna. AFter calling this, you should receive no further messages for the
 given GID.
 
 NOTE: if you call this with the goTenna's unique GID, you'll need to call @c setGoTennaGID: before continueing to use
 your goTenna. You do NOT need to call this before updating your goTenna's unique GID.
 
 @param gidToDelete The GID that should be removed from the goTenna.
 @param onError     Called when an error occurs (See error code for details).
 */
- (void)deleteGID:(NSNumber * _Nonnull)gidToDelete onError:(nullable void (^)(NSError * _Nullable))onError;

/**
 Broadcast Message
 
 @param messageData Message data with text 160 characters or less
 @param onResponse  Called on response
 @param onError     Called on error (See error code for details)
 */
- (void)sendBroadcast:(NSData * _Nonnull)messageData
           onResponse:(nullable void (^)(GTResponse * _Nonnull))onResponse
              onError:(nullable void (^)(NSError * _Nullable))onError;

/**
 Emergency Broadcast
 
 @param messageData Message data with text 160 characters or less
 @param onResponse  Called on success
 @param onError     Called on error (See error code for details)
 */
- (void)sendEmergencyBroadcast:(NSData * _Nonnull)messageData
                    onResponse:(nullable void (^)(GTResponse * _Nonnull))onResponse
                       onError:(nullable void (^)(NSError * _Nullable))onError;

/**
 Broadcast Message with Hops
 
 This function is only available to Super SDK users.
 
 @param messageData Message data with text 160 characters or less
 @param hopCount    How many hops you want the shout to travel
 @param onResponse  Called on success
 @param onError     Called on error (See error code for details)
 */
- (void)sendBroadcast:(NSData * _Nonnull)messageData
             hopCount:(NSUInteger)hopCount
           onResponse:(nullable void (^)(GTResponse * _Nonnull))onResponse
              onError:(nullable void (^)(NSError * _Nullable))onError;

/**
 Create Group
 
 Call this method to create a group.
 You must have the unique GIDs for all members of the group.
 When you call this, a one-to-one message is sent to each member of the group notifying them of group creation
 
 NOTE: if the group is large, this method can take a while to process as each message goes out
 
 @param memberGIDs       Cannot include either 1111111111 or 9999999999, other group GIDs, cannot exceed 10 members
 @param onMemberResponse Called for each member response, @c responseCode in @c GTResponse can be used to determine whether receiver received the message
 @param senderGID        Sender's GID
 @param onError          Required. Called on error (See error code for details)
 @return                 Created Group GID
 */
- (NSNumber * _Nonnull)createGroupWithGIDs:(NSArray * _Nonnull)memberGIDs
                          onMemberResponse:(nullable void (^)(GTResponse * _Nonnull, NSNumber * _Nonnull memberGID))onMemberResponse
                                   fromGID:(NSNumber * _Nonnull)senderGID
                                   onError:(nullable void (^)(NSError * _Nullable, NSNumber * _Nullable))onError;

/**
 On Group Created
 
 Set block to perform when receiving a group creation message
 As a member of a created group, you need to know when you've been added to a group. Here,
 you are added to a group
 
 NOTE: you must have called setGotennaGID with your unique GID to receive these messages
 
 @param externalOnGroupCreate Called when you are added to a group. Contains group info
 */
- (void)setOnGroupCreated:(nullable void (^)(GTGroupCreationMessageData * _Nonnull))externalOnGroupCreate;

/**
 Get System Info
 
 @param onSuccess System info response object
 @param onError   Called when an error occurs (See error code for details)
 */
- (void)sendGetSystemInfoOnSuccess:(nullable void (^)(SystemInfoResponseData * _Nonnull))onSuccess
                           onError:(nullable void (^)(NSError * _Nullable))onError;

/**
 Create Multicast Group
 
 Allows the user to create their own multicast group. A multicast group works just like a regular
 group except there is no encryption, and you do not need to know who is in the group to join.
 
 This function is only available to Super SDK users.
 
 @param  multicastGroupGID GID for the multicast group
 @return True if the function ran successfully
 */
- (BOOL)createMulticastGroup:(NSNumber * _Nonnull)multicastGroupGID;

/**
 Set Mesh Geofence Region
 
 @param onResponse Called when the command finishes. See the @c responsePositive property for command success.
 @param onError    Called when an error occurs (See error code for details)
 */
- (void)sendSetGeoRegion:(RegionID)regionID onResponse:(nullable void (^)(GTResponse * _Nonnull))onResponse onError:(nullable void (^)(NSError * _Nullable))onError;

/**
 Get Mesh Geofence Region
 
 @param onResponse Called when the command finishes. See the @c responsePositive property for command success.
 @param onError    Called when an error occurs (See error code for details)
 */
- (void)sendGetGeoRegionOnResponse:(nullable void (^)(GTResponse * _Nonnull))onResponse onError:(nullable void (^)(NSError * _Nullable))onError;

NS_ASSUME_NONNULL_BEGIN
/*
 * SDK methods not for partners
 */
- (void)resetGotenna;
- (void)queueCommand:(GTCommand *)command;
- (void)sendGetMessageRequest;
- (void)abortCurrentCommand;
- (void)dispatchResponse:(NSMutableData *)response;
- (void)sendStoreDateTimeWithEmergencyMessage:(NSString *)emergencyMessage;

// Queue
- (void)queuePriorityCommands:(GTCommandArray *)array;
- (void)pauseQueue;
- (void)nudgeQueue;
- (void)resetQueue;
- (void)sendHardReset;

- (NSArray *)remainingCommands;
- (GTCommand *)currentQueueCommand;

// goTenna v1 only
- (void)startEmergencyBeaconBroadcastOnResponse:(void (^)(GTResponse *response))onResponse onError:(void (^)(NSError *))onError;
- (void)stopEmergencyBeaconBroadcastOnResponse:(void (^)(GTResponse *response))onResponse onError:(void (^)(NSError *))onError;
- (void)getEmergencyBeaconBroadcastStatusOnResponse:(void (^)(BOOL statusReceived))onStatusReceived onError:(void (^)(NSError *))onError;

// Public keys
- (void)sendPublicKeyRequestToGID:(NSNumber *)destinationGID;
- (void)sendPublicKeyResponseToGID:(NSNumber *)destinationGID;
- (void)sendMyMeshPublicKeyToGID:(NSNumber *)receiverGID;

// Key exchange
- (void)addPostKeyExchangeMeshMessageToResend:(GTSendCommand *)sendCommand;
- (void)removePostKeyExchangeMeshMessageFromResend:(GTSendCommand*)sendCommand;
- (BOOL)hasPostKeyExchangeMeshMessagesToResend;

- (NSArray<GTSendCommand *> *)removedKeyExchangeMessagesRetrievalWithGID:(NSNumber *)gid;

// Internal use only
@property (atomic, readonly) NSMutableArray *meshMessageToResendList;
@property (nonatomic, strong) GTResponseDispatcher *responseProcessor;
@property (nonatomic, assign) BOOL shouldBlockKeepAliveGet;

NS_ASSUME_NONNULL_END

@end
