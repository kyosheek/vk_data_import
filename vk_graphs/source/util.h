//
//  util.hpp
//  vk_graphs
//
//  Created by Даниил on 29/03/2019.
//  Copyright © 2019 kyoshee. All rights reserved.
//

#ifndef util_hpp
#define util_hpp

#include <string>
#include <vector>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
std::string PerformCurlRequest(std::string request);
int CountMutual(std::vector<int> a, std::vector<int> b);

#endif /* util_hpp */
