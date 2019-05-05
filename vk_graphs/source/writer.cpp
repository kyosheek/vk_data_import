//
//  writer.cpp
//  vk_graphs
//
//  Created by Даниил on 30/03/2019.
//  Copyright © 2019 kyoshee. All rights reserved.
//

#include <fstream>
#include <iostream>

#include "writer.h"
#include "util.h"
#include "json.hpp"

using json = nlohmann::json;

void Writer::SetPool(Pool p)
{
    m_p = p;
}

void Writer::SetFilename(std::string s)
{
    m_filename = s;
}

void Writer::Write()
{
    std::cout << "\twrite description\n";
    WriteDescription();
    std::cout << "\twrite nodes\n";
    WritePersonNode(m_p.m_start);
    WriteNodes();
    std::cout << "\twrite edges\n";
    std::cout << "\t\twrite likes\n";
    WritePersonEdgesLikes(m_p.m_start);
    std::cout << "\t\twrite comments\n";
    WritePersonEdgesComments(m_p.m_start);
    std::cout << "\t\twrite posts from others\n";
    WritePersonEdgesPostsO(m_p.m_start);
    std::cout << "\t\twrite photo likes\n";
    WritePersonEdgesPhotosLikes(m_p.m_start);
    std::cout << "\t\twrite communities\n";
    WritePersonEdgesCommunities(m_p.m_start);
    WriteEdges();
    std::cout << "\twrite close tags\n";
    WriteClose();
}

void Writer::WriteDescription()
{
    std::ofstream file;
    file.open(m_filename.c_str(), std::ios_base::trunc);
    file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    file << "<avs>\n";
    file << "\t<description>\n";
    file << "\t\t<type id=\"person\" for=\"node\">\n";
    file << "\t\t\t<key attr.name=\"Icon_Name\" attr.type=\"string\" id=\"Icon_Name\"/>\n";
    file << "\t\t\t<key attr.name=\"id\" attr.type=\"int\" id=\"np_id\"/>\n";
    file << "\t\t\t<key attr.name=\"first_name\" attr.type=\"string\" id=\"np_fn\"/>\n";
    file << "\t\t\t<key attr.name=\"last_name\" attr.type=\"string\" id=\"np_ln\"/>\n";
    file << "\t\t\t<key attr.name=\"photo_link\" attr.type=\"string\" id=\"np_ph\"/>\n";
    file << "\t\t\t<key attr.name=\"is_closed\" attr.type=\"int\" id=\"np_closed\"/>\n";
    file << "\t\t\t<key attr.name=\"birth_day\" attr.type=\"string\" id=\"np_bd\"/>\n";
    file << "\t\t\t<key attr.name=\"country\" attr.type=\"string\" id=\"np_country\"/>\n";
    file << "\t\t\t<key attr.name=\"cur_city\" attr.type=\"string\" id=\"np_city\"/>\n";
    file << "\t\t\t<key attr.name=\"hometown\" attr.type=\"string\" id=\"np_ht\"/>\n";
    file << "\t\t\t<key attr.name=\"school\" attr.type=\"string\" id=\"np_sch\"/>\n";
    file << "\t\t\t<key attr.name=\"university\" attr.type=\"string\" id=\"np_uni\"/>\n";
    file << "\t\t\t<key attr.name=\"faculty\" attr.type=\"string\" id=\"np_fac\"/>\n";
    file << "\t\t\t<key attr.name=\"posts_count\" attr.type=\"int\" id=\"np_pc\"/>\n";
    file << "\t\t</type>\n";
    file << "\t\t<type id=\"community\" for=\"node\">\n";
    file << "\t\t\t<key attr.name=\"id\" attr.type=\"int\" id=\"nc_id\"/>\n";
    file << "\t\t\t<key attr.name=\"members_count\" attr.type=\"int\" id=\"nc_count\"/>\n";
    file << "\t\t</type>\n";
    file << "\t\t<type id=\"wall_like\" for=\"edge\">\n";
    file << "\t\t\t<key attr.name=\"link_orient\" attr.type=\"int\" id=\"ewl_orient\"/>\n";
    file << "\t\t</type>\n";
    file << "\t\t<type id=\"wall_comment\" for=\"edge\">\n";
    file << "\t\t\t<key attr.name=\"link_orient\" attr.type=\"int\" id=\"ewc_orient\"/>\n";
    file << "\t\t</type>\n";
    file << "\t\t<type id=\"wall_post\" for=\"edge\">\n";
    file << "\t\t\t<key attr.name=\"link_orient\" attr.type=\"int\" id=\"ewp_orient\"/>\n";
    file << "\t\t</type>\n";
    file << "\t\t<type id=\"photo_like\" for=\"edge\">\n";
    file << "\t\t\t<key attr.name=\"link_orient\" attr.type=\"int\" id=\"ephl_orient\"/>\n";
    file << "\t\t</type>\n";
    file << "\t\t<type id=\"in_community\" for=\"edge\">\n";
    file << "\t\t\t<key attr.name=\"link_orient\" attr.type=\"int\" id=\"incom_orient\"/>\n";
    file << "\t\t</type>\n";
    file << "\t\t<type id=\"mutual_friends\" for=\"edge\">\n";
    file << "\t\t\t<key attr.name=\"link_orient\" attr.type=\"int\" id=\"mf_orient\"/>\n";
    file << "\t\t\t<key attr.name=\"friends_count\" attr.type=\"int\" id=\"mf_count\"/>\n";
    file << "\t\t</type>\n";
    file << "\t</description>\n";
    file << "\t<graph edgedefault=\"directed\">\n";
    file.close();
}

