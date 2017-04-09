#include <iostream>
#include <vector>

#include "HTTPLib.h"

namespace HttpLib{
HTTPResponse::HTTPResponse()
{
    contentType = "text/plain";
}

HTTPResponse::~HTTPResponse()
{
    this->m_SendOutput();
}

void HTTPResponse::m_SendOutput()
{
    std::cout << "Content-Type: " << contentType << "\n\n"; 
    for(std::vector<std::string>::iterator it = response.begin();it != response.end();++it){
        std::cout << *it;
    }
}

void HTTPResponse::setContentType(std::string str)
{
    contentType = str;
}

void HTTPResponse::write(std::string str)
{
    response.push_back(str);
}
};
