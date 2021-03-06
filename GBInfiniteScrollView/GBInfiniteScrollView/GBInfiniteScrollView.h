//
//  GBInfiniteScrollView.h
//  GBInfiniteScrollView
//
//  Created by Gerardo Blanco García on 01/10/13.
//  Copyright (c) 2013 Gerardo Blanco García. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining
//  a copy of this software and associated documentation files (the
//  "Software"), to deal in the Software without restriction, including
//  without limitation the rights to use, copy, modify, merge, publish,
//  distribute, sublicense,  and/or sell copies of the Software, and to
//  permit persons to whom the Software is furnished to do so, subject to
//  the following conditions:
//
//  The above copyright notice and this permission notice shall be
//  included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
//  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
//  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#import <UIKit/UIKit.h>

#import "GBInfiniteScrollViewPage.h"

typedef NS_ENUM(NSInteger, GBAutoScrollDirection) {
    /** Automatic scrolling from right to left. This is the default. */
    GBAutoScrollDirectionRightToLeft,
    /** Automatic scrolling from left to right. */
    GBAutoScrollDirectionLeftToRight,
    /** Automatic scrolling from top to bottom. */
    GBAutoScrollDirectionTopToBottom,
    /** Automatic scrolling from bottom to top. */
    GBAutoScrollDirectionBottomToTop
};

typedef NS_ENUM(NSInteger, GBScrollDirection) {
    /** Horizontal scroll direction. */
    GBScrollDirectionHorizontal,
    /** Vertical scroll direction. */
    GBScrollDirectionVertical
};

@interface GBInfiniteScrollViewParent : UIScrollView

/**
 *  Timing function of an scroll animation.
 *  Defaults to CAMediaTimingFunctionEaseInEaseOut.
 */
@property (nonatomic) CAMediaTimingFunction *timingFunction;

/**
 *  The animation duration for the contentOffset.
 *  Defaults to 0.25f
 */
@property (nonatomic) CGFloat animationDuration;

/**
 *  Debug mode.
 *  Defaults to NO.
 */
@property (nonatomic, getter = isDebugModeOn) BOOL debug;

/**
 *  Verbose for debug mode.
 *  Defaults to NO.
 */
@property (nonatomic, getter = isVerboseDebugModeOn) BOOL verboseDebug;

@end

@protocol GBInfiniteScrollViewDelegate;
@protocol GBInfiniteScrollViewDataSource;

/**
 * GBInfiniteScrollView class provides an endlessly scroll view organized in pages. It is a subclass of UIScrollView,
 * which allows users to scroll infinitely in the horizontal direction. GBInfiniteScrollView also provides automatic
 * scrolling feature.
 *
 * A infinite scroll view object must have an object that acts as a data source and an object that acts as a delegate.
 * The data source must adopt the GBInfiniteScrollViewDataSource protocol and the delegate must adopt the
 * GBInfiniteScrollViewDelegate protocol. The data source provides the views that GBInfiniteScrollView needs to display.
 * The delegate allows the adopting delegate to respond to scrolling operations.
 *
 * GBInfiniteScrollView overrides the layoutSubviews method of UIView so that it calls reloadData only when you create a
 * new instance of GBInfiniteScrollView or when you assign a new data source. Reloading the infinite scroll view clears
 * current state, including the current view, but it is possible to specify the initial page index to display.
 *
 * It is based on Apple StreetScroller iOS sample code.
 */
@interface GBInfiniteScrollView : GBInfiniteScrollViewParent <UIScrollViewDelegate>

/** 
 * The data source of the infinite scroll view object.
 */
@property (nonatomic, assign) id <GBInfiniteScrollViewDataSource> infiniteScrollViewDataSource;

/**
 * The delegate of the infinite scroll view object.
 */
@property (nonatomic, assign) id <GBInfiniteScrollViewDelegate> infiniteScrollViewDelegate;

/**
 * Returns an initialized infinite scroll view.
 */
- (id)init;

/**
 * Returns an initialized infinite scroll view from a given frame.
 */
- (id)initWithFrame:(CGRect)frame;

/**
 * Returns an initialized infinite scroll view from data in a given unarchiver.
 */
- (id)initWithCoder:(NSCoder *)aDecoder;

/** 
 * The time interval of the automatic scrolling.
 */
@property (nonatomic) CGFloat interval;

/**
 * The direction of scrolling, horizontal (default) or vertical.
 */
@property (nonatomic) GBScrollDirection scrollDirection;

/** 
 * The direction of automatic scrolling, right to left (default) or left to right.
 */
@property (nonatomic) GBAutoScrollDirection autoScrollDirection;

/** 
 * The initial page index.
 */
@property (nonatomic) NSUInteger pageIndex;

/** 
 * The current page index.
 */
@property (nonatomic, readonly) NSUInteger currentPageIndex;

/** 
 * A Boolean value that controls if it should scrolling wrap the data source's ends.
 */
@property (nonatomic) BOOL shouldScrollingWrapDataSource;

/**
 *  Verbose for debug mode.
 */
