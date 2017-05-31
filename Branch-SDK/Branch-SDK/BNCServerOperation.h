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

@interface BNCBranchServerOperation : NSObject <BNCPersistentQueueItem>
@property (strong) NSURL          *URL;
@property (strong) NSString       *method;
@property (assign) NSInteger      HTTPStatusCode;
@property (strong) NSError        *error;
@property (strong) id<NSObject>   requestData;
@property (strong) id<NSObject>   responseData;
@property (strong) NSDate         *startDate;
@property (strong) NSDate         *finishDate;
@property (assign) NSTimeInterval timeoutInterval;
@property (strong) id<BNCNetworkHTTPOperationProtocol> networkOperation;
@property (copy)   void (^completionHandler)(BNCBranchServerOperation*operation);
- (void) start;
- (void) cancel;
@end

#pragma mark - BNCBranchServer

@interface BNCBranchServer : NSObject

- (instancetype) initWithNetworkService:(id<BNCNetworkServiceProtocol>)networkService;

- (BNCBranchServerOperation*) getOperationWithURL:(NSURL *)URL
                                       completion:(void (^)(BNCBranchServerOperation*operation))completion;

- (BNCBranchServerOperation*) postOperationWithURL:(NSURL *)URL
                                              data:(id<NSObject>)dictionaryOrArray
                                        completion:(void (^)(BNCBranchServerOperation*operation))completion;

@property (assign) NSInteger maximumConcurrentOperations;
@property (assign) NSTimeInterval defaultTimeout;
@end
