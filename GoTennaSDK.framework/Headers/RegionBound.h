//
//  RegionBound.h
//  goTenna
//
//  Created by JOSHUA M MAKINDA on 11/15/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>

typedef enum : NSUInteger {
    NONE,
    NORTH_AMERICA,
    EUROPE,
    SOUTH_AFRICA,
    AUSTRALIA,
    NEW_ZEALAND,
    SINGAPORE,
    TAIWAN,
    JAPAN,
    HONGKONG,
    SOUTH_KOREA,
    
    /* ITU Regions */
    ITU_1,
    ITU_2,
    ITU_3,
    ITU_3_EXT
} RegionID;

@interface RegionBound : NSObject

@property (nonatomic, readonly) RegionID regionID;

/**
 Returns region bound for given region ID
 */
+ (instancetype)regionBoundForRegionID:(RegionID)regionID;

/**
 Returns region name for given region ID
 */
+ (NSString *)regionNameFromId:(RegionID)regionID;

/**
 Returns all ITU regions
 */
+ (NSArray<RegionBound *> *)ituRegions;

/**
 Returns all countries
 */
+ (NSArray<RegionBound *> *)allRegions;

/**
 Returns true if the location is within the region
 */
- (BOOL)regionBoundContainsPoint:(CLLocationCoordinate2D)location;

@end