@property (nonatomic, getter = isTapEnabled) BOOL tapEnabled;

/**
 *  Gets the current view.
 *
 *  @return The current page of the infinite scroll view.
 */
- (GBInfiniteScrollViewPage *)currentPage;

/**
 * Reloads everything from scratch.
 */
- (void)reloadData;

/** 
 * Updates current page's data source.
 */
- (void)updateData;

/**
 * Resets the infinite scroll view layout.
 */
- (void)resetLayout;

/** 
 * Stops automatic scrolling.
 */
- (void)stopAutoScroll;

/** 
 * Starts automatic scrolling.
 */
- (void)startAutoScroll;

/**
 *  Gets a reusable page.
 *
 *  @return A reusable GBInfiniteScrollViewPage object.
 */
- (GBInfiniteScrollViewPage *)dequeueReusablePage;

/**
 * Scrolls a specific page.
 *
 *  @param index Index of the page.
 *  @param animated YES if the scrolling should be animated, NO if it should be immediate.
 */
- (void)scrollToPageAtIndex:(NSUInteger)index animated:(BOOL)animated;

@end

/**
 * @protocol GBInfiniteScrollViewDataSource
 *
 * This protocol represents the data model object.
 */
@protocol GBInfiniteScrollViewDataSource<NSObject>

@required

/**
 *  Tells the data source to return the number of pages.
 *
 *  @warning Required
 *
 *  @param infiniteScrollView The infinite scroll view object.
 *
 *  @return An NSInteger with the number of pages of the GBInfiniteScrollViewPage object.
 */
- (NSInteger)numberOfPagesInInfiniteScrollView:(GBInfiniteScrollView *)infiniteScrollView;

/**
 *  Asks the data source for a view to display in a particular page index.
 *
 *  @warning Required
 *
 *  @param infiniteScrollView The infinite scroll view object.
 *  @param index Index of the page
 *
 *  @return The GBInfiniteScrollViewPage object for the index.
 */
- (GBInfiniteScrollViewPage *)infiniteScrollView:(GBInfiniteScrollView *)infiniteScrollView
                                     pageAtIndex:(NSUInteger)index;

@end

/**
 * @protocol GBInfiniteScrollViewDelegate 
 *
 * This protocol allows the adopting delegate to respond to scrolling operations.
 */
@protocol GBInfiniteScrollViewDelegate<NSObject>

@optional

/**
 *  Called when the GBInfiniteScrollView is panning.
 *
 *  @warning Optional
 *
 *  @param UIPanGestureRecognizer
 */

-(void)infiniteScrollViewDidPan:(UIPanGestureRecognizer*)pan;

/**
 *  Called when the GBInfiniteScrollView has scrolled to next page.
 *
 *  @warning Optional
 *
 *  @param infiniteScrollView The infinite scroll view object.
 */
- (void)infiniteScrollViewDidScrollNextPage:(GBInfiniteScrollView *)infiniteScrollView;

/**
 *  Called when the GBInfiniteScrollView has scrolled to previous page.
 *
 *  @warning Optional
 *
 *  @param infiniteScrollView The infinite scroll view object.
 */
- (void)infiniteScrollViewDidScrollPreviousPage:(GBInfiniteScrollView *)infiniteScrollView;

/**
 * Called when use tap on GBInfiniteScrollView.
 *
 *  @warning Optional
 *
 *  @param infiniteScrollView The infinite scroll view object.
 *  @param pageIndex Tapped page index.
 */
- (void)infiniteScrollView:(GBInfiniteScrollView *)infiniteScrollView didTapAtIndex:(NSInteger)pageIndex;

/**
 *  Called when the GBInfiniteScrollView will beigin dragging.
 *
 *  @warning Optional
 *
 *  @param infiniteScrollView The infinite scroll view object.
 */
- (void)infiniteScrollViewWillBeginDragging:(GBInfiniteScrollView *)infiniteScrollView;

/**
 *  Called when the GBInfiniteScrollView will end dragging.
 *
 *  @warning Optional
 *
 *  @param infiniteScrollView The infinite scroll view object.
 *  @param velocity The velocity of the scroll view (in points) at the moment the touch was released.
 *  @param targetContentOffset The expected offset when the scrolling action decelerates to a stop.
 */
- (void)infiniteScrollViewWillEndDragging:(GBInfiniteScrollView *)scrollView withVelocity:(CGPoint)velocity
                      targetContentOffset:(inout CGPoint *)targetContentOffset;

/**
 *  Asks the delegate if it is allowed to scroll to next page.
 *
 *  @warning Optional
 *
 *  @param infiniteScrollView The infinite scroll view object.
 */
- (BOOL)infiniteScrollViewShouldScrollNextPage:(GBInfiniteScrollView *)infiniteScrollView;

/**
 *  Asks the delegate if it is allowed to scroll to previous page.
 *
 *  @warning Optional
 *
 *  @param infiniteScrollView The infinite scroll view object.
 */
- (BOOL)infiniteScrollViewShouldScrollPreviousPage:(GBInfiniteScrollView *)infiniteScrollView;

@end