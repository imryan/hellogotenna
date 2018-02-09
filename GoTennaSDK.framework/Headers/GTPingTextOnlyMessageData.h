//
//  GTPingTextOnlyMessageData.h
//  goTenna SDK
//
//  Created by JOSHUA M MAKINDA on 10/1/15.
//  Copyright (c) 2015 goTenna. All rights reserved.
//

#import "GTTextOnlyMessageData.h"

@interface GTPingTextOnlyMessageData : GTTextOnlyMessageData

- (instancetype)initOutgoingWithText:(NSString *)text onError:(NSError **)error;

@end
