//
//  pool.hpp
//  vk_graphs
//
//  Created by Даниил on 30/03/2019.
//  Copyright © 2019 kyoshee. All rights reserved.
//

#ifndef pool_hpp
#define pool_hpp

#include <vector>
#include <string>
#include <array>
#include <map>

#include <stdio.h>

#include "person.h"

struct Pool
{
    Person m_start;
    int m_depth;
    
    std::vector<std::vector<Person>> m_persons = {};
    std::vector<int> m_presentIds = {};
    std::map<int, int> m_presentCommunities;
    std::map<int, std::vector<std::array<int, 2>>> m_mutualFriends;
    
    void SetStart(Person p);
    void SetDepth(int depth);
    void Gather();
    void GatherByFriends(int depth, int pos);
    void GatherByLikes(int depth, int pos);
    void GatherByComments(int depth, int pos);
    void GatherByPosts(int depth, int pos);
    void GatherByPhotosLikes(int depth, int pos);
    void CheckMatches();
    void CheckMatchesByLikes(Person* p);
    void CheckMatchesByComments(Person* p);
    void CheckMatchesByPosts(Person* p);
    void CheckMatchesByPhotosLikes(Person* p);
    void AddCommunities();
    void CountMutualFriends();
};

#endif /* pool_hpp */
