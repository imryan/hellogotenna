//
//  FirmwareManager.m
//  HelloGoTenna
//
//  Created by Ryan Cohen on 8/1/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import "FirmwareManager.h"
#import <GoTennaSDK/GoTennaSDK.h>

@interface FirmwareManager () <GTFirmwareInstallationProgressProtocol>

@property (nonatomic, weak) id<FirmwareManagerProtocol> delegate;
@property (nonatomic, assign) FirmwareUpdateState state;

@end

@implementation FirmwareManager

# pragma mark - Init

- (instancetype)initWithDelegate:(id<FirmwareManagerProtocol>)delegate {
    self = [super init];
    
    if (self) {
        if (delegate) {
            _delegate = delegate;
        }
    }
    
    return self;
}

# pragma mark - Functions

- (void)beginFirmwareUpdate {
    id<GTFirmwareRetrieveProtocol> retriever = [GTFirmwareRetrieverFactory firmwareRetrieverAmazon];
    
    [[GTFirmwareDownloadTaskManager manager] retrieveAndStoreFirmwareUsingRetriever:retriever onCompletion:^{
        [[GTFirmwareDownloadTaskManager manager] downloadLastRetrievedFirmwareWithProgressDelegate:self];
    }];
}

- (BOOL)isUpdatingFirmware {
    return [[GTFirmwareDownloadTaskManager manager] isInstallingFirmware];
}

- (void)updateState:(FirmwareUpdateState)state {
    if ([self.delegate respondsToSelector:@selector(firmwareManager:didUpdateState:progress:)]) {
        [self.delegate firmwareManager:self didUpdateState:state progress:0.f];
    }
}

- (void)updateStateWithProgress:(float)progress {
    if ([self.delegate respondsToSelector:@selector(firmwareManager:didUpdateState:progress:)]) {
        [self.delegate firmwareManager:self didUpdateState:UpdateProgressChanged progress:progress];
    }
}

# pragma mark - GTFirmwareInstallationProgressProtocol

- (void)updateInitialized {
    [self updateState:UpdateInitialized];
}

- (void)initializeComplete {
    [self updateState:UpdateInitializeComplete];
}

- (void)finalizeComplete {
    [self updateState:UpdateFinalizeComplete];
}

- (void)newProgressAmount:(float)progress {
    [self updateStateWithProgress:progress];
}

- (void)updateComplete:(double)firmwareVersion {
    [self updateState:UpdateSucceeded];
}

- (void)updateFailed:(GTFirmwareWriterFailureState)failState version:(double)firmwareVersion {
    [self updateState:UpdateFailed];
}

@end
