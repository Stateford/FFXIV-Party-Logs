#pragma once

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <string>

using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

namespace Request
{
    void get(std::wstring, std::wstring&);
}