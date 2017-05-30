//
//  BNCNetworkService.h
//  Branch-TestBed
//
//  Created by edward on 5/30/17.
//  Copyright © 2017 Branch Metrics. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BNCNetworkServiceProtocol.h"

#pragma mark BNCNetworkOperation

@interface BNCNetworkHTTPOperation : NSObject <BNCNetworkHTTPOperationProtocol>

@property (readonly) NSURLSessionTaskState  sessionState;
@property (readonly) NSMutableURLRequest    *request;
@property (readonly) NSInteger              HTTPStatusCode;
@property (readonly) NSError                *error;
@property (readonly) NSDate                 *dateStart;
@property (readonly) NSDate                 *dateFinish;
@property (readonly) id<NSObject>           responseData;

- (void) start;
- (void) cancel;
@end

#pragma mark - BNCNetworkService

@interface BNCNetworkService : NSObject <BNCNetworkServiceProtocol>
+ (BNCNetworkService*) sharedService;

- (BNCNetworkHTTPOperation*) getOperationWithURL:(NSURL *)URL
                                      completion:(void (^)(BNCNetworkHTTPOperation*operation))completion;

- (BNCNetworkHTTPOperation*) postOperationWithURL:(NSURL *)URL
                                      contentType:(NSString*)contentType
                                             data:(NSData *)data
                                       completion:(void (^)(BNCNetworkHTTPOperation*operation))completion;

@property (assign) NSInteger maximumConcurrentOperations;
@property (assign) NSTimeInterval defaultTimeout;
@end
