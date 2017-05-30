//
//  BNCNetworkQueue.h
//  Branch-TestBed
//
//  Created by edward on 5/30/17.
//  Copyright © 2017 Branch Metrics. All rights reserved.
//

#import <Foundation/Foundation.h>

#pragma mark BNCPersistentQueueItem

typedef NS_ENUM(NSInteger, BNCPersistentQueueItemState) {
    BNCPersistentQueueItemStateWaiting   = 0,
    BNCPersistentQueueItemStateRunning   = 1,
    BNCPersistentQueueItemStateCompleted = 2,
};

@protocol BNCPersistentQueueItem <NSObject, NSCoding>
- (NSString*) uniqueIdentifier;
@property (assign) BNCPersistentQueueItemState queueItemState;
@end

#pragma mark - BNCPersistentQueue

@interface BNCPersistentQueueBNCPersistentQueue : NSObject

- (instancetype) initWithDataStoreURL:(NSURL*)URL;

- (void) addItem:(id<BNCPersistentQueueItem>)item;
- (void) removeItemWithIdentifier:(NSString*)uniqueIdentifier;

- (id<BNCPersistentQueueItem>) nextItem;
- (NSInteger) queueDepth;

@end
