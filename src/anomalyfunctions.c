//
//  anomalyfunctions.c
//  inlocus_anomalydetection
//
//  Created by Sahil Tyagi on 26/08/19.
//  Copyright © 2019 Sahil Tyagi. All rights reserved.
//

# include <stdlib.h>
# include <math.h>
# include <float.h>
# include "windowstruct.h"
# include "anomalyfunctions.h"

//returns a window with probabilities for each input value
struct windowqueue* getprobability(struct windowqueue* window) {
    struct windowqueue* anomalyscores = createwindowqueue();
    if(window->head != NULL && window->tail != NULL) {
        struct windowqnode* qnode = window->head;
        
        double meanval = mean(window);
        double stdeval = stdeviation(window);
        printf("boxcox transformed mean: %f\n", meanval);
        printf("boxcox transformed std: %f\n", stdeval);
        
        double exponent = pow((qnode->value - meanval),2)/2*pow(stdeval,2);
        double prob = exp(exponent)/(pow(2*M_PI, 0.5)*stdeval);
        printf("probabilty score:%f\n", prob);
        enqueue(anomalyscores, prob);
        while(qnode->next != NULL) {
            struct windowqnode* nextnode = qnode->next;
            double exponent = pow((qnode->value - meanval),2)/2*pow(stdeval,2);
            double prob = exp(exponent)/(pow(2*M_PI, 0.5)*stdeval);
            printf("probabilty score:%f\n", prob);
            enqueue(anomalyscores, prob);
            qnode = nextnode;
        }
    }
    
    return anomalyscores;
}

double mean(struct windowqueue* window) {
    double summedval=0.0;
    int counter=0;
    if(window->head != NULL && window->tail != NULL) {
        struct windowqnode* qnode = window->head;
        summedval += qnode->value;
        counter++;
        while(qnode->next != NULL) {
            struct windowqnode* nextnode = qnode->next;
            summedval += nextnode->value;
            counter++;
            qnode = nextnode;
        }
    }
    
    return (summedval/counter);
}

double stdeviation(struct windowqueue* window) {
    double summedsquare=0.0;
    int counter=0;
    if(window->head != NULL && window->tail != NULL) {
        double average = mean(window);
        struct windowqnode* qnode = window->head;
        summedsquare += pow((qnode->value - average), 2);
        counter++;
        while(qnode->next != NULL) {
            struct windowqnode* nextnode = qnode->next;
            summedsquare += pow((nextnode->value - average), 2);
            counter++;
            qnode = nextnode;
        }
    }
    
    return pow((summedsquare/counter), 0.5);
}

double sumOfLogX(struct windowqueue* window) {
    double sumlogX = 0.00;
    if(window->head != NULL) {
        struct windowqnode* qnode = window->head;
        sumlogX += log(qnode->value);
        while(qnode->next != NULL) {
            struct windowqnode* nextnode = qnode->next;
            sumlogX += log(nextnode->value);
            qnode = nextnode;
        }
    }
    
    return sumlogX;
}

double squaredTransformDiff(struct windowqueue* transformed_window, double mean, double stdeviation) {
    double sumsquarediff = 0.00;
    if(transformed_window->head != NULL) {
        struct windowqnode* qnode = transformed_window->head;
        sumsquarediff = pow((qnode->value - mean),2);
        while(qnode->next != NULL) {
            struct windowqnode* nextnode = qnode->next;
            sumsquarediff += pow((nextnode->value - mean),2);
            qnode = nextnode;
        }
    }
    
    return (sumsquarediff/(2*stdeviation*stdeviation));
}

struct windowqueue* boxcoxtransform(struct windowqueue* window, double lowerbound, double upperbound, double stepsize) {
    double lambda = lowerbound;
    int n = sizeofwindow(window);
    //double sumlogx = (lambda - 1)*sumOfLogX(window);
    double global_loglike = -DBL_MAX;
    struct windowqueue* transformed_window;
    struct windowqueue* globalwindow;
    
    while(lambda < upperbound) {
        printf("doing box-cox eval for lambda %f\n", lambda);
        transformed_window = transformedwindow(window, lambda);
        double avg = mean(transformed_window);
        double sd = stdeviation(transformed_window);
        double squarediff = squaredTransformDiff(transformed_window, avg, sd);
        printf("lambda: %f\n", lambda);
        printf("mean: %f\n", avg);
        printf("standard deviation: %f\n", sd);
        printf("window size: %d\n", n);
        
        double constantval = (-n*log(2*M_PI*sd*sd))/2;
//        double loglikelihood =  constantval - squarediff + sumlogx;
        double loglikelihood =  constantval - squarediff;
        printf("constant val:%f\n", constantval);
        printf("squarediff:%f\n", squarediff);
//        printf("sumlogx %f\n", sumlogx);
        printf("local loglikelihood: %f\n", loglikelihood);
        
        if(loglikelihood > global_loglike) {
            global_loglike = loglikelihood;
            globalwindow = transformed_window;
            printf("GLOBAL loglikelihood: %f\n", global_loglike);
        }
        
        lambda += stepsize;
    }
    
//    if(globalwindow->head != NULL) {
//        struct windowqnode* qnode = globalwindow->head;
//        qnode->value = (qnode->value/optimum_sigma);
//        while(qnode->next != NULL) {
//            struct windowqnode* nextnode = qnode->next;
//            nextnode->value = (nextnode->value/optimum_sigma);
//            qnode = nextnode;
//        }
//    }
    
    //printf("optimum value for lambda is %f\n", lambda);
    return globalwindow;
}
