//
//  BNCServerOperation.m
//  Branch-TestBed
//
//  Created by edward on 5/30/17.
//  Copyright © 2017 Branch Metrics. All rights reserved.
//

#import "BNCServerOperation.h"
#import "BNCPersistentQueue.h"
#import "BNCLog.h"

@implementation BNCBranchServerOperation
@end

@interface BNCBranchServer ()
@property (strong) BNCPersistentQueue *persistentQueue;
@property (strong) id<BNCNetworkServiceProtocol> networkService;
@end

@implementation BNCBranchServer

- (BNCBranchServerOperation*) postOperationWithURL:(NSURL *)URL
                                              data:(id<NSObject>)dictionaryOrArray
                                        completion:(void (^)(BNCBranchServerOperation*operation))completion {
    NSData *data = nil;
    NSError *error = nil;
    BNCBranchServerOperation *serverOperation = [BNCBranchServerOperation new];

    if (dictionaryOrArray) {
        data = [NSJSONSerialization dataWithJSONObject:dictionaryOrArray options:0 error:&error];
    }
    if (error) {
        serverOperation.error = error;
        serverOperation.completionHandler = completion;
        return serverOperation;
    }
    serverOperation.networkOperation =
        [self.networkService postOperationWithURL:URL
            contentType:@"application/json"
            data:data
            completion:^(id<BNCNetworkHTTPOperationProtocol>operation) {
                [self networkOperationDidComplete:serverOperation];
            }];
    [self.persistentQueue addItem:serverOperation];
    return serverOperation;
}

- (void) networkOperationDidComplete:(BNCBranchServerOperation*)serverOperation {

    if (!serverOperation.networkOperation.error &&
        serverOperation.networkOperation.HTTPStatusCode == 200) {
        if (serverOperation.completionHandler)
            serverOperation.completionHandler(serverOperation);
        [self.persistentQueue removeItemWithIdentifier:serverOperation.uniqueIdentifier];
        return;
    }

    if ([serverOperation.startDate timeIntervalSinceNow] <= - serverOperation.timeoutInterval) {
    }

    if ([self canRetryNetworkOpertion:serverOperation.networkOperation]) {
    }

}

@end
