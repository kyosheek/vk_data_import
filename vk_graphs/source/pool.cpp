//
//  pool.cpp
//  vk_graphs
//
//  Created by Даниил on 30/03/2019.
//  Copyright © 2019 kyoshee. All rights reserved.
//

#include <algorithm>
#include <iostream>

#include "pool.h"
#include "json.hpp"
#include "util.h"

using json = nlohmann::json;

void Pool::SetStart(Person p)
{
    m_start = p;
    m_presentIds.push_back(p.m_id);
}

void Pool::SetDepth(int d)
{
    m_depth = d;
}

void Pool::Gather()
{
    m_persons.push_back({});
    //std::cout << "gather by likes\n";
    GatherByLikes(-1, 0);
    //std::cout << "present ids: ";
    //std::cout << m_presentIds.size() << std::endl;
    //std::cout << "gather by comments\n";
    GatherByComments(-1, 0);
    //std::cout << "present ids: " << m_presentIds.size() << std::endl;
    //std::cout << "gather by wall posts\n";
    GatherByPosts(-1, 0);
    //std::cout << "present ids: " << m_presentIds.size() << std::endl;
    //std::cout << "gather by photo likes\n";
    GatherByPhotosLikes(-1, 0);
    //std::cout << "present ids: " << m_presentIds.size() << std::endl;
    //std::cout << "gather by friends\n";
    GatherByFriends(-1, 0);
    //std::cout << "present ids: " << m_presentIds.size() << std::endl;
    if (!m_persons[0].empty())
    {
        std::cout << "persons on depth 1 : " << m_persons[0].size() << std::endl;
    }
    for (int i = 0; i < m_depth - 1; i++)
    {
        if (!m_persons[i].empty())
        {
            std::cout << "DEPTH : " << i+1 << std::endl;
            m_persons.push_back({});
            for (int j = 0; j < m_persons[i].size(); j++)
            {
                std::cout << j << "||";
                //std::cout << "gather by likes\n";
                GatherByLikes(i, j);
                //std::cout << "present ids: " << m_presentIds.size() << std::endl;
                //std::cout << "gather by comments\n";
                GatherByComments(i, j);
                //std::cout << "present ids: " << m_presentIds.size() << std::endl;
                //std::cout << "gather by wall posts\n";
                GatherByPosts(i, j);
                //std::cout << "present ids: " << m_presentIds.size() << std::endl;
                //std::cout << "gather by photo likes\n";
                GatherByPhotosLikes(i, j);
                //std::cout << "present ids: " << m_presentIds.size() << std::endl;
                //std::cout << "gather by friends\n";
                GatherByFriends(i, j);
                //std::cout << "present ids: " << m_presentIds.size() << std::endl;
            }
        }
    }
    //std::cout << "check for matches on last depth\n";
    CheckMatches();
    //std::cout << "add communities\n";
    AddCommunities();
    //std::cout << "count mutual friends\n";
    CountMutualFriends();
    //std::cout << "END OF POOL\n";
}

void Pool::GatherByFriends(int depth, int pos)
{
    std::vector<Person> tmp;
    if (depth == -1)
    {
        //std::cout << "persons on friends : " << m_start.m_friends.size() << std::endl;
        for (auto& it : m_start.m_friends)
        {
            if (std::find(m_presentIds.begin(), m_presentIds.end(), it) == m_presentIds.end())
            {
                tmp.push_back(Person(it));
                m_presentIds.push_back(it);
            }
        }
    }
    else
    {
        if (depth != m_depth - 1)
        {
            //std::cout << "persons on friends : " << m_persons[depth][pos].m_friends.size() << std::endl;
            for (auto& it : m_persons[depth][pos].m_friends)
            {
                if (std::find(m_presentIds.begin(), m_presentIds.end(), it) == m_presentIds.end())
                {
                    tmp.push_back(Person(it));
                    m_presentIds.push_back(it);
                }
            }
        }
    }
    m_persons[depth + 1].insert(std::end(m_persons[depth + 1]), std::begin(tmp), std::end(tmp));
    for (auto& it : tmp)
    {
        it.Clear();
    }
    tmp.clear();
}

void Pool::GatherByLikes(int depth, int pos)
{
    std::vector<Person> tmp;
    if (depth == -1)
    {
        //std::cout << "persons on wall likes : " << m_start.m_wallLikes.size() << std::endl;
        for (int i = 0; i < m_start.m_wallLikes.size(); i++)
        {
            if (std::find(m_presentIds.begin(), m_presentIds.end(), m_start.m_wallLikes[i]) == m_presentIds.end())
            {
                tmp.push_back(Person(m_start.m_wallLikes[i]));
                m_presentIds.push_back(m_start.m_wallLikes[i]);
            }
        }
    }
    else
    {
        if (depth != m_depth - 1)
        {
            //std::cout << "persons on wall likes : " << m_persons[depth][pos].m_wallLikes.size() << std::endl;
            for (int i = 0; i < m_persons[depth][pos].m_wallLikes.size(); i++)
            {
                if (std::find(m_presentIds.begin(), m_presentIds.end(), m_persons[depth][pos].m_wallLikes[i]) == m_presentIds.end())
                {
                    tmp.push_back(Person(m_persons[depth][pos].m_wallLikes[i]));
                    m_presentIds.push_back(m_persons[depth][pos].m_wallLikes[i]);
                }
            }
        }
    }
    m_persons[depth + 1].insert(std::end(m_persons[depth + 1]), std::begin(tmp), std::end(tmp));
    for (auto& it : tmp)
    {
        it.Clear();
    }
    tmp.clear();
}

