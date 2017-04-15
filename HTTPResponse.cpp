#include <iostream>
#include <vector>

#include "HTTPLib.h"

#define ENDLINE "\r\n\r\n"

namespace HttpLib{

const std::string HTTPResponse::TYPE_HTML       = "text/html";
const std::string HTTPResponse::TYPE_TEXT       = "text/plain";
const std::string HTTPResponse::TYPE_CSS        = "text/css";
const std::string HTTPResponse::TYPE_JAVASCRIPT = "application/javascript";
const std::string HTTPResponse::TYPE_JSON       = "application/json";
const std::string HTTPResponse::TYPE_ZIP        = "application/zip";
const std::string HTTPResponse::TYPE_PDF        = "application/pdf";
const std::string HTTPResponse::TYPE_XML        = "application/xml";
const std::string HTTPResponse::TYPE_MPEG       = "audio/mpeg";
const std::string HTTPResponse::TYPE_VORBIS     = "audio/vorbis";
const std::string HTTPResponse::TYPE_PNG        = "image/png";
const std::string HTTPResponse::TYPE_JPEG       = "image/jpeg";
const std::string HTTPResponse::TYPE_GIF        = "image/gif";

HTTPResponse::HTTPResponse()
{
    contentType = TYPE_HTML;

    m_HeaderSent = false;
}

HTTPResponse::~HTTPResponse()
{
    this->flush();

    // To prevent browser from returning error 500 for empty responses
    if(!m_HeaderSent){
        std::cout << TYPE_TEXT << ENDLINE; 
    }
}

void HTTPResponse::header(std::string str)
{
    if(m_HeaderSent){
        std::cout << "Headers already sent" << std::endl;
        return;
   }
    std::cout << str << ENDLINE;
    m_HeaderSent = true;
}

void HTTPResponse::redirect(std::string url)
{
    if(m_HeaderSent){
        std::cout << "Headers already sent" << std::endl;
        return;
   }
    std::cout << "Location: " << url << ENDLINE;
    m_HeaderSent = true;
}

void HTTPResponse::flush()
{
    if(response.size() > 0){

        if(m_HeaderSent){
            std::cout << "Headers already sent" << std::endl;
            return;
        }

        std::cout << "Content-Type: " << contentType << ENDLINE; 
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
