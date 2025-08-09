#include "src/Request.h"
#include "src/Response.h"

int main()
{
    // /f1/2025/last/results/
    // https://api.jolpi.ca/ergast/f1/2021/last/results/
    // //"https://api.jolpi.ca/ergast/f1/2025/driverstandings/"
    const std::string url = "https://api.jolpi.ca/ergast/f1/2025/constructorstandings/";

    const Request request1;
    const std::string file = request1.createRequest(url);
    Response::createResponse3(file); // we use this notation because this static function is apart of the class itself NOT of an object of this class.
}
