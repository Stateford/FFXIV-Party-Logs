#include "request.h"

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>


using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

namespace Request
{
    void get(std::wstring url, std::wstring &returnedBody)
    {
        http_client client(url);

        client.request(methods::GET).then([&](http_response response)
        {
            if (response.status_code() == status_codes::OK)
            {
                auto body = response.extract_string().get();
                // std::wcout << body;
                returnedBody = body;
            }
        }).wait();
    }
}