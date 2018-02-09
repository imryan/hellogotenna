//
// Created by Julietta Yaunches on 5/06/2014.
// goTenna SDK
//

#import <Foundation/Foundation.h>

@class GTPacketPreparer;
@class GTPacket;
@class GTCommand;
@class GTCommandArray;
@class GTSendCommand;

@interface GTCommandQueue : NSObject

@property (nonatomic, strong) GTCommand *currentCommand;

- (void)queueGTCommand:(GTCommand *)command;
- (void)queueGTCommands:(GTCommandArray *)incomingCommands;

- (void)nudgeToNextCommand;
- (void)empty;
- (void)pauseQueue;
- (void)executeUpcomingCommand;

- (NSArray<GTSendCommand *> *)removeKeyExchangeRequestsForGID:(NSNumber *)gid;
- (NSArray *)remainingCommands;

@end
