#include "Request.h"

size_t Request::callbackFunc(void *contents, size_t size, size_t nmemb, void *userp)
{
    static_cast<std::string *>(userp)->append(static_cast<char *>(contents), size * nmemb); // this creates the appropriate space for our buffer.
    return size * nmemb;
}

Request::Request(): curl(curl_easy_init()) {}

Request::~Request() {curl_easy_cleanup(curl);}


std::string Request::createRequest(const std::string& url) const
{
    if (!curl)
    {
        std::cerr << "curl_easy_init failed" << std::endl;
    }

    std::string response;

    try
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackFunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode result = curl_easy_perform(curl);

        if (result != CURLE_OK) // result is just tell us if our request was done. Does not write response here.
        {
            std::cerr << "Request failed: " << curl_easy_strerror(result) << std::endl;
            throw std::runtime_error("HTTP request failed: " + std::string(curl_easy_strerror(result)));
        }

    } catch (const std::exception& e)
    {
        std::cerr << "an error occurred: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "unknown exception" << e.what() <<  std::endl;
    }

    return response;
}




