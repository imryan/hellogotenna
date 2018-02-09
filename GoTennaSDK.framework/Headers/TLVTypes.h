//
//  TLVTypes.h
//  GoTenna
//
//  Created by JOSHUA M MAKINDA on 12/14/15.
//  Copyright © 2015 goTenna. All rights reserved.
//

extern NSNumber *TLV_TYPE_MESSAGE_TYPE;
extern NSNumber *TLV_TYPE_SENDER_INITIALS;

extern NSNumber *TLV_TYPE_TEXT;
extern NSNumber *TLV_TYPE_RECEIVING_GID;
extern NSNumber *TLV_TYPE_LOCATION_MESSAGE_DATA;

// LocationMessageData
extern NSNumber *location_offset;
extern NSNumber *TLV_TYPE_LOCATION_NAME;
extern NSNumber *TLV_TYPE_LOCATION_LATITUDE;
extern NSNumber *TLV_TYPE_LOCATION_LONGITUDE;
extern NSNumber *TLV_TYPE_LOCATION_TYPE;
extern NSNumber *TLV_TYPE_LOCATION_GPS_TIMESTAMP;

// GroupCreationMessageData
extern NSNumber *TLV_TYPE_GROUP_GID;
extern NSNumber *TLV_TYPE_GROUP_MEMBER_LIST;
extern NSNumber *TLV_TYPE_GROUP_SHARED_SECRET;

// For Message Resending
extern NSNumber *TLV_TYPE_MESSAGE_ID;

// For Public Key Exchange
extern NSNumber *TLV_TYPE_PUBLIC_KEY_DATA;

// For extended TLV sections
extern NSNumber *TLV_TYPE_ENCRYPTION_INFO;
extern NSNumber *TLV_TYPE_EXTENDER_JACKET_2B;
extern NSNumber *TLV_TYPE_EXTENDER_JACKET_3B;
extern NSNumber *TLV_TYPE_EXTENDER_JACKET_4B;
