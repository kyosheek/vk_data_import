//
//  man.hpp
//  vk_graphs
//
//  Created by Даниил on 29/03/2019.
//  Copyright © 2019 kyoshee. All rights reserved.
//

#ifndef man_hpp
#define man_hpp

#include <string>
#include <vector>
#include <map>

#include <stdio.h>

struct Person
{
    int m_id;
    bool m_closed;
    std::string m_fn, m_ln, m_bd, m_ph, m_country, m_city, m_ht;
    std::string m_uni = "", m_fac = "";
    std::string m_sch = "";
    int m_wallPostsCount;
    
    std::vector<int> m_friends = {};
    std::vector<int> m_wallPosts = {};
    std::vector<int> m_wallLikes = {};
    std::vector<int> m_wallComments = {};
    std::vector<int> m_wallPostsO = {};
    std::vector<int> m_photos = {};
    std::vector<int> m_photosLikes = {};
    std::map<int, int> m_communities = {};
    
    Person() {}
    Person(int id);
    
    void SetId(int id);
    void SetWallLikes(std::vector<int> v);
    void SetWallComments(std::vector<int> v);
    void SetWallPostsO(std::vector<int> v);
    void SetPhotosLikes(std::vector<int> v);
    void GetGeneral();
    void GetFriends();
    void GetGroups();
    void GetLinks();
    void GetWallPosts();
    void GetWallLikes();
    void GetWallComments();
    void GetPhotos();
    void GetPhotosLikes();
    void Clear();
    
    ~Person() {}
};

#endif /* man_hpp */
