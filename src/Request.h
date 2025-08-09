#pragma once
#include <iostream>
#include <string>
#include <curl/curl.h>


class Request
{
public:
    Request();
    ~Request();

    std::string createRequest(const std::string& url) const;

private:
    std::string baseURL = "https://api.jolpi.ca/ergast/f1/2025/races/";     //"https://api.jolpi.ca/ergast/f1/2025/driverstandings/"
    CURL* curl; // why static again?

    static size_t callbackFunc(void *contents, size_t size, size_t nmemb, void *userp);
};