void Writer::WriteNodes()
{
    for (int i = 0; i < m_p.m_persons.size(); i++)
    {
        for (int j = 0; j < m_p.m_persons[i].size(); j++)
        {
            WritePersonNode(m_p.m_persons[i][j]);
        }
    }
    WriteCommunityNodes();
}

void Writer::WritePersonNode(Person p)
{
    std::ofstream file;
    file.open(m_filename.c_str(), std::ios_base::app);
    file << "\t\t<node id=\"np" << p.m_id << "\" type=\"person\">\n";
    file << "\t\t\t<data key=\"Icon_Name\">" << p.m_id % 6 + 1 << "</data>\n";
    file << "\t\t\t<data key=\"np_id\">" << p.m_id << "</data>\n";
    file << "\t\t\t<data key=\"np_fn\">" << p.m_fn << "</data>\n";
    file << "\t\t\t<data key=\"np_ln\">" << p.m_ln << "</data>\n";
    file << "\t\t\t<data key=\"np_ph\">" << p.m_ph << "</data>\n";
    file << "\t\t\t<data key=\"np_closed\">" << p.m_closed << "</data>\n";
    file << "\t\t\t<data key=\"np_bd\">" << p.m_bd << "</data>\n";
    file << "\t\t\t<data key=\"np_country\">" << p.m_country << "</data>\n";
    file << "\t\t\t<data key=\"np_city\">" << p.m_city << "</data>\n";
    file << "\t\t\t<data key=\"np_ht\">" << p.m_ht << "</data>\n";
    file << "\t\t\t<data key=\"np_sch\">" << p.m_sch << "</data>\n";
    file << "\t\t\t<data key=\"np_uni\">" << p.m_uni << "</data>\n";
    file << "\t\t\t<data key=\"np_fac\">" << p.m_fac << "</data>\n";
    file << "\t\t\t<data key=\"np_pc\">" << p.m_wallPostsCount << "</data>\n";
    file << "\t\t</node>\n";
    file.close();
}

void Writer::WriteCommunityNodes()
{
    std::ofstream file;
    file.open(m_filename.c_str(), std::ios_base::app);
    for (auto& it: m_p.m_presentCommunities)
    {
        file << "\t\t<node id=\"nc" << it.first << "\" type=\"community\">\n";
        file << "\t\t\t<data key=\"nc_id\">" << it.first << "</data>\n";
        file << "\t\t\t<data key=\"nc_count\">" << it.second << "</data>\n";
        file << "\t\t</node>\n";
    }
    file.close();
}

void Writer::WriteEdges()
{
    std::cout << "\t\twrite likes\n";
    WriteEdgesLikes();
    std::cout << "\t\twrite comments\n";
    WriteEdgesComments();
    std::cout << "\t\twrite posts from others\n";
    WriteEdgesPostsO();
    std::cout << "\t\twrite photo likes\n";
    WriteEdgesPhotosLikes();
    std::cout << "\t\twrite communities\n";
    WriteEdgesCommunities();
    std::cout << "\t\twrite mutual counts\n";
    WriteMutualFriends();
}


void Writer::WriteEdgesLikes()
{
    for (int i = 0; i < m_p.m_persons.size(); i++)
    {
        for (int j = 0; j < m_p.m_persons[i].size(); j++)
        {
            WritePersonEdgesLikes(m_p.m_persons[i][j]);
        }
    }
}

void Writer::WritePersonEdgesLikes(Person p)
{
    std::ofstream file;
    file.open(m_filename.c_str(), std::ios_base::app);
    for (int i = 0; i < p.m_wallLikes.size(); i++)
    {
        file << "\t\t<edge id=\"ewl" << p.m_id << "_" << i << "\" ";
        file << "source=\"np" << p.m_id << "\" ";
        file << "target=\"np" << p.m_wallLikes[i] << "\" ";
        file << "type=\"wall_like\">\n";
        file << "\t\t\t<data key=\"ewl_orient\">1</data>\n";
        file << "\t\t</edge>\n";
    }
    file.close();
}

