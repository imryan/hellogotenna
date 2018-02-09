//
//  GroupCreateViewController.m
//  HelloGoTenna
//
//  Created by Ryan Cohen on 7/26/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import "GroupCreateViewController.h"
#import <GoTennaSDK/GoTennaSDK.h>
#import "ChatViewController.h"
#import "ContactManager.h"

const int MIN_GROUP_MEMBERS = 1;

@interface GroupCreateViewController ()

@property (nonatomic, weak) IBOutlet UITableView *tableView;

@property (nonatomic, strong) NSMutableArray<Contact *> *recipients;
@property (nonatomic, assign) NSUInteger memberResponseCount;
@property (nonatomic, strong) NSNumber *groupGID;
@property (nonatomic, strong) Group *group;

@end

@implementation GroupCreateViewController

# pragma mark - Functions

- (void)sendGroupInvites {
    [self resetGroupInvitationState];
    
    self.groupGID = [[GTCommandCenter shared] createGroupWithGIDs:[self memberGIDArray] onMemberResponse:^(GTResponse *response, NSNumber *memberGID) {
        [self receivedMemberResponseForGID:memberGID found:[response responsePositive]];
        
    } fromGID:[[UserDataStore shared] currentUser].gId onError:^(NSError *error, NSNumber *memberGID) {
        [self receivedMemberResponseForGID:memberGID found:NO];
    }];
}

- (void)receivedMemberResponseForGID:(NSNumber *)gid found:(BOOL)found {
    self.memberResponseCount++;
    
    [self updateInvitationState:(found ? GroupInvitationStateReceived : GroupInvitationStateNotReceived) contactGID:gid];
    
    if (self.memberResponseCount == [self.recipients count]) {
        UITableViewCell *cell = [self.tableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:1]];
        cell.userInteractionEnabled = YES;
        
        self.group = [[Group alloc] initWithGID:self.groupGID groupMembers:self.recipients];
        [self reloadSendGroupMessageCell];
    }
    
    [self reloadRecipients];
}

# pragma mark - UITableView

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 2;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return (section == 0) ? [self.recipients count] : 1;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    return (section == 0) ? @"Recipients" : nil;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"CellId" forIndexPath:indexPath];
    return [self configureCell:cell forIndexPath:indexPath];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    if (indexPath.section == 1) {
        if (self.group != nil) {
            [self performSegueWithIdentifier:@"ToChat" sender:self];
        } else {
            [self sendGroupInvites];
            
            UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
            cell.userInteractionEnabled = NO;
        }
    }
    
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

# pragma mark - Helpers

- (void)reloadRecipients {
    [self.tableView beginUpdates];
    [self.tableView reloadSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationAutomatic];
    [self.tableView endUpdates];
}

- (void)reloadSendGroupMessageCell {
    [self.tableView beginUpdates];
    [self.tableView reloadSections:[NSIndexSet indexSetWithIndex:1] withRowAnimation:UITableViewRowAnimationAutomatic];
    [self.tableView endUpdates];
}

- (void)resetGroupInvitationState {
    for (Contact *contact in self.recipients) {
        contact.invitationState = GroupInvitationStateSending;
    }
    
    self.memberResponseCount = 0;
    
    [self reloadRecipients];
}

- (void)updateInvitationState:(GroupInvitationState)state contactGID:(NSNumber *)contactGID {
    for (Contact *contact in self.recipients) {
        if ([contact.gid isEqualToNumber:contactGID]) {
            contact.invitationState = state;
            break;
        }
    }
}

- (UITableViewCell *)configureCell:(UITableViewCell *)cell forIndexPath:(NSIndexPath *)indexPath {
    if (indexPath.section == 0) {
        Contact *contact = self.recipients[indexPath.row];
        
        cell.textLabel.text = contact.name;
        cell.detailTextLabel.text = [contact invitationStateString];
        cell.accessoryType = UITableViewCellAccessoryNone;
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
        
        return cell;
    }
    
    cell.textLabel.text = (self.group != nil) ? @"Send Message to Group" : @"Send Invites";
    cell.detailTextLabel.text = nil;
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    
    return cell;
}

- (NSArray<NSNumber *> *)memberGIDArray {
    NSMutableArray *memberGIDs = [NSMutableArray arrayWithCapacity:self.recipients.count];
    
    for (Contact *contact in self.recipients) {
        [memberGIDs addObject:contact.gid];
    }
    
    return memberGIDs;
}

# pragma mark - Navigation

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"ToChat"]) {
        ChatViewController *chatViewController = (ChatViewController *)[segue destinationViewController];
        chatViewController.conversationType = GroupGID;
        chatViewController.group = self.group;
    }
}

# pragma mark - Lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.recipients = [[[ContactManager sharedManager] allDemoContactsExcludingSelf] mutableCopy];
    self.group = nil;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
