#include <iostream>
#include <vector>

#include "HTTPLib.h"

namespace HttpLib{
HTTPResponse::HTTPResponse()
{
    contentType = "text/plain";

    m_HeaderSent = false;
}

HTTPResponse::~HTTPResponse()
{
    this->flush();
}

void HTTPResponse::redirect(std::string url)
{
    if(m_HeaderSent){
        std::cout << "Headers already sent" << std::endl;
        return;
   }
    std::cout << "Location: " << url << "\n\n";
}

void HTTPResponse::flush()
{
    if(response.size() > 0){

        if(m_HeaderSent){
            std::cout << "Headers already sent" << std::endl;
            return;
        }

        std::cout << "Content-Type: " << contentType << "\n\n"; 
        for(std::vector<std::string>::iterator it = response.begin();it != response.end();++it){
            std::cout << *it;
        }

        m_HeaderSent = true;

        response.clear();
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
