//
//  GTFirmwareRetrieverFactory.h
//  goTenna SDK
//

#import <Foundation/Foundation.h>
#import "GTFirmwareRetrieveProtocol.h"

@interface GTFirmwareRetrieverFactory : NSObject

/**
*  Create instance of firmware retriever using Amazon Web Services
*
*  @return Object that conforms to the GTFirmwareRetrieveProtocol
*/
+ (id<GTFirmwareRetrieveProtocol>)firmwareRetrieverAmazon;

@end