void Pool::GatherByComments(int depth, int pos)
{
    std::vector<Person> tmp;
    if (depth == -1)
    {
        //std::cout << "persons on wall comments : " << m_start.m_wallComments.size() << std::endl;
        for (int i = 0; i < m_start.m_wallComments.size(); i++)
        {
            if (std::find(m_presentIds.begin(), m_presentIds.end(), m_start.m_wallComments[i]) == m_presentIds.end())
            {
                tmp.push_back(Person(m_start.m_wallComments[i]));
                m_presentIds.push_back(m_start.m_wallComments[i]);
            }
        }
    }
    else
    {
        if (depth != m_depth - 1)
        {
            //std::cout << "persons on wall comments : " << m_persons[depth][pos].m_wallComments.size() << std::endl;
            for (int i = 0; i < m_persons[depth][pos].m_wallComments.size(); i++)
            {
                if (std::find(m_presentIds.begin(), m_presentIds.end(), m_persons[depth][pos].m_wallComments[i]) == m_presentIds.end())
                {
                    tmp.push_back(Person(m_persons[depth][pos].m_wallComments[i]));
                    m_presentIds.push_back(m_persons[depth][pos].m_wallComments[i]);
                }
            }
        }
    }
    m_persons[depth + 1].insert(std::end(m_persons[depth + 1]), std::begin(tmp), std::end(tmp));
    for (auto& it : tmp)
    {
        it.Clear();
    }
    tmp.clear();
}

void Pool::GatherByPosts(int depth, int pos)
{
    std::vector<Person> tmp;
    if (depth == -1)
    {
        //std::cout << "persons on wall posts : " << m_start.m_wallPostsO.size() << std::endl;
        for (int i = 0; i < m_start.m_wallPostsO.size(); i++)
        {
            if (std::find(m_presentIds.begin(), m_presentIds.end(), m_start.m_wallPostsO[i]) == m_presentIds.end())
            {
                tmp.push_back(Person(m_start.m_wallPostsO[i]));
                m_presentIds.push_back(m_start.m_wallPostsO[i]);
            }
        }
    }
    else
    {
        if (depth != m_depth - 1)
        {
            //std::cout << "persons on wall posts : " << m_persons[depth][pos].m_wallPostsO.size() << std::endl;
            for (int i = 0; i < m_persons[depth][pos].m_wallPostsO.size(); i++)
            {
                if (std::find(m_presentIds.begin(), m_presentIds.end(), m_persons[depth][pos].m_wallPostsO[i]) == m_presentIds.end())
                {
                    tmp.push_back(Person(m_persons[depth][pos].m_wallPostsO[i]));
                    m_presentIds.push_back(m_persons[depth][pos].m_wallPostsO[i]);
                }
            }
        }
    }
    m_persons[depth + 1].insert(std::end(m_persons[depth + 1]), std::begin(tmp), std::end(tmp));
    for (auto& it : tmp)
    {
        it.Clear();
    }
    tmp.clear();
}

void Pool::GatherByPhotosLikes(int depth, int pos)
{
    std::vector<Person> tmp;
    if (depth == -1)
    {
        //std::cout << "persons on photo likes : " << m_start.m_photosLikes.size() << std::endl;
        for (int i = 0; i < m_start.m_photosLikes.size(); i++)
        {
            if (std::find(m_presentIds.begin(), m_presentIds.end(), m_start.m_photosLikes[i]) == m_presentIds.end())
            {
                tmp.push_back(Person(m_start.m_photosLikes[i]));
                m_presentIds.push_back(m_start.m_photosLikes[i]);
            }
        }
    }
    else
    {
        if (depth != m_depth - 1)
        {
            //std::cout << "persons on photo likes : " << m_persons[depth][pos].m_photosLikes.size() << std::endl;
            for (int i = 0; i < m_persons[depth][pos].m_photosLikes.size(); i++)
            {
                if (std::find(m_presentIds.begin(), m_presentIds.end(), m_persons[depth][pos].m_photosLikes[i]) == m_presentIds.end())
                {
                    tmp.push_back(Person(m_persons[depth][pos].m_photosLikes[i]));
                    m_presentIds.push_back(m_persons[depth][pos].m_photosLikes[i]);
                }
            }
        }
    }
    m_persons[depth + 1].insert(std::end(m_persons[depth + 1]), std::begin(tmp), std::end(tmp));
    for (auto& it : tmp)
    {
        it.Clear();
    }
    tmp.clear();
}

