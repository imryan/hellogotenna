//
//  NSString+GTFormatting.h
//  goTenna SDK
//
//  Created by Julietta Yaunches on 16/07/2014.
//  Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (GTFormatting)

+ (NSString *)getStringFromDate:(NSDate *)date;
+ (NSString *)getStringFromDateExtended:(NSDate *)date;
+ (NSString *)pingStringWithDate:(NSDate *)date;

+ (NSString *)presentGID:(NSNumber *)gid;
+ (NSString *)phoneNumberCleaned:(NSString *)gidToClean;

- (NSString *)safeSubstringFromIndex:(NSUInteger)fromIndex;

- (BOOL)isAllDigits;

@end
