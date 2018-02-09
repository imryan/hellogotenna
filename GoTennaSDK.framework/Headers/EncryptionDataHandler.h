//
//  EncryptionDataHandler.h
//  goTenna SDK
//
//  Created by JOSHUA M MAKINDA on 1/5/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class TLVSection;
@class DecryptedPayloadData;
@class EncryptionInfoHeader;
@class GTEncryptionInfo;

@interface EncryptionDataHandler : NSObject

+ (GTEncryptionInfo *)createGroupEncryptedMessagePayloadWithGroupGID:(NSNumber *)groupGID
                                                     andSharedSecret:(NSData *)sharedSecret
                                                     andOutgoingData:(NSData *)outgoingData
                                                         receiverGID:(NSNumber *)receiverGID
                                                            resendID:(int)resendId;

+ (GTEncryptionInfo *)createOneToOneEncryptedMessagePayloadWithRemotePublicKey:(NSData *)remotePublicKey
                                                                  outgoingData:(NSData *)outgoingData
                                                                   receiverGID:(NSNumber*)receiverGID
                                                                      resendID:(int)resendId;
;

+ (GTEncryptionInfo *)createPlainMessagePayloadWithOutgoingData:(NSData *)outgoingData
                                                    receiverGID:(NSNumber *)receiverGID
                                                       resendID:(int)resendId;
;


+ (EncryptionInfoHeader *)parseEncryptionInfoHeaderWithMessagePayloadTLV:(TLVSection *)messagePayloadTLV;

+ (DecryptedPayloadData *)decryptMessagePayloadWith:(EncryptionInfoHeader *)encryptionInfoHeader
                               andMessagePayloadTLV:(TLVSection *)messagePayloadTLV
                                        andGroupGID:(NSNumber *)groupGID
                                     isGroupMessage:(BOOL)isGroupMessage;

@end
