//
// Created by Julietta Yaunches on 11/18/14.
// Copyright (c) 2014 goTenna-inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTBaseMessageData.h"
#import "GTMessageDataProtocol.h"

@interface GTLocationRequestOnlyMessageData : GTBaseMessageData <GTMessageDataProtocol>

- (instancetype)initWithReceiverGID:(NSNumber *)receiverGID onError:(NSError **)pError;

@end
