//
//  hellomake.c
//  inlocus_anomalydetection
//
//  Created by Sahil Tyagi on 23/08/19.
//  Copyright © 2019 Sahil Tyagi. All rights reserved.
//

#include "testmain.h"
#include "anomalyfunctions.h"
#include "windowstruct.h"

int main() {
    struct windowqueue* q = createwindowqueue();
    enqueue(q, 55.00);
    enqueue(q, 20.00);
    enqueue(q, 10.00);
    enqueue(q, 15.00);
    printf("first element: %f\n", q->head->value);
//    printf("2nd element: %f\n", q->head->next->value);
//    printf("last element: %f\n", q->tail->value);
//    printf("window size: %d\n", sizeofwindow(q));
    
    //readqueue(q);
    
//    struct windowqueue* q2 = boxcoxtransform(q, 0.0, 2, 0.5);
//
//    printf("reading q2 values...\n");
//    readqueue(q2);
//
//    struct windowqueue* probq = getprobability(q2);
//    readqueue(probq);
    
//    dequeue(q);
//    printf("after deletion first element: %f\n", q->head->value);
    return(0);
}
