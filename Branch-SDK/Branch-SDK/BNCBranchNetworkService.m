//
//  BNCServerOperation.m
//  Branch-TestBed
//
//  Created by Edward Smith on 5/30/17.
//  Copyright © 2017 Branch Metrics. All rights reserved.
//

#import "BNCBranchNetworkService.h"
#import "BNCLog.h"

#pragma mark BNCBranchNetworkService

@interface BNCBranchNetworkServiceOperation ()
@property (strong) NSError        *error;
@property (strong) id<NSObject>   responseData;
@property (strong) NSDate         *startDate;
@property (strong) NSDate         *finishDate;

@property (strong) id<BNCNetworkOperationProtocol> networkOperation;
@property (copy) void (^completionHandler)(BNCBranchNetworkServiceOperation*operation);
@end

#pragma mark - BNCBranchNetworkService

@interface BNCBranchNetworkService () {
    NSTimeInterval      _defaultTimeoutInterval;
}
@property (strong) BNCPersistentQueue *persistentQueue;
@property (strong) id<BNCNetworkServiceProtocol> networkService;
@end

@implementation BNCBranchNetworkService

- (void) setDefaultTimeoutInterval:(NSTimeInterval)timeout {
    @synchronized (self) {
        _defaultTimeoutInterval = MAX(timeout, 10.0);
    }
}

- (NSTimeInterval) defaultTimeoutInterval {
    @synchronized (self) {
        return _defaultTimeoutInterval;
    }
}

- (BNCBranchNetworkServiceOperation*) postOperationWithURL:(NSURL *)URL
                          data:(id<NSObject>)dictionaryOrArray
                    completion:(void (^)(BNCBranchNetworkServiceOperation*operation))completion {

    NSData *data = nil;
    NSError *error = nil;
    BNCBranchNetworkServiceOperation *serviceOperation = [BNCBranchNetworkServiceOperation new];
    serviceOperation.startDate = [NSDate date];
    serviceOperation.timeoutInterval = self.defaultTimeoutInterval;
    serviceOperation.completionHandler = completion;

    if (dictionaryOrArray) {
        data = [NSJSONSerialization dataWithJSONObject:dictionaryOrArray options:0 error:&error];
    }
    if (error) {
        serviceOperation.error = error;
        return serviceOperation;
    }
    serviceOperation.networkOperation =
        [self.networkService postOperationWithURL:URL
            contentType:@"application/json"
            data:data
            completion:^(id<BNCNetworkOperationProtocol>operation) {
                [self networkOperationDidComplete:serviceOperation];
            }];
    BNCLogAssert(serviceOperation.networkOperation != nil);
    [self.persistentQueue addItem:serviceOperation];
    return serviceOperation;
}

- (void) networkOperationDidComplete:(BNCBranchNetworkServiceOperation*)serverOperation {

    serverOperation.finishDate = [NSDate date];

    // Success
    if (!serverOperation.networkOperation.error &&
        serverOperation.networkOperation.HTTPStatusCode == 200) {
        [self.persistentQueue removeItemWithIdentifier:serverOperation.uniqueIdentifier];
        if (serverOperation.completionHandler)
            serverOperation.completionHandler(serverOperation);
        return;
    }

    // Cancelled
    
    // Timed out
    if ([serverOperation.startDate timeIntervalSinceNow] <= - serverOperation.timeoutInterval) {
        NSMutableDictionary *errorDictionary = [NSMutableDictionary dictionaryWithDictionary:@{
            NSLocalizedDescriptionKey: @"Timed out while trying to connnect to the server."
        }];
        if (serverOperation.error) {
            NSError *underlyingError = [serverOperation.error copy];
            [errorDictionary setObject:underlyingError forKey:NSUnderlyingErrorKey];
        }
        serverOperation.error =
            [NSError errorWithDomain:NSURLErrorDomain code:NSURLErrorTimedOut
                userInfo:@{NSLocalizedDescriptionKey: @"Timed out while trying to connnect to the server." }];
        [self.persistentQueue removeItemWithIdentifier:serverOperation.uniqueIdentifier];
        if (serverOperation.completionHandler)
            serverOperation.completionHandler(serverOperation);
        return;
    }

    // Retry
    if ([self canRetryServerOpertion:serverOperation]) {

    }

    // Failed
}

- (BOOL) canRetryServerOpertion:(BNCBranchNetworkServiceOperation*)serverOperation {
    return YES;
}

#pragma mark - Glue Code

- (void) startRequest:(BNCServerRequest *)request {

}

@end
