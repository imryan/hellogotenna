//
//  SecurityManager.h
//  ACBluetoothChat
//
//  Created by alexchoi on 2/14/14.
//  Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

static const NSString * PersonalPublicKeyIdentifier = @"com.gotenna.chat.publickey\0";


@interface SecurityManager : NSObject


+ (void)generatePersonalKeyPairPlease; /// make personal private and public key pair for the user
+ (NSData *) dataForPersonalPublicKey;    //// returns nsdata form of user's personal public key
+ (NSData *) hashDataForPersonalPublicKey; /// first byte of nsdata of user's personal public key
+ (NSData *) dataForPublicKey:(NSString *) publicKeyIdentifier;  /// nsdata for any stored public key
+ (NSData *) hashDataForPublicKey: (NSString *) publicKeyIdentifier;  /// first byte of nsdata of any stored public key
+ (SecKeyRef) savePublicKey:(NSData *) publicKeyData withIdentifier:(NSString *) identifier; /// for storing friends' public key
+ (NSData *) encryptData:(NSData *) unencryptedData withPublicKey:(NSString *) publicKeyIdentifier; /// to replace method below
+ (NSData *) decryptData:(NSData *) encryptedData withPrivateKey:(NSString *) privateKeyIdentifier; /// decrypt with a stored private key, ie group message key
+ (NSData *)decryptDataWithPersonalPrivateKey: (NSData *)dataToDecrypt; /// decrypt with current personal private key



@end
