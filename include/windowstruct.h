//
//  windowstruct.h
//  inlocus_anomalydetection
//
//  Created by Sahil Tyagi on 24/08/19.
//  Copyright © 2019 Sahil Tyagi. All rights reserved.
//

#ifndef windowstruct_h
#define windowstruct_h
#include <stdio.h>

struct windowqnode {
    double value;
    struct windowqnode* next;
};

struct windowqueue {
    struct windowqnode *head, *tail;
};

struct windowqnode* newqnode(double val);
struct windowqueue* createwindowqueue();
void enqueue(struct windowqueue* window, double value);
struct windowqnode* dequeue(struct windowqueue* window);
int sizeofwindow(struct windowqueue* window);
struct windowqueue* transformedwindow(struct windowqueue* window, double lambda);
void readqueue(struct windowqueue* window);
#endif /* windowstruct_h */
