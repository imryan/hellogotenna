//
//  GTLogExportProtocol.h
//  goTenna SDK
//
//  Created by Julietta Yaunches on 6/24/15.
//  Copyright (c) 2015 goTenna. All rights reserved.
//

@protocol GTLogExportProtocol <NSObject>

- (NSString *)directory;
- (NSString *)filename;
- (NSString *)subject;
- (NSString *)logDestinationEmail;

- (void)truncateLog;
- (void)writeQueued;

@end
