#import <Foundation/Foundation.h>

typedef enum : NSUInteger {
    GTFirmwareWriterFailureStateNone,
    GTFirmwareWriterFailureStateShowRetry,
    GTFirmwareWriterFailureStateSomethingWrong,
    GTFirmwareWriterFailureStateNotConnected
} GTFirmwareWriterFailureState;

@protocol GTFirmwareInstallationProgressProtocol <NSObject>
- (void)initializeComplete;
- (void)finalizeComplete;
- (void)newProgressAmount:(float)progress;
- (void)updateComplete:(double)firmwareVersion;
- (void)updateFailed:(GTFirmwareWriterFailureState)failState version:(double)firmwareVersion;
- (void)updateInitialized;
@end
