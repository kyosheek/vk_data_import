//
//  man.cpp
//  vk_graphs
//
//  Created by Даниил on 29/03/2019.
//  Copyright © 2019 kyoshee. All rights reserved.
//

#include "Log.h"
#include "person.h"
#include "util.h"

#include "json.hpp"

using json = nlohmann::json;

Person::Person(int id)
{
    //std::cout << "ID : " << id <<std::endl;
    SetId(id);
    //std::cout << "\tget general\n";
    GetGeneral();
    if (!m_closed)
    {
        //std::cout << "\tget friends\n";
        GetFriends();
        //std::cout << "\tget links\n";
        GetLinks();
        //std::cout << "\t\tget groups\n";
        GetGroups();
    }
    else
    {
        //Log("Profile %d is closed\n", m_id);
    }
}

void Person::SetId(int id)
{
    m_id = id;
}

void Person::SetWallLikes(std::vector<int> v)
{
    m_wallLikes.clear();
    m_wallLikes = v;
}

void Person::SetWallComments(std::vector<int> v)
{
    m_wallComments.clear();
    m_wallComments = v;
}

void Person::SetWallPostsO(std::vector<int> v)
{
    m_wallPostsO.clear();
    m_wallPostsO = v;
}

void Person::SetPhotosLikes(std::vector<int> v)
{
    m_photosLikes.clear();
    m_photosLikes = v;
}

void Person::GetGeneral()
{
    std::string request = "https://api.vk.com/method/users.get?v=5.92&fields=photo_max_orig,is_closed,bdate,country,city,home_town,schools,universities&user_ids=";
    request += std::to_string(m_id);
    request += "&access_token=7aec11b67aec11b67aec11b6147a8b1cb677aec7aec11b6210289ad353de1fa28ed6b48";
    json j = json::parse(PerformCurlRequest(request));
    
    //std::cout << "\tfn||";
    m_fn = j["response"][0]["first_name"];
    
    if (m_fn == "DELETED")
    {
        //std::cout << "ln||";
        //Log("Profile %d is deleted\n", m_id);
        m_ln = "DELETED";
    }
    else if (j["response"][0]["last_name"].size() < 1)
    {
        //Log("No last name for %d\n", m_id);
        m_ln = "EMPTY";
    }
    else
    {
        m_ln = j["response"][0]["last_name"];
    }
    
    //std::cout << "bd||";
    if (j["response"][0]["bdate"] == nullptr)
    {
        //Log("Birth date for %d not specified\n", m_id);
        m_bd = "EMPTY";
    }
    else
    {
        m_bd = j["response"][0]["bdate"];
    }
    
    //std::cout << "ph||";
    m_ph = j["response"][0]["photo_max_orig"];
    
    //std::cout << "deact||";
    if (j["response"][0]["deactivated"] == nullptr)
    {
        m_closed = j["response"][0]["is_closed"];
    }
    else
    {
        //Log("Profile %d is deactivated\n", m_id);
        m_closed = true;
    }
    
    //std::cout << "country||";
    if (j["response"][0]["country"] == nullptr)
    {
        //Log("Country for profile %d is not specified\n", m_id);
        m_country = "EMPTY";
    }
    else if (j["response"][0]["country"]["title"] == nullptr)
    {
        //Log("Country for profile %d is not specified\n", m_id);
        m_country = "EMPTY";
    }
    else
    {
        m_country = j["response"][0]["country"]["title"];
    }
    
    //std::cout << "city||";
    if (j["response"][0]["city"] == nullptr)
    {
        //Log("City for profile %d is not specified\n", m_id);
        m_city = "EMPTY";
    }
    else if (j["response"][0]["city"]["title"] == nullptr)
    {
        //Log("City for profile %d is not specified\n", m_id);
        m_city = "EMPTY";
    }
    else
    {
        m_city = j["response"][0]["city"]["title"];
    }
    
    //std::cout << "ht||";
    if (j["response"][0]["hometown"] == nullptr)
    {
        //Log("Hometownfor profile %d is not specified\n", m_id);
        m_ht = "EMPTY";
    }
    else
    {
        m_ht = j["response"][0]["hometown"];
    }
    
    //std::cout << "sch||";
    if (j["response"][0]["schools"].size() < 1)
    {
        //Log("School for profile %d is not specified\n", m_id);
        m_sch = "EMPTY";
    }
    else
    {
        for (int i = 0; i < j["response"][0]["schools"].size(); i++)
        {
            std::string tmp = j["response"][0]["schools"][i]["id"];
            m_sch += tmp;
            if (i != j["response"][0]["schools"].size() - 1)
            {
                m_sch += ",";
            }
            tmp.clear();
        }
    }
    
    //std::cout << "uni+fac||\n";
    if (j["response"][0]["universities"].size() < 1)
    {
        //Log("University for profile %d is not specified\n", m_id);
        m_uni = "EMPTY";
        m_fac = "EMPTY";
    }
    else
    {
        for (int i = 0; i < j["response"][0]["universities"].size(); i++)
        {
            int tmp = j["response"][0]["universities"][i]["id"];
            m_uni += std::to_string(tmp);
            if (j["response"][0]["universities"][i]["faculty"] == nullptr)
            {
                //Log("Faculty for profile %d is not specified\n", m_id);
                m_fac += "EMPTY";
            }
            else
            {
                tmp = j["response"][0]["universities"][i]["faculty"];
                m_fac += std::to_string(tmp);
            }
            if (i != j["response"][0]["universities"].size() - 1)
            {
                m_uni += ",";
                m_fac += ",";
            }
        }
    }
    //std::cout << "\tend of general\n";
    j.clear();
    request.clear();
}

