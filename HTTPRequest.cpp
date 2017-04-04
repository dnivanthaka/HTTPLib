#include <iostream>
#include <cstdlib>
#include <cstring>

#include "HTTPRequest.h"

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
    
}

HTTPRequest::~HTTPRequest()
{
    
    
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

int main(void)
{
    HTTPRequest *http = new HTTPRequest();
    
    return 0;
}