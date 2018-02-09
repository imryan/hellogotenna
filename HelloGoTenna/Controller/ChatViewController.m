//
//  ChatViewController.m
//  HelloGoTenna
//
//  Created by Ryan Cohen on 7/26/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import "ChatViewController.h"
#import "ContactManager.h"
#import "MessagingManager.h"
#import "QueueManager.h"

#import "ChatTableDataSource.h"

@import GoTennaSDK;

@interface ChatViewController () <MessagingManagerProtocol, QueueManagerProtocol, ChatTableProtocol, UITextFieldDelegate>

@property (nonatomic, weak) IBOutlet UITableView *tableView;

@property (nonatomic, strong) ChatTableDataSource *dataSource;
@property (nonatomic, strong) NSNumber *receivingGID;
@property (nonatomic, assign) BOOL shouldDisplayRecipients;

@end

@implementation ChatViewController

# pragma mark - Actions

- (void)insertMessage:(Message *)message {
    BOOL isShout = ([message.receiverGID isEqualToNumber:[GIDManager shoutGID]]);
    GTGIDType type = (isShout) ? ShoutGID : (self.conversationType == GroupGID && self.group ? GroupGID : OneToOneGID);
    
    if (self.conversationType != type) return;
    
    if (message) {
        [self.dataSource addMessage:message];
        [self reloadTable];
    }
}

- (void)sendMessage {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:self.title
                                                                   message:@"Send a message"
                                                            preferredStyle:UIAlertControllerStyleAlert];
    
    [alert addTextFieldWithConfigurationHandler:^(UITextField *textField) {
        textField.placeholder = @"Write your message";
        textField.autocapitalizationType = UITextAutocapitalizationTypeSentences;
        textField.delegate = self;
    }];
    
    UIAlertAction *action = [UIAlertAction actionWithTitle:@"Send" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        NSString *text = alert.textFields[0].text;
        [self sendMessage:text forConversationType:self.conversationType];
    }];
    
    UIAlertAction *dismiss = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:nil];
    
    [alert addAction:action];
    [alert addAction:dismiss];
    
    [self presentViewController:alert animated:YES completion:nil];
}

- (void)sendMessage:(NSString *)text forConversationType:(GTGIDType)conversationType {
    if (conversationType == GroupGID) {
        self.receivingGID = [self.group groupGID];
    }
    
    Message *outgoingMessage = [[Message alloc] initWithText:text
                                                   senderGID:[[UserDataStore shared] currentUser].gId
                                                 receiverGID:self.receivingGID];
    
    switch (conversationType) {
        case ShoutGID:
            [[MessagingManager sharedManager] sendBroadcastMessage:outgoingMessage];
            break;
        case OneToOneGID:
        case GroupGID:
            [[MessagingManager sharedManager] sendMessage:outgoingMessage encrypt:YES];
            break;
        case EmergencyGID:
            break;
    }
}

# pragma mark - MessagingManagerProtocol

- (void)messagingManager:(MessagingManager *)manager didSendOutgoingMessage:(Message *)message {
    [self insertMessage:message];
}

- (void)messagingManager:(MessagingManager *)manager didFailSendingMessage:(Message *)message {
    [self showAlertWithTitle:@"Message Failed" message:[NSString stringWithFormat:@"Your message '%@' was not sent.", message.text]];
}

- (void)messagingManager:(MessagingManager *)manager didReceiveIncomingShout:(Message *)message {
    [self insertMessage:message];
}

- (void)messagingManager:(MessagingManager *)manager didReceiveIncomingMessage:(Message *)message {
    [self insertMessage:message];
}

//- (void)messagingManager:(MessagingManager *)manager didReceiveIncoming:(GTBaseMessageData *)messageData {
//    // Generic handler
//    Message *message = [[Message alloc] initWithData:(GTTextOnlyMessageData *)messageData];
//    [self insertMessage:message];
//}

# pragma mark - QueueManagerProtocol

- (void)queueManager:(QueueManager *)manager didResendMessage:(Message *)message {
    [self insertMessage:message];
}

# pragma mark - ChatTableProtocol

- (void)chatTable:(ChatTableDataSource *)chatTable didSelectCell:(UITableViewCell *)cell {
    if ([cell.textLabel.text isEqualToString:@"Send Message"]) {
        [self sendMessage];
    }
}

- (void)chatTable:(ChatTableDataSource *)chatTable didSelectContact:(Contact *)contact {
    self.receivingGID = contact.gid;
}

# pragma mark - UITextFieldDelegate

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string {
    if (textField.text.length > 160) {
        textField.text = [textField.text substringToIndex:160];
    }
    
    return YES;
}

# pragma mark - Helpers

- (void)reloadTable {
    NSUInteger messagesIndex = (self.shouldDisplayRecipients) ? 1 : 0;
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.tableView beginUpdates];
        [self.tableView reloadSections:[NSIndexSet indexSetWithIndex:messagesIndex] withRowAnimation:UITableViewRowAnimationAutomatic];
        [self.tableView endUpdates];
    });
}

- (void)setupConversation {
    NSString *title = nil;
    
    switch (self.conversationType) {
        case ShoutGID:
            title =  @"Broadcast";
            self.receivingGID = [GIDManager shoutGID];
            break;
        case OneToOneGID:
            title = @"Private Chat";
            self.receivingGID = [[[ContactManager sharedManager] allDemoContactsExcludingSelf] firstObject].gid;
            break;
        case GroupGID:
            title = @"Group";
            self.receivingGID = (self.group) ? [self.group groupGID] : @0;
            break;
        case EmergencyGID:
            title = @"Emergency";
            self.receivingGID = [GIDManager emergencyGID];
            break;
    }
    
    self.title = title;
}

- (void)showAlertWithTitle:(NSString *)title message:(NSString *)message {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:title message:message preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *dismiss = [UIAlertAction actionWithTitle:@"Dismiss" style:UIAlertActionStyleDefault handler:nil];
    
    [alert addAction:dismiss];
    [self presentViewController:alert animated:YES completion:nil];
}

# pragma mark - Lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    [self setupConversation];
    
    self.dataSource = [[ChatTableDataSource alloc] initWithConversationType:self.conversationType delegate:self];
    self.dataSource.recipients = (self.group) ? [self.group groupMembers] : [[ContactManager sharedManager] allDemoContactsExcludingSelf];
    
    self.tableView.dataSource = self.dataSource;
    self.tableView.delegate = self.dataSource;
    
    self.shouldDisplayRecipients = (self.conversationType == OneToOneGID || self.conversationType == GroupGID);
    
    // Assign handlers
    [[MessagingManager sharedManager] setDelegate:self];
    [[QueueManager sharedManager] setDelegate:self];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
