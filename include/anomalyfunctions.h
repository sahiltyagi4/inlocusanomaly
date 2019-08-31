//
//  anomalyfunctions.h
//  inlocus_anomalydetection
//
//  Created by Sahil Tyagi on 26/08/19.
//  Copyright © 2019 Sahil Tyagi. All rights reserved.
//

#ifndef anomalyfunctions_h
#define anomalyfunctions_h

#include <stdio.h>
#include "windowstruct.h"

struct windowqueue* getprobability(struct windowqueue* window);
double mean(struct windowqueue* window);
double stdeviation(struct windowqueue* window);
struct windowqueue* boxcoxtransform(struct windowqueue* window, double lowerbound, double upperbound, double stepsize);
double sumOfLogX(struct windowqueue* window);
double squaredTransformDiff(struct windowqueue* transformed_window, double mean, double stdeviation);
#endif /* anomalyfunctions_h */
