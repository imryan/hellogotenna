//
//  ViewController.m
//  HelloGoTenna
//
//  Created by Ryan Cohen on 7/20/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import "ViewController.h"
#import "ChatViewController.h"
#import "GroupCreateViewController.h"
#import "ContactManager.h"
#import "MessagingManager.h"
#import "FirmwareManager.h"

@import GoTennaSDK;

NSString * const kGroupWasCreatedNotification = @"kGroupCreatedNotification";

@interface ViewController () <GTPairingHandlerProtocol, BluetoothPairingProtocol, FirmwareManagerProtocol>

@property (nonatomic, weak) IBOutlet UITableView *tableView;
@property (nonatomic, weak) IBOutlet UIBarButtonItem *connectBarItem;

@property (nonatomic, strong) FirmwareManager *firmwareManager;
@property (nonatomic, strong) NSString *firmwareUpdateStatus;
@property (nonatomic, strong) Group *selectedGroup;

@end

@implementation ViewController

# pragma mark - Actions

- (IBAction)connect:(id)sender {
    if ([self.connectBarItem.title isEqualToString:@"Disconnect"]) {
        [self disconnectFromGoTenna];
    } else {
        [self scanForNewGoTenna];
        self.connectBarItem.title = @"Disconnect";
    }
}

- (void)scanForNewGoTenna {
    [[GTPairingManager shared] setShouldReconnect:YES];
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:[GTConfig forgetThisDeviceKey]];
    
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"GoTenna"
                                                                   message:@"Select a device to scan for."
                                                            preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction *v1 = [UIAlertAction actionWithTitle:@"goTenna v1" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        [[BluetoothConnectionManager shared] setDevice:GTDeviceTypeGoTenna];
        [[GTPairingManager shared] initiateScanningConnect];
    }];
    
    UIAlertAction *mesh = [UIAlertAction actionWithTitle:@"goTenna Mesh" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        [[BluetoothConnectionManager shared] setDevice:GTDeviceTypeMesh];
        [[GTPairingManager shared] initiateScanningConnect];
    }];
    
    [alert addAction:v1];
    [alert addAction:mesh];
    
    [self presentViewController:alert animated:YES completion:nil];
    
    self.connectBarItem.title = @"Connect";
    self.connectBarItem.enabled = NO;
}

- (void)disconnectFromGoTenna {
    [[GTPairingManager shared] setShouldReconnect:NO];
    [[GTPairingManager shared] initiateDisconnect];
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:[GTConfig forgetThisDeviceKey]];
    
    self.connectBarItem.title = @"Connect";
    self.connectBarItem.enabled = YES;
    self.tableView.userInteractionEnabled = NO;
}

- (void)chooseDemoUser {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Set Name & GID"
                                                                   message:@"Select a demo user"
                                                            preferredStyle:UIAlertControllerStyleAlert];
    
    for (Contact *contact in [[ContactManager sharedManager] allDemoContacts]) {
        NSString *title = [NSString stringWithFormat:@"%@ (%@)", contact.name, contact.gid.stringValue];
        
        UIAlertAction *action = [UIAlertAction actionWithTitle:title style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
            [self sendSetGID:contact.gid name:contact.name withBlock:^(BOOL success) {
                if (success) {
                    self.connectBarItem.enabled = YES;
                    self.tableView.userInteractionEnabled = YES;
                    
                    [self reloadSection:0];
                }
            }];
        }];
        
        [alert addAction:action];
    }
    
    UIAlertAction *cancel = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:nil];
    [alert addAction:cancel];
    
    [self presentViewController:alert animated:YES completion:nil];
}

- (void)chooseGroup {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Group"
                                                                   message:@"Select a group"
                                                            preferredStyle:UIAlertControllerStyleAlert];
    
    
    
    for (Group *group in [[ContactManager sharedManager] allGroups]) {
        NSString *title = [NSString stringWithFormat:@"%@ (%lu members)", group.groupGID, (unsigned long)group.groupMembers.count];
        
        UIAlertAction *action = [UIAlertAction actionWithTitle:title style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
            self.selectedGroup = group;
            [self performSegueWithIdentifier:@"ChatSegue" sender:@(GroupGID)];
        }];
        
        [alert addAction:action];
    }
    
    UIAlertAction *cancel = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:nil];
    [alert addAction:cancel];
    
    [self presentViewController:alert animated:YES completion:nil];
}

# pragma mark - Device Actions

- (void)sendEchoWithBlock:(void (^)(BOOL success))block {
    [[GTCommandCenter shared] sendEchoCommand:^(GTResponse *response) {
        block(response.responsePositive);
    } onError:^(NSError *error) {
        NSLog(@"[GoTenna] Error %@ %@", NSStringFromSelector(_cmd), error.localizedDescription);
        block(NO);
    }];
}