void Pool::CheckMatches()
{
    for (int i = 0; i < m_persons[m_depth - 1].size(); i++)
    {
        CheckMatchesByLikes(&m_persons[m_depth - 1][i]);
        CheckMatchesByComments(&m_persons[m_depth - 1][i]);
        CheckMatchesByPosts(&m_persons[m_depth - 1][i]);
        CheckMatchesByPhotosLikes(&m_persons[m_depth - 1][i]);
    }
}

void Pool::CheckMatchesByLikes(Person* p)
{
    std::vector<int> tmp;
    for (int i = 0; i < p->m_wallLikes.size(); i++)
    {
        if (std::find(m_presentIds.begin(), m_presentIds.end(), p->m_wallLikes[i]) != m_presentIds.end())
        {
            tmp.push_back(p->m_wallLikes[i]);
        }
    }
    p->m_wallLikes.clear();
    p->m_wallLikes.insert(std::end(p->m_wallLikes), std::begin(tmp), std::end(tmp));
    tmp.clear();
}

void Pool::CheckMatchesByComments(Person* p)
{
    std::vector<int> tmp;
    for (int i = 0; i < p->m_wallComments.size(); i++)
    {
        if (std::find(m_presentIds.begin(), m_presentIds.end(), p->m_wallComments[i]) != m_presentIds.end())
        {
            tmp.push_back(p->m_wallComments[i]);
        }
    }
    p->m_wallComments.clear();
    p->m_wallComments.insert(std::end(p->m_wallComments), std::begin(tmp), std::end(tmp));
    tmp.clear();
}

void Pool::CheckMatchesByPosts(Person* p)
{
    std::vector<int> tmp;
    for (int i = 0; i < p->m_wallPostsO.size(); i++)
    {
        if (std::find(m_presentIds.begin(), m_presentIds.end(), p->m_wallPostsO[i]) != m_presentIds.end())
        {
            tmp.push_back(p->m_wallPostsO[i]);
        }
    }
    p->m_wallPostsO.clear();
    p->m_wallPostsO.insert(std::end(p->m_wallPostsO), std::begin(tmp), std::end(tmp));
    tmp.clear();
}

void Pool::CheckMatchesByPhotosLikes(Person* p)
{
    std::vector<int> tmp;
    for (int i = 0; i < p->m_photosLikes.size(); i++)
    {
        if (std::find(m_presentIds.begin(), m_presentIds.end(), p->m_photosLikes[i]) != m_presentIds.end())
        {
            tmp.push_back(p->m_photosLikes[i]);
        }
    }
    p->m_photosLikes.clear();
    p->m_photosLikes.insert(std::end(p->m_photosLikes), std::begin(tmp), std::end(tmp));
    tmp.clear();
}

void Pool::AddCommunities()
{
    for (auto const& it: m_start.m_communities)
    {
        m_presentCommunities[it.first] = it.second;
    }
    for (auto& i : m_persons)
    {
        for (auto& j : i)
        {
            for (auto const& k : j.m_communities)
            {
                if (m_presentCommunities.find(k.first) == m_presentCommunities.end())
                {
                    m_presentCommunities[k.first] = k.second;
                }
            }
        }
    }
}

void Pool::CountMutualFriends()
{
    std::array<int, 2> count = {};
    std::vector<std::array<int, 2>> all_count = {};
    
    for (int i = 0; i < m_persons.size(); i++)
    {
        for (int j = 0; j < m_persons[i].size(); j++)
        {
            if (!m_persons[i][j].m_closed)
            {
                count[0] = m_persons[i][j].m_id;
                count[1] = CountMutual(m_start.m_friends, m_persons[i][j].m_friends);
                all_count.push_back(count);
            }
        }
    }
    m_mutualFriends[m_start.m_id] = all_count;
    all_count.clear();
    
    for (int i = 0; i < m_persons.size(); i++)
    {
        for (int j = 0; j < m_persons[i].size(); j++)
        {
            if (!m_persons[i][j].m_closed)
            {
                int ii = i;
                int jj = j + 1;
                if (i != m_persons.size() - 1 && j != m_persons[i].size() - 1)
                {
                    if (j != m_persons[i].size() - 1)
                    {
                        ii = i;
                    }
                    else
                    {
                        ii = i+1;
                        jj = 0;
                    }
                    for (int k = ii; k < m_persons.size(); k++)
                    {
                        for (int l = jj; l < m_persons[k].size(); l++)
                        {
                            count[0] = m_persons[k][l].m_id;
                            count[1] = CountMutual(m_persons[i][j].m_friends, m_persons[k][l].m_friends);
                            all_count.push_back(count);
                        }
                    }
                }
                else
                {
                    break;
                }
                m_mutualFriends[m_persons[i][j].m_id] = all_count;
                all_count.clear();
            }
        }
    }
}
