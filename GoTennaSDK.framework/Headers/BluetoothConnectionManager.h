//
//  BluetoothConnectionManager.h
//  goTenna SDK
//
//  Created by Julietta Yaunches on 30/05/2014.
//  Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@protocol BluetoothPairingProtocol;

// Services
extern NSString * const kGoTennaServiceUUID;
extern NSString * const kGoTennaMeshServiceUUID;

// v1 characteristics
extern NSString * const kGoTennaKeepAliveCharacteristicUUID;
extern NSString * const kGoTennaWriteCharacteristicUUID;
extern NSString * const kGoTennaReadCharacteristicUUID;

// Mesh characteristics
extern NSString * const kGoTennaMeshKeepAliveCharacteristicUUID;
extern NSString * const kGoTennaMeshReadCharacteristicUUID;
extern NSString * const kGoTennaMeshWriteCharacteristicUUID;

// Shared characteristics
extern NSString * const kGoTennaDeviceInformationUUID;
extern NSString * const kGoTennaBluetoothProtocolRevisionCharacteristicUUID;

typedef NS_ENUM(NSInteger, GTDeviceType) {
    GTDeviceTypeGoTenna = 0,
    GTDeviceTypePro,
    GTDeviceTypeMesh
};

@interface BluetoothConnectionManager : NSObject <CBCentralManagerDelegate>

@property (nonatomic, weak) id<BluetoothPairingProtocol> pairingDelegate;
@property (nonatomic, assign) BOOL connectionNotRequired;

+ (instancetype)shared;

- (void)scanAndConnectForDevice:(GTDeviceType)deviceType;
- (void)scanAndConnect;
- (void)stopScan;
- (void)resetCentralManager;
- (void)userDisconnect;

- (BOOL)isConnected;
- (BOOL)isScanning;
- (BOOL)bluetoothOff;

- (GTDeviceType)getDeviceType;
- (void)setDevice:(GTDeviceType)deviceType;

@end