void Person::GetGroups()
{
    std::string request = "https://api.vk.com/method/users.getSubscriptions?v=5.92&access_token=7aec11b67aec11b67aec11b6147a8b1cb677aec7aec11b6210289ad353de1fa28ed6b48&count=200&extended=1&fields=members_count&user_id=";
    request += std::to_string(m_id);
    json j = json::parse(PerformCurlRequest(request));
    if (j["error"] == nullptr)
    {
        std::string tmpreq = request;
        int count = j["response"]["count"];
        int step = 0;
        int offset = 0;
        int cc = 0;
        while (count > 0)
        {
            if (step > 0)
            {
                tmpreq += "&offset=" + std::to_string(offset);
                j = json::parse(PerformCurlRequest(tmpreq));
            }
            if (count > 200)
            {
                cc = 200;
            }
            else
            {
                cc = count;
            }
            for (int k = 0; k < cc; k++)
            {
                if (j["response"]["items"][k]["members_count"] != nullptr)
                {
                    m_communities[j["response"]["items"][k]["id"]] = j["response"]["items"][k]["members_count"];
                }
            }
            step += 1;
            offset = step*200;
            count -= 200;
            tmpreq = request;
        }
        tmpreq.clear();
    }
    else
    {
        //Log("Unable to get groups for user %d\n", m_id);
    }
    j.clear();
    request.clear();
}

void Person::GetFriends()
{
    std::string request = "https://api.vk.com/method/friends.get?v=5.92&access_token=7aec11b67aec11b67aec11b6147a8b1cb677aec7aec11b6210289ad353de1fa28ed6b48&count=9999&user_id=";
    request += std::to_string(m_id);
    //std::cout << "\tgather friends for " << m_id << std::endl;
    json a = json::parse(PerformCurlRequest(request));
    if (a["response"]["items"] != nullptr)
    {
        std::vector<int> friends = a["response"]["items"];
        m_friends = friends;
        friends.clear();
    }
    a.clear();
    request.clear();
}

void Person::GetLinks()
{
    //std::cout << "\t\tget wall posts\n";
    GetWallPosts();
    if (!m_wallPosts.empty())
    {
        //std::cout << "\t\tget likes on wall\n";
        GetWallLikes();
        //std::cout << "\t\tget comments on wall\n";
        GetWallComments();
    }
    //std::cout << "\t\tget photos\n";
    GetPhotos();
    if (!m_photos.empty())
    {
        //std::cout << "\t\tget likes on photos\n";
        GetPhotosLikes();
    }
}

void Person::GetWallPosts()
{
    std::string request = "https://api.vk.com/method/wall.get?v=5.92&access_token=7aec11b67aec11b67aec11b6147a8b1cb677aec7aec11b6210289ad353de1fa28ed6b48&count=10&owner_id=";
    request += std::to_string(m_id);
    json j = json::parse(PerformCurlRequest(request));
    if (j["error"] == nullptr)
    {
        int count = j["response"]["count"];
        if (count > 10)
        {
            count = 10;
        }
        m_wallPostsCount = count;
        for (int i = 0; i < count; i++)
        {
            if (j["response"]["items"][i]["from_id"] == m_id)
            {
                m_wallPosts.push_back(j["response"]["items"][i]["id"]);
            }
            else
            {
                m_wallPostsO.push_back(j["response"]["items"][i]["from_id"]);
            }
        }
    }
    else
    {
        //Log("Unable to get wall posts for profile %d", m_id);
    }
    j.clear();
    request.clear();
}

