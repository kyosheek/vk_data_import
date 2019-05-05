//
//  util.cpp
//  vk_graphs
//
//  Created by Даниил on 29/03/2019.
//  Copyright © 2019 kyoshee. All rights reserved.
//

#include "util.h"
#include "curl/curl.h"

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append( (char*)contents, size * nmemb);
    return size * nmemb;
}

std::string PerformCurlRequest(std::string request)
{
    std::string a = "";
    CURL *curl;
    CURLcode res;
    
    curl = curl_easy_init();
    if ( curl )
    {
        curl_easy_setopt( curl, CURLOPT_URL, request.c_str() );
        curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, &WriteCallback );
        curl_easy_setopt( curl, CURLOPT_WRITEDATA, &a );
        res = curl_easy_perform( curl );
        curl_easy_cleanup( curl );
        return a;
    }
    else
    {
        curl_easy_cleanup( curl );
        return "CURL init error";
    }
}

int CountMutual(std::vector<int> a, std::vector<int> b)
{
    int count = 0;
    if (a.size() < b.size())
    {
        for (auto &i: a)
        {
            if (std::find(b.begin(), b.end(), i) != b.end())
            {
                count++;
            }
        }
    }
    else
    {
        for (auto &i: b)
        {
            if (std::find(a.begin(), a.end(), i) != a.end())
            {
                count++;
            }
        }
    }
    return count;
}