- (void)sendGetSystemInfoWithBlock:(void (^)(NSString *systemInfoDescription))block {
    [[GTCommandCenter shared] sendGetSystemInfoOnSuccess:^(SystemInfoResponseData *response) {
        block([response asString]);
    } onError:^(NSError *error) {
        NSLog(@"[GoTenna] Error %@ %@", NSStringFromSelector(_cmd), error.localizedDescription);
        block(nil);
    }];
}

- (void)sendSetGID:(NSNumber *)gid name:(NSString *)name withBlock:(void (^)(BOOL success))block {
    [[GTCommandCenter shared] setgoTennaGID:gid withUsername:name onError:^(NSError *error) {
        if (error) {
            NSLog(@"[GoTenna] Error %@ %@", NSStringFromSelector(_cmd), error.localizedDescription);
            block(NO);
        }
    }];
    
    block(YES);
}

# pragma mark - GTPairingHandlerProtocol

- (void)updateState:(GTConnectionState)state {
    switch (state) {
        case Disconnected:
            NSLog(@"[GoTenna] State: Disconnected");
            break;
        case Connecting:
            NSLog(@"[GoTenna] State: Connecting");
            break;
        case Connected:
            NSLog(@"[GoTenna] State: Connected");
            
            if (![[UserDataStore shared] currentUser]) {
                [self chooseDemoUser];
            } else {
                self.connectBarItem.enabled = YES;
                self.tableView.userInteractionEnabled = YES;
                
                // Ensure GID has been set to current device
                if ([[UserDataStore shared] currentUser]) {
                    [self sendSetGID:[[UserDataStore shared] currentUser].gId name:[[UserDataStore shared] currentUser].name withBlock:^(BOOL success) {
                        if (!success) {
                            [self showAlertWithTitle:@"Error" message:@"Failed to send set GID command."];
                        }
                    }];
                }
            }
            break;
    }
}

# pragma mark - FirmwareManagerProtocol

- (void)firmwareManager:(FirmwareManager *)firmwareManager didUpdateState:(FirmwareUpdateState)state progress:(float)progress {
    NSString *stateString = nil;
    
    switch (state) {
        case UpdateInitialized:
            stateString = @"Initialized";
            break;
        case UpdateInitializeComplete:
            stateString = @"Initialize complete";
            break;
        case UpdateProgressChanged:
            stateString = [NSString stringWithFormat:@"%d%%", (int)(progress * 100)];
            break;
        case UpdateFinalizeComplete:
            stateString = @"Finalize complete";
            break;
        case UpdateSucceeded:
            stateString = @"Succeeded";
            break;
        case UpdateFailed:
            stateString = @"Failed";
            break;
    }
    
    self.firmwareUpdateStatus = stateString;
    [self reloadSection:3];
}

# pragma mark - BluetoothPairingProtocol

- (void)bluetoothPoweredOn {
    // Bluetooth enabled
}

- (void)didConnectToPeripheral {
    // Connected to device
}

- (void)canNotConnectToPeripheral {
    // Could not connect to device
    [self showAlertWithTitle:@"GoTenna" message:@"Could not connect to your device."];
}

- (void)bluetoothConnectionNotAvailable:(CBManagerState)state {
    // Bluetooth is off
    [self showAlertWithTitle:@"GoTenna" message:@"Enable Bluetooth to scan for a device."];
}

- (void)nonUserDisconnectionOccurred {
    // Device disconnected
    [self showAlertWithTitle:@"GoTenna" message:@"Your device was disconnected."];
}

# pragma mark - UITableView

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 4;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    NSUInteger rows = 0;
    
    if (section == 0) {
        rows = 2;
    } else if (section == 1) {
        rows = 3;
    } else if (section == 2) {
        rows = 4;
    } else {
        rows = 1;
    }
    
    return rows;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    NSString *title = nil;
    
    if (section == 0) {
        title = @"You";
    } else if (section == 1) {
        title = @"Device";
    } else if (section == 2) {
        title = @"Messaging";
    } else {
        title = @"Firmware";
    }
    
    return title;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *cellId = @"CellId";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellId forIndexPath:indexPath];
    
    return [self configureCell:cell forIndexPath:indexPath];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [self handleActionForIndexPath:indexPath];
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

# pragma mark - Helpers

- (UITableViewCell *)configureCell:(UITableViewCell *)cell forIndexPath:(NSIndexPath *)indexPath {
    NSString *key = nil, *value = nil;
    
    // Name & GID
    if (indexPath.section == 0) {
        switch (indexPath.row) {
            case 0:
                key = @"Name";
                value = [[UserDataStore shared] currentUser].name ?: @"None";
                break;
            case 1:
                key = @"GID";
                value = [NSString presentGID:[[UserDataStore shared] currentUser].gId] ?: @"None";
                break;
        }
    }
    
    // Send Echo, Set System Info, Set GID
    else if (indexPath.section == 1) {
        switch (indexPath.row) {
            case 0:
                key = @"Send Echo";
                break;
            case 1:
                key = @"Send Get System Info";
                break;
            case 2:
                key = @"Set GID";
                break;
        }
    }
    
    // Send Private, Broadcast, Group Messages
    else if (indexPath.section == 2) {
        switch (indexPath.row) {
            case 0:
                key = @"Send Broadcast Message";
                break;
            case 1:
                key = @"Send Private Message";
                break;
            case 2:
                key = @"Create Group";
                break;
            case 3:
                key = @"Send Group Message";
                break;
        }
    }
    
    // Update Firmware
    else {
        switch (indexPath.row) {
            case 0:
                key = @"Update Firmware";
                value = self.firmwareUpdateStatus;
                break;
        }
    }
    
    cell.textLabel.text = key;
    cell.detailTextLabel.text = value;
    
    cell.accessoryType  = (value) ? UITableViewCellAccessoryNone : UITableViewCellAccessoryDisclosureIndicator;
    cell.selectionStyle = (value) ? UITableViewCellSelectionStyleNone : UITableViewCellSelectionStyleDefault;
    
    return cell;
}

- (void)handleActionForIndexPath:(NSIndexPath *)indexPath {
    // Device
    if (indexPath.section == 1) {
        if (indexPath.row == 0) {
            [self sendEchoWithBlock:^(BOOL success) {
                // ...
            }];
        }
        else if (indexPath.row == 1) {
            [self sendGetSystemInfoWithBlock:^(NSString *systemInfoDescription) {
                [self showAlertWithTitle:@"System Info" message:systemInfoDescription];
            }];
        } else {
            [self chooseDemoUser];
        }
    }
    
    // Messaging
    else if (indexPath.section == 2) {
        GTGIDType conversationType = ShoutGID;
        
        switch (indexPath.row) {
            case 0:
                conversationType = ShoutGID;
                break;
            case 1:
                conversationType = OneToOneGID;
                break;
            case 2: {
                [self performSegueWithIdentifier:@"ToGroupCreate" sender:nil];
                return;
            }
                break;
            case 3: {
                conversationType = GroupGID;
                [self chooseGroup];
                return;
            }
                break;
        }
        
        [self performSegueWithIdentifier:@"ChatSegue" sender:@(conversationType)];
    }
    
    // Update Firmware
    else {
        if (indexPath.section == 3 && indexPath.row == 0) {
            [self promptFirmwareUpdate];
        }
    }
}

- (void)reloadSection:(NSUInteger)section {
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.tableView beginUpdates];
        [self.tableView reloadSections:[NSIndexSet indexSetWithIndex:section] withRowAnimation:UITableViewRowAnimationAutomatic];
        [self.tableView endUpdates];
    });
}

- (void)handleGroupCreated:(NSNotification *)notification {
    if (notification.name == kGroupWasCreatedNotification) {
        Group *group = notification.userInfo[@"group"];
        NSString *message = [NSString stringWithFormat:@"You were added to a group along with %lu others.", (unsigned long)[group.groupMembers count] - 1];
        
        [self showAlertWithTitle:@"Added to Group" message:message];
    }
}

- (void)showAlertWithTitle:(NSString *)title message:(NSString *)message {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:title message:message preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *dismiss = [UIAlertAction actionWithTitle:@"Dismiss" style:UIAlertActionStyleDefault handler:nil];
    
    [alert addAction:dismiss];
    [self presentViewController:alert animated:YES completion:nil];
}

- (void)promptFirmwareUpdate {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Firmware update" message:@"Are you sure you'd like to update your device's firmware?" preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction *confirm = [UIAlertAction actionWithTitle:@"Begin update" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        self.firmwareManager = [[FirmwareManager alloc] initWithDelegate:self];
        
        if (![self.firmwareManager isUpdatingFirmware]) {
            [self.firmwareManager beginFirmwareUpdate];
        }
    }];
    
    UIAlertAction *dismiss = [UIAlertAction actionWithTitle:@"Dismiss" style:UIAlertActionStyleCancel handler:nil];
    
    [alert addAction:confirm];
    [alert addAction:dismiss];
    
    [self presentViewController:alert animated:YES completion:nil];
}

# pragma mark - Navigation

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"ChatSegue"])  {
        ChatViewController *chatViewController = (ChatViewController *)[segue destinationViewController];
        GTGIDType conversationType = [(NSNumber *)sender intValue];
        
        chatViewController.conversationType = conversationType;
        chatViewController.group = self.selectedGroup;
    }
}

# pragma mark - Lifecycle

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleGroupCreated:) name:kGroupWasCreatedNotification object:nil];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Assign pairing handler
    [[GTPairingManager shared] setPairingHandler:self];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
