//
//  GTMeshGeofence.h
//  GoTenna
//
//  Created by JOSHUA M MAKINDA on 11/14/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <GoTennaSDK/RegionBound.h>

@interface GTMeshGeofence : NSObject

+ (RegionID)lastSavedRegionID;

+ (NSString *)lastSavedRegionName;
+ (NSString *)lastSavedITURegionName;

- (void)geofenceSetFrequencyForLocation:(CLLocationCoordinate2D)location regionFound:(void(^)(RegionID regionID))foundRegion;

@end
