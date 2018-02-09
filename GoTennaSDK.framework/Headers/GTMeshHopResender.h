//
//  GTMeshHopResender.h
//  goTenna SDK
//
//  Created by Ryan Cohen on 4/4/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTDataTypes.h"

@class GTCommand;

@interface GTMeshHopResender : NSObject

/**
 Shared instance of the class
 */
+ (instancetype)sharedInstance;

/**
 Resends the message with max hop count
 */
- (void)resendMessageWithMoreMaxHops:(GTCommand *)command;

/**
 Returns true if the message should be sent with max hop count
 */
- (BOOL)shouldResendMessageWithMoreMaxHops:(GTCommand *)command responseType:(GTCommandResponseType)responseType;

@end
