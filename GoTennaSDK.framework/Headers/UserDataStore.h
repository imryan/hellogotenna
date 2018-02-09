//
//  UserDataStore.h
//  goTenna SDK
//

#import <Foundation/Foundation.h>

@class User;
@class CLLocation;
@class GTSecurityService;

@interface UserDataStore : NSObject

+ (instancetype)shared;

- (User *)currentUser;
- (User *)registerUserWithName:(NSString *)username andGid:(NSNumber *)gid;

- (void)deleteUser;

- (void)addMulticastGID:(NSNumber *)number;
- (void)deleteMulticastGID:(NSNumber *)number;
- (BOOL)hasMulticastGID:(NSNumber *)number;

- (void)addGroupGID:(NSNumber *)number;
- (void)deleteGroupGID:(NSNumber *)number;

- (BOOL)saveUser:(User *)user;
- (BOOL)isMyGID:(NSNumber *)gid;
- (BOOL)userIsLoggedIn;
- (BOOL)hasValidUser;
- (BOOL)userIsUpdatingFirmware;

// Private
- (void)markOnboardingProcessCompleted;
- (BOOL)userHasOnboarded;
- (BOOL)userFinishedOnboardingProcess;

@end
