#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <cstdio>
//#include <sstream>

#include "HTTPLib.h"

namespace HttpLib{

const std::string HTTPRequest::m_MultipartMime          = "multipart/form-data";
const std::string HTTPRequest::m_MultipartBoundaryStart = "boundary=";

HTTPRequest::HTTPRequest()
{
    

    m_RequestMethod  = (getenv("REQUEST_METHOD") != NULL)?getenv("REQUEST_METHOD"):"";
    m_PathInfo       = (getenv("PATH_INFO") != NULL)?getenv("PATH_INFO"):"";
    m_PathTranslated = (getenv("PATH_TRANSLATED") != NULL)?getenv("PATH_TRANSLATED"):"";
    m_ScriptName     = (getenv("SCRIPT_NAME") != NULL)?getenv("SCRIPT_NAME"):""; 
    m_QueryString    = (getenv("QUERY_STRING") != NULL)?getenv("QUERY_STRING"):"";
    m_RemoteHost     = (getenv("REMOTE_HOST") != NULL)?getenv("REMOTE_HOST"):"";
    m_ContentType    = (getenv("CONTENT_TYPE") != NULL)?getenv("CONTENT_TYPE"):"";
    m_ContentLength  = (getenv("CONTENT_LENGTH") != NULL)?getenv("CONTENT_LENGTH"):"0";
    m_HttpUserAgent  = (getenv("HTTP_USER_AGENT") != NULL)?getenv("HTTP_USER_AGENT"):"";
    m_HttpAccept     = (getenv("HTTP_ACCEPT") != NULL)?getenv("HTTP_ACCEPT"):"";
    
    m_pMultipartData = NULL;
    m_isMultipart    = false;
    //std::string c("REQUEST");
    if(m_RequestMethod.compare("GET") == 0){
        this->mParseQueryString();
    }else if(m_RequestMethod.compare("POST") == 0){
        if(m_ContentType.find(m_MultipartMime) == std::string::npos){
            std::cin >> m_QueryString;
            this->mParseQueryString();
        }else{
            //Multipart form submission
            //TODO Error checking
            m_isMultipart = true;
            int len = ::atoi(m_ContentLength.c_str());
            m_pMultipartData = (char *)malloc(sizeof(char) * len);
            ::fread(m_pMultipartData, sizeof(char), len, stdin);
            //fflush(stdin);
            std::cout << "Content-Type: text/plain\r\n\r\n";
            std::cout << m_pMultipartData << std::endl;
            std::cout << "DATALEN" << strlen(m_pMultipartData) << std::endl;
            int bpos = m_ContentType.find(m_MultipartBoundaryStart);
            m_MultipartBoundary = m_ContentType.substr(bpos + m_MultipartBoundaryStart.length());
            //multipart/form-data; boundary=---------------------------1902646541629952042542318893
            //-----------------------------1902646541629952042542318893
            mParseMultipartData();
        }
        /*int len = ::atoi(m_ContentLength.c_str());
        char buff[len];
        ::fread(buff, len, 1, stdin);
        std::cout << "Content-Type: text/plain\r\n\r\n";
        std::cout << buff << std::endl;*/
    } 
}

HTTPRequest::~HTTPRequest()
{
   if(m_isMultipart){
    ::free(m_pMultipartData);
   } 
    
}

void HTTPRequest::mParseMultipartData()
{
    std::string::size_type start_pos = 0, end_pos;
    std::string param;
    char *token;
    unsigned int start = 0;
    
    std::cout << "---------------------------------- <br />";
    std::cout << "TOKEN LEN " << m_MultipartBoundary.length() << "ENDL " << m_MultipartBoundary << std::endl;
    
    while((token = strstr(&m_pMultipartData[start], m_MultipartBoundary.c_str())) != NULL){
        std::cout << "TOKEN " << token << "ENDTOKEN";
        
        start += m_MultipartBoundary.length();
        //Split data into new lines until the boundary is reached
    }
    
    std::cout << m_pMultipartData << std::endl;
    std::cout << "DATALEN" << strlen(m_pMultipartData) << std::endl;
    //std::cout << boundary << "\n\n";

    /*while((end_pos = m_pMultipartData.find(boundary, start_pos)) != std::string::npos){
        param = m_pMultipartData.substr(start_pos, boundary.length() + (end_pos - start_pos));
        start_pos = end_pos + 1;
        std::cout << param;
    }

    //reading the ending segment
    if(m_pMultipartData.size() > start_pos){
        //std::cout << m_QueryString.substr(start_pos) << std::endl;
        param = m_pMultipartData.substr(boundary.length() + start_pos);
        std::cout << param;
    }*/
}

void HTTPRequest::mParseQueryString()
{
    std::string::size_type start_pos = 0, end_pos;
    std::string param;

    while((end_pos = m_QueryString.find('&', start_pos)) != std::string::npos){
        param = m_QueryString.substr(start_pos, (end_pos - start_pos));
        //std::cout << param << std::endl;
        start_pos = end_pos + 1;
        std::vector<std::string> list = this->mGetValuePair(param);
        //std::cout << list[0] << std::endl;
        //std::cout << list[1] << std::endl;
        pairs.insert(std::pair<std::string, std::string>(list[0], list[1]));
    }

    //reading the ending segment
    if(m_QueryString.size() > start_pos){
        //std::cout << m_QueryString.substr(start_pos) << std::endl;
        param = m_QueryString.substr(start_pos);
        std::vector<std::string> list = this->mGetValuePair(param);
        pairs.insert(std::pair<std::string, std::string>(list[0], list[1]));
    }
}

std::string HTTPRequest::getParameter(std::string key)
{
    std::map<std::string, std::string>::iterator it;

    it = pairs.find(key);
    if(it != pairs.end())
        return it->second;

    return "";
}

std::string HTTPRequest::mDecodeHtml(std::string str)
{
    std::string entity_chars[] = {" ", "!", "\"", "#", 
                                  "$", "%", "&", "'", 
                                  "(", ")", "*", "+", 
                                  ",", "-", ".", "/"};
    
    std::string::size_type start_pos = 0, end_pos;
    
    /*for(std::map<std::string, std::string>::iterator it = escape_chars.begin();it != escape_chars.end();++it){
            while((end_pos = str.find(it->first, start_pos)) != std::string::npos){
                str.replace(end_pos, 3, it->second);
                start_pos = end_pos + 1;
            }
    }*/
    //Removing the '+' char
    while((end_pos = str.find("+", start_pos)) != std::string::npos){
        str.replace(end_pos, 1, " ");
        start_pos = end_pos + 1;
    }

    start_pos = 0;

    while((end_pos = str.find("%", start_pos)) != std::string::npos){
        std::string segment = str.substr(end_pos + 1, 2);
        int entity = ::atoi(segment.c_str());
        /*std::stringstream ss;
        ss << entity_chars[entity - 20];
        str.replace(end_pos, 3, ss.str());*/
        str.replace(end_pos, 3, entity_chars[entity - 20]);
        start_pos = end_pos + 1;
    }

    return str;
}

std::vector<std::string> HTTPRequest::mGetValuePair(std::string str)
{
    std::vector<std::string> pair;
    std::string::size_type pos = 0;
    std::string key, value;

    pos = str.find('=', 0);
    if(pos != std::string::npos){
        key = str.substr(0, pos);
        value = str.substr(pos + 1);
    }
    // Decode html entities here
    //if(this->getRequestMethod().compare("GET") == 0){
        key   = this->mDecodeHtml(key);
        value = this->mDecodeHtml(value);
    //}
    
    pair.push_back(key);
    pair.push_back(value);

    return pair;
}

std::string HTTPRequest::getRequestMethod(){return m_RequestMethod;}
std::string HTTPRequest::getPathInfo(){return m_PathInfo;}
std::string HTTPRequest::getPathTranslated(){return m_PathTranslated;}
std::string HTTPRequest::getScriptName(){return m_ScriptName;}
std::string HTTPRequest::getQueryStringRaw(){return m_QueryString;}
std::string HTTPRequest::getRemoteHost(){return m_RemoteHost;}
std::string HTTPRequest::getContentType(){return m_ContentType;}
std::string HTTPRequest::getContentLength(){return m_ContentLength;}
std::string HTTPRequest::getHTTPUserAgent(){return m_HttpUserAgent;}
std::string HTTPRequest::getHttpAccept(){return m_HttpAccept;}

};

