//
// Created by Julietta Yaunches on 30/05/2014.
// goTenna SDK
//


#import <Foundation/Foundation.h>
#import "GTResponse.h"

@interface GTResponseDataWrapper : NSObject

@property (nonatomic, strong) NSData *cleanedData;

- (instancetype)initWithChunks:(NSData *)data;

- (NSNumber *)extractSequenceNumber;
- (NSData *)extractChecksum:(NSData *)data;
- (NSData *)extractMessageData;
- (NSUInteger)extractHopCount;

- (BOOL)responseTypeIs:(const char *)response;

@end
