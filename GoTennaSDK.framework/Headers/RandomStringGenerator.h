//
//  RandomStringGenerator.h
//  goTenna SDK
//
//  Created by Thomas Colligan on 8/24/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RandomStringGenerator : NSObject

+ (NSString *)generateRandomStringWithLength:(int)length;

@end
