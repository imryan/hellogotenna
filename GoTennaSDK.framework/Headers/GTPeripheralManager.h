//
// goTenna SDK
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@class ChunkProcessor;
@class GTPacket;
@class GTCommand;
@class GTKeepAliveProcessor;

@interface GTPeripheralManager : NSObject <CBPeripheralDelegate>

@property (nonatomic, strong) CBPeripheral *peripheral;

+ (GTPeripheralManager *)shared;

- (void)updatePeripheral:(CBPeripheral *)peripheral;
- (void)writeCommandPackets:(GTCommand *)command;
- (BOOL)peripheralIsConnected;

- (void)scanPeripheralServices:(void (^)())onCharacteristicsReceived;

@end
