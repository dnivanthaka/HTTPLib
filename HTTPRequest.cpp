#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>

#include "HTTPLib.h"

namespace HttpLib{

HTTPRequest::HTTPRequest()
{
    m_RequestMethod  = (getenv("REQUEST_METHOD") != NULL)?getenv("REQUEST_METHOD"):"";
    m_PathInfo       = (getenv("PATH_INFO") != NULL)?getenv("PATH_INFO"):"";
    m_PathTranslated = (getenv("PATH_TRANSLATED") != NULL)?getenv("PATH_TRANSLATED"):"";
    m_ScriptName     = (getenv("SCRIPT_NAME") != NULL)?getenv("SCRIPT_NAME"):""; 
    m_QueryString    = (getenv("QUERY_STRING") != NULL)?getenv("QUERY_STRING"):"";
    m_RemoteHost     = (getenv("REMOTE_HOST") != NULL)?getenv("REMOTE_HOST"):"";
    m_ContentType    = (getenv("CONTENT_TYPE") != NULL)?getenv("CONTENT_TYPE"):"";
    m_ContentLength  = (getenv("CONTENT_LENGTH") != NULL)?getenv("CONTENT_LENGTH"):"";
    m_HttpUserAgent  = (getenv("HTTP_USER_AGENT") != NULL)?getenv("HTTP_USER_AGENT"):"";
    m_HttpAccept     = (getenv("HTTP_ACCEPT") != NULL)?getenv("HTTP_ACCEPT"):"";
    //std::string c("REQUEST");
    if(m_RequestMethod.compare("GET") == 0){
        this->mParseQueryString();
    }else if(m_RequestMethod.compare("POST") == 0){
        std::cin >> m_QueryString;
        this->mParseQueryString();
    } 
}

HTTPRequest::~HTTPRequest()
{
    
    
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
    //TODO implement functionality
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
    key   = this->mDecodeHtml(key);
    value = this->mDecodeHtml(value);

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

