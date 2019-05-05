//
//  Log.h
//  VisualNovelXC
//
//  Created by Даниил on 17/03/2019.
//  Copyright © 2019 kyoshee. All rights reserved.
//

#ifndef Log_h
    #define Log_h

    #include <stdio.h>

    #define DEBUG 1

    #ifdef DEBUG
        #define Log(...) printf(__VA_ARGS__); printf("\n");
    #else
        #define Log(...);
    #endif

#endif /* Log_h */
