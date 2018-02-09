//
//  GTFirmwareRetrieveProtocol.h
//  goTenna SDK
//

#import <Foundation/Foundation.h>

typedef void (^RetrievalCompletion)();

@protocol GTFirmwareRetrieveProtocol <NSObject>

- (void)retrieveFirmwareWithStorageCompletion:(RetrievalCompletion)retrievalCompletion;

@end