void Person::GetWallLikes()
{
    std::string request = "https://api.vk.com/method/likes.getList?v=5.92&type=post&access_token=7aec11b67aec11b67aec11b6147a8b1cb677aec7aec11b6210289ad353de1fa28ed6b48&count=100&owner_id=";
    request += std::to_string(m_id);
    request += "&item_id=";
    for (int i = 0; i < m_wallPosts.size(); i++)
    {
        std::string tmpreq = request + std::to_string(m_wallPosts[i]);
        json j = json::parse(PerformCurlRequest(tmpreq));
        int count = j["response"]["count"];
        int step = 0;
        int offset = 0;
        int cc = 0;
        while (count > 0)
        {
            if (step > 0)
            {
                tmpreq += "&offset=" + std::to_string(offset);
                j = json::parse(PerformCurlRequest(tmpreq));
            }
            if (count > 100)
            {
                cc = 100;
            }
            else
            {
                cc = count;
            }
            for (int k = 0; k < cc; k++)
            {
                m_wallLikes.push_back(j["response"]["items"][k]);
            }
            step += 1;
            offset = step*100;
            count -= 100;
            tmpreq = request + std::to_string(m_wallPosts[i]);
        }
        j.clear();
        tmpreq.clear();
    }
    request.clear();
}

void Person::GetWallComments()
{
    std::string request = "https://api.vk.com/method/wall.getComments?v=5.92&access_token=7aec11b67aec11b67aec11b6147a8b1cb677aec7aec11b6210289ad353de1fa28ed6b48&sort=asc&need_likes=0&count=5&owner_id=";
    request += std::to_string(m_id);
    request += "&post_id=";
    for (int i = 0; i < m_wallPosts.size(); i++)
    {
        std::string tmpreq = request + std::to_string(m_wallPosts[i]);
        json j = json::parse(PerformCurlRequest(tmpreq));
        if (j["error"] == nullptr)
        {
            int count = j["response"]["count"];
            if (count > 5)
            {
                count = 5;
            }
            for (int k = 0; k < count; k++)
            {
                if (j["response"]["items"][k]["from_id"] != nullptr)
                {
                    m_wallComments.push_back(j["response"]["items"][k]["from_id"]);
                }
            }
        }
        else
        {
            //Log("Unable to get comments for post %d of profile %d\n", m_wallPosts[i], m_id);
        }
        j.clear();
        tmpreq.clear();
    }
    request.clear();
}

void Person::GetPhotos()
{
    std::string request = "https://api.vk.com/method/photos.get?v=5.92&access_token=7aec11b67aec11b67aec11b6147a8b1cb677aec7aec11b6210289ad353de1fa28ed6b48&album_id=profile&rev=1&count=2&owner_id=";
    request += std::to_string(m_id);
    json j = json::parse(PerformCurlRequest(request));
    if (j["error"] == nullptr)
    {
        int count = j["response"]["count"];
        if (count > 2)
        {
            count = 2;
        }
        for (int i = 0; i < count; i++)
        {
            if (j["response"]["items"][i]["id"] != nullptr)
            {
                m_photos.push_back(j["response"]["items"][i]["id"]);
            }
        }
    }
    else
    {
        //Log("Unable to get photos for profile %d\n", m_id);
    }
    j.clear();
    request.clear();
}

void Person::GetPhotosLikes()
{
    std::string request = "https://api.vk.com/method/likes.getList?v=5.92&type=photo&access_token=7aec11b67aec11b67aec11b6147a8b1cb677aec7aec11b6210289ad353de1fa28ed6b48&count=100&owner_id=";
    request += std::to_string(m_id);
    request += "&item_id=";
    for (int i = 0; i < m_photos.size(); i++)
    {
        std::string tmpreq = request + std::to_string(m_photos[i]);
        json j = json::parse(PerformCurlRequest(tmpreq));
        if (j["error"] == nullptr)
        {
            int count = j["response"]["count"];
            int step = 0;
            int offset = 0;
            int cc = 0;
            while (count > 0)
            {
                //std::cout << "\t\tstep: " << step << "\n";
                if (step > 0)
                {
                    tmpreq += "&offset=" + std::to_string(offset);
                    j = json::parse(PerformCurlRequest(tmpreq));
                }
                if (count > 100)
                {
                    cc = 100;
                }
                else
                {
                    cc = count;
                }
                for (int k = 0; k < cc; k++)
                {
                    m_photosLikes.push_back(j["response"]["items"][k]);
                }
                step += 1;
                offset = step*100;
                count -= 100;
                tmpreq = request + std::to_string(m_id) + "&item_id=" + std::to_string(m_photos[i]);
            }
        }
        j.clear();
        tmpreq.clear();
    }
    request.clear();
}

void Person::Clear()
{
    m_fn.clear(); m_ln.clear(); m_bd.clear(); m_ph.clear(); m_country.clear(); m_city.clear(); m_ht.clear(); m_uni.clear(); m_fac.clear(); m_sch.clear();
    m_friends.clear();
    m_wallPosts.clear();
    m_wallLikes.clear();
    m_wallComments.clear();
    m_wallPostsO.clear();
    m_photosLikes.clear();
    m_communities.clear();
}
