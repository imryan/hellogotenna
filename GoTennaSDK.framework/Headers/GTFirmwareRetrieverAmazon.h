//
//  GTFirmwareRetrieverAmazon.h
//  NewiOSTests
//
//  Created by JOSHUA M MAKINDA on 3/3/16.
//  Copyright © 2016 JOSHUA M MAKINDA. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTFirmwareRetrieveProtocol.h"

@interface GTFirmwareRetrieverAmazon : NSObject <GTFirmwareRetrieveProtocol>

- (instancetype)initWithFirmwareAmazonBucket:(const NSString *)bucket;

- (void)retrieveFirmwareWithStorageCompletion:(RetrievalCompletion)retrievalCompletion;

@end
