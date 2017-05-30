//
//  BNCNetworkProvider.h
//  Branch-TestBed
//
//  Created by edward on 5/30/17.
//  Copyright © 2017 Branch Metrics. All rights reserved.
//

#import <Foundation/Foundation.h>

#pragma mark - BNCNetworkOperationProtocol

@protocol BNCNetworkHTTPOperationProtocol <NSObject>
@property (readonly) NSURL          *URL;
@property (readonly) NSString       *method;
@property (readonly) NSInteger      HTTPStatusCode;
@property (readonly) NSError        *error;
@property (readonly) id<NSObject>   responseData;
@property (readonly) NSDate         *startDate;
@property (readonly) NSDate         *finishDate;
@property (readonly) NSTimeInterval timeoutInterval;

- (void) start;
- (void) cancel;
@end

#pragma mark - BNCNetworkServiceProtocol

@protocol BNCNetworkServiceProtocol <NSObject>

+ (id<BNCNetworkServiceProtocol>) new;

@property (assign) NSTimeInterval defaultTimeout;
@property (assign) NSInteger maximumConcurrentOperations;
@property (assign, getter=operationsAreSuspended) BOOL suspendOperations;

- (id<BNCNetworkHTTPOperationProtocol>) getOperationWithURL:(NSURL *)URL
           completion:(void (^)(id<BNCNetworkHTTPOperationProtocol>operation))completion;

- (id<BNCNetworkHTTPOperationProtocol>) postOperationWithURL:(NSURL *)URL
          contentType:(NSString*)contentType
                 data:(NSData *)data
           completion:(void (^)(id<BNCNetworkHTTPOperationProtocol>operation))completion;

@end
