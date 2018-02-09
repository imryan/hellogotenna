//
//  GTMeshPublicKeyResponseMessageData.h
//  goTenna SDK
//
//  Created by JOSHUA M MAKINDA on 2/6/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTMessageDataProtocol.h"
#import "GTBaseMessageData.h"

@interface GTMeshPublicKeyResponseMessageData : GTBaseMessageData <GTMessageDataProtocol>

@property (nonatomic, readonly) NSData *publicKey;

- (instancetype)initOutgoingWithPublicKey:(NSData *)publicKey onError:(NSError **)error;

@end
