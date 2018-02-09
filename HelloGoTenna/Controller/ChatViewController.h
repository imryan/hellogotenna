//
//  ChatViewController.h
//  HelloGoTenna
//
//  Created by Ryan Cohen on 7/26/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GoTennaSDK/GTDataTypes.h>

@class Group;

@interface ChatViewController : UIViewController

@property (nonatomic, strong) Group *group;
@property (nonatomic, assign) GTGIDType conversationType;

@end
