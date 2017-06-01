//
//  BNCServerOperation.h
//  Branch-TestBed
//
//  Created by edward on 5/30/17.
//  Copyright © 2017 Branch Metrics. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BNCNetworkServiceProtocol.h"
#import "BNCPersistentQueue.h"
#import "BNCServerRequest.h"

#pragma mark BNCBranchNetworkServiceOperation

@interface BNCBranchNetworkServiceOperation : NSObject <BNCPersistentQueueItem>
@property (readonly) NSURL          *URL;
@property (readonly) NSString       *method;
@property (readonly) NSInteger      HTTPStatusCode;
@property (readonly) NSError        *error;
@property (readonly) NSDictionary   *responseDictionary;
@property (readonly) NSDate         *startDate;
@property (readonly) NSDate         *finishDate;
@property (assign)   NSTimeInterval timeoutInterval;

- (void) start;
- (void) cancel;
@end

#pragma mark - BNCBranchNetworkService

@interface BNCBranchNetworkService : NSObject

- (instancetype) initWithNetworkService:(id<BNCNetworkServiceProtocol>)networkService NS_DESIGNATED_INITIALIZER;

- (BNCBranchNetworkServiceOperation*) getOperationWithURL:(NSURL *)URL
                             data:(NSDictionary*)data
                       completion:(void (^)(BNCBranchNetworkServiceOperation*operation))completion;

- (BNCBranchNetworkServiceOperation*) postOperationWithURL:(NSString *)API
                              data:(id<NSObject>)dictionaryOrArray
                        completion:(void (^)(BNCBranchNetworkServiceOperation*operation))completion;

@property (assign) NSInteger maximumConcurrentOperations;
@property (assign) NSTimeInterval defaultTimeoutInterval;

// Glue code:

- (void) startRequest:(BNCServerRequest*)request;

@end
