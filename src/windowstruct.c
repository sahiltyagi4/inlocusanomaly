//
//  windowstruct.c
//  inlocus_anomalydetection
//
//  Created by Sahil Tyagi on 24/08/19.
//  Copyright © 2019 Sahil Tyagi. All rights reserved.
//

# include <stdlib.h>
# include <math.h>
#include "windowstruct.h"

struct windowqnode* newqnode(double val) {
    struct windowqnode* qnode = (struct windowqnode*)malloc(sizeof(struct windowqnode));
    qnode->value = val;
    qnode->next = NULL;
    return qnode;
}

struct windowqueue* createwindowqueue() {
    struct windowqueue* window = (struct windowqueue*)malloc(sizeof(struct windowqueue));
    window->head = NULL;
    window->tail = NULL;
    return window;
}

void enqueue(struct windowqueue* window, double val) {
    struct windowqnode* qnode = newqnode(val);
    if(window->head == NULL) {
        window->head = window->tail = qnode;
    } else {
        window->tail->next = qnode;
        window->tail = qnode;
    }
}

struct windowqnode* dequeue(struct windowqueue* window) {
    if(window->head == NULL ) {
        return NULL;
    }
    
    struct windowqnode* qnode = window->head;
    window->head = qnode->next;
    
    if(window->head == NULL) {
        window->tail = NULL;
    }
    
    return qnode;
}

int sizeofwindow(struct windowqueue* window) {
    int size = 0;
    if(window->head != NULL) {
        
        struct windowqnode* qnode = window->head;
        size++;
        while(qnode->next != NULL) {
            struct windowqnode* nextnode = qnode->next;
            size++;
            qnode = nextnode;
        }
    }
    return size;
}

struct windowqueue* transformedwindow(struct windowqueue* window, double lambda) {
    struct windowqueue* transformed_window = createwindowqueue();
    if(window->head != NULL) {
        double x_transformed = 0.00;
        struct windowqnode* qnode = window->head;
        if(lambda ==0) {
            x_transformed = log(qnode->value);
        } else {
            x_transformed = (pow(qnode->value, lambda) - 1)/(lambda);
        }
        printf("original val: %f and transformed val: %f\n", qnode->value, x_transformed);
        
        enqueue(transformed_window, x_transformed);
        while(qnode->next != NULL) {
            struct windowqnode* nextnode = qnode->next;
            if(lambda ==0) {
                x_transformed = log(nextnode->value);
            } else {
                x_transformed = (pow(nextnode->value, lambda) - 1)/(lambda);
            }
            printf("original val: %f and transformed val: %f\n", nextnode->value, x_transformed);
            enqueue(transformed_window, x_transformed);
            qnode = nextnode;
        }
    }
    
    return transformed_window;
}

void readqueue(struct windowqueue* window) {
    if(window->head != NULL) {
        struct windowqnode* qnode = window->head;
        printf("%f\n", qnode->value);
        while(qnode->next != NULL) {
            struct windowqnode* nextnode = qnode->next;
            printf("%f\n", nextnode->value);
            qnode = nextnode;
        }
    }
}
