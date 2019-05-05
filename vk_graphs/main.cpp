//
//  main.cpp
//  vk_graphs
//
//  Created by Даниил on 29/03/2019.
//  Copyright © 2019 kyoshee. All rights reserved.
//

#include <iostream>

#include "source/writer.h"

int main(int argc, const char * argv[]) {
    std::cout << "PERSON\n";
    Person p(203861508);
    Pool pool;
    pool.SetStart(p);
    pool.SetDepth(1);
    std::cout << "POOL\n";
    pool.Gather();
    Writer w;
    w.SetFilename("s_d1.avs");
    w.SetPool(pool);
    std::cout << "WRITER\n";
    w.Write();
    return 0;
}
