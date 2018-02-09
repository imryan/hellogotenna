//
// Created by Julietta Yaunches on 21/10/2014.
// Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GTUserDefaults : NSObject

+ (void)enableShouts:(BOOL)on;
+ (void)activateAntennaSweep:(BOOL)on;
+ (void)setAppJustCrashed:(BOOL)value;
+ (void)setEncryptionEnabled:(BOOL)enabled;

+ (BOOL)appJustCrashed;
+ (BOOL)acceptingShouts;
+ (BOOL)encryptionEnabled;
+ (BOOL)antennaSweepActivated;

@end
