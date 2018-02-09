//
// Created by Julietta Yaunches on 9/09/2014.
// goTenna SDK
//

@class GTResponse;
@class GTCommand;
@class GTSendCommand;

#import <Foundation/Foundation.h>

@interface GTResponseDispatcher : NSObject

- (void)processResponse:(GTResponse *)response forCommand:(GTCommand *)command;
- (void)processMeshAckResponse:(GTResponse *)response forSendCommand:(GTSendCommand *)sendCommand;

@end
