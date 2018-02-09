#import <Foundation/Foundation.h>

@interface NSData (GTHelper)

+ (NSData *)swapInt:(unsigned int)theInt toByteLength:(NSUInteger)length;

- (NSArray *)splitDataByLength:(NSUInteger)unit;

- (void)safeGetBytes:(unsigned char *)string range:(NSRange)range;

- (NSData *)safeSubData:(NSUInteger)position withLength:(NSInteger)length;

- (NSString *)hexString;

@end
