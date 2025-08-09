#include "src/Request.h"
#include "src/Response.h"

int main()
{
    const std::string url = "https://api.jolpi.ca/ergast/f1/2025/driverstandings/";

    const Request request1;
    const std::string file = request1.createRequest(url);
    Response::createResponse(file); // we use this notation because this static function is apart of the class itself NOT of an object of this class.
}
