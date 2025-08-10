#pragma once
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sstream>


class Request
{
public:
    Request();
    ~Request();

    std::string createRequest(const int& year, const std::string& endpoint) const;

private:
    std::string baseURL = "https://api.jolpi.ca/ergast/f1/";
    CURL* curl;
    static size_t callbackFunc(void *contents, size_t size, size_t nmemb, void *userp);
    std::string buildURL(const int& year, const std::string& endpoint) const;
};