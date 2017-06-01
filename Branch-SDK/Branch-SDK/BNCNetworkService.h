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

@interface BNCNetworkOperationProtocol : NSObject <BNCNetworkOperationProtocol>
@property (readonly) NSURL          *URL;
@property (readonly) NSInteger      HTTPStatusCode;
@property (readonly) NSError        *error;
@property (readonly) id<NSObject>   responseData;
@property (assign)   NSTimeInterval timeoutInterval;

- (void) start;
- (void) cancel;
@end

#pragma mark - BNCNetworkService

@interface BNCNetworkService : NSObject <BNCNetworkServiceProtocol>
+ (id<BNCNetworkServiceProtocol>) new;

@property (assign) NSTimeInterval defaultTimeout;
@property (assign) NSInteger maximumConcurrentOperations;
@property (assign, getter=operationsAreSuspended) BOOL suspendOperations;

- (id<BNCNetworkOperationProtocol>) getOperationWithURL:(NSURL *)URL
           completion:(void (^)(id<BNCNetworkOperationProtocol>operation))completion;

- (id<BNCNetworkOperationProtocol>) postOperationWithURL:(NSURL *)URL
          contentType:(NSString*)contentType
                 data:(NSData *)data
           completion:(void (^)(id<BNCNetworkOperationProtocol>operation))completion;
@end
