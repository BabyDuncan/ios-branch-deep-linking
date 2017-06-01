//
//  BranchSetIdentityRequest.h
//  Branch-TestBed
//
//  Created by Graham Mueller on 5/22/15.
//  Copyright (c) 2015 Branch Metrics. All rights reserved.
//

#import "Branch.h"

#if 0
#import "BNCServerRequest.h"

@interface BranchSetIdentityRequest : BNCServerRequest

- (id)initWithUserId:(NSString *)userId callback:(callbackWithParams)callback;

@end

#else
#import "BNCBranchNetworkService.h"

@interface BNCBranchNetworkService (BranchSetIdentityRequest)

- (BNCBranchNetworkServiceOperation*) branchSetIdentityRequestWithUserId:(NSString *)userId
                                                                callback:(callbackWithParams)callback;

@end

#endif
