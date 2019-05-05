//
//  writer.hpp
//  vk_graphs
//
//  Created by Даниил on 30/03/2019.
//  Copyright © 2019 kyoshee. All rights reserved.
//

#ifndef writer_hpp
#define writer_hpp

#include <stdio.h>

#include "pool.h"

struct Writer
{
    Pool m_p;
    
    std::string m_filename;
    
    void SetPool(Pool p);
    void SetFilename(std::string s);
    void Write();
    void WriteDescription();
    void WriteNodes();
    void WritePersonNode(Person p);
    void WriteCommunityNodes();
    void WriteEdges();
    void WriteEdgesLikes();
    void WritePersonEdgesLikes(Person p);
    void WriteEdgesComments();
    void WritePersonEdgesComments(Person p);
    void WriteEdgesPostsO();
    void WritePersonEdgesPostsO(Person p);
    void WriteEdgesPhotosLikes();
    void WritePersonEdgesPhotosLikes(Person p);
    void WriteEdgesCommunities();
    void WritePersonEdgesCommunities(Person p);
    void WriteMutualFriends();
    void WriteClose();
};

#endif /* writer_hpp */