void Writer::WriteEdgesComments()
{
    for (int i = 0; i < m_p.m_persons.size(); i++)
    {
        for (int j = 0; j < m_p.m_persons[i].size(); j++)
        {
            WritePersonEdgesComments(m_p.m_persons[i][j]);
        }
    }
}

void Writer::WritePersonEdgesComments(Person p)
{
    std::ofstream file;
    file.open(m_filename.c_str(), std::ios_base::app);
    for (int i = 0; i < p.m_wallComments.size(); i++)
    {
        file << "\t\t<edge id=\"ewc" << p.m_id << "_" << i << "\" ";
        file << "source=\"np" << p.m_id << "\" ";
        file << "target=\"np" << p.m_wallComments[i] << "\" ";
        file << "type=\"wall_comment\">\n";
        file << "\t\t\t<data key=\"ewc_orient\">1</data>\n";
        file << "\t\t</edge>\n";
    }
    file.close();
}

void Writer::WriteEdgesPostsO()
{
    for (int i = 0; i < m_p.m_persons.size(); i++)
    {
        for (int j = 0; j < m_p.m_persons[i].size(); j++)
        {
            WritePersonEdgesPostsO(m_p.m_persons[i][j]);
        }
    }
}

void Writer::WritePersonEdgesPostsO(Person p)
{
    std::ofstream file;
    file.open(m_filename.c_str(), std::ios_base::app);
    for (int i = 0; i < p.m_wallPostsO.size(); i++)
    {
        file << "\t\t<edge id=\"ewp" << p.m_id << "_" << i << "\" ";
        file << "source=\"np" << p.m_id << "\" ";
        file << "target=\"np" << p.m_wallPostsO[i] << "\" ";
        file << "type=\"wall_post\">\n";
        file << "\t\t\t<data key=\"ewp_orient\">1</data>\n";
        file << "\t\t</edge>\n";
    }
    file.close();
}

void Writer::WriteEdgesPhotosLikes()
{
    for (int i = 0; i < m_p.m_persons.size(); i++)
    {
        for (int j = 0; j < m_p.m_persons[i].size(); j++)
        {
            WritePersonEdgesPhotosLikes(m_p.m_persons[i][j]);
        }
    }
}

void Writer::WritePersonEdgesPhotosLikes(Person p)
{
    std::ofstream file;
    file.open(m_filename.c_str(), std::ios_base::app);
    for (int i = 0; i < p.m_photosLikes.size(); i++)
    {
        file << "\t\t<edge id=\"ephl" << p.m_id << "_" << i << "\" ";
        file << "source=\"np" << p.m_id << "\" ";
        file << "target=\"np" << p.m_photosLikes[i] << "\" ";
        file << "type=\"photo_like\">\n";
        file << "\t\t\t<data key=\"ephl_orient\">1</data>\n";
        file << "\t\t</edge>\n";
    }
    file.close();
}

void Writer::WriteEdgesCommunities()
{
    for (int i = 0; i < m_p.m_persons.size(); i++)
    {
        for (int j = 0; j < m_p.m_persons[i].size(); j++)
        {
            WritePersonEdgesCommunities(m_p.m_persons[i][j]);
        }
    }
}

void Writer::WritePersonEdgesCommunities(Person p)
{
    std::ofstream file;
    file.open(m_filename.c_str(), std::ios_base::app);
    int count = 0;
    for (auto const& it : p.m_communities)
    {
        file << "\t\t<edge id=\"eic" << it.first << "_" << count << "\" ";
        file << "source=\"np" << p.m_id << "\" ";
        file << "target=\"nc" << it.first << "\" ";
        file << "type=\"in_community\">\n";
        file << "\t\t\t<data key=\"incom_orient\">0</data>\n";
        file << "\t\t</edge>\n";
        count ++;
    }
    file.close();
}

void Writer::WriteMutualFriends()
{
    std::ofstream file;
    file.open(m_filename.c_str(), std::ios_base::app);
    for (auto& it: m_p.m_mutualFriends)
    {
        int count = 0;
        for (auto& it2 : it.second)
        {
            file << "\t\t<edge id=\"emf" << it.first << "_" << count << "\" ";
            file << "source=\"np" << it.first << "\" ";
            file << "target=\"np" << it2[0] << "\" ";
            file << "type=\"mutual_friends\">\n";
            file << "\t\t\t<data key=\"mf_orient\">3</data>\n";
            file << "\t\t\t<data key=\"mf_count\">" << it2[1] << "</data>\n";
            file << "\t\t</edge>\n";
            count++;
        }
    }
    file.close();
}

void Writer::WriteClose()
{
    std::ofstream file;
    file.open(m_filename.c_str(), std::ios_base::app);
    file << "\t</graph>\n";
    file << "</avs>";
    file.close();
}
