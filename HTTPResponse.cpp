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

    // To prevent browser from returning error 500 for empty responses
    if(!m_HeaderSent){
        std::cout << "Content-Type: text/plain\n\n"; 
    }
}

void HTTPResponse::redirect(std::string url)
{
    if(m_HeaderSent){
        std::cout << "Headers already sent" << std::endl;
        return;
   }
    std::cout << "Location: " << url << "\n\n";
    m_HeaderSent = true;
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
