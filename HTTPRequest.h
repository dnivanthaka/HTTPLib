#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
class HTTPRequest{
public:
    HTTPRequest();
    ~HTTPRequest();
    std::string getRequestMethod();
    std::string getPathInfo();
    std::string getPathTranslated();
    std::string getScriptName();
    std::string getQueryStringRaw();
    std::string getRemoteHost();
    std::string getContentType();
    std::string getContentLength();
    std::string getHTTPUserAgent();
    std::string getHttpAccept();
    
    std::string getGetVar(std::string);
    std::string getPostVar(std::string);
    
private:
    std::string m_RequestMethod, m_PathInfo, m_PathTranslated, m_ScriptName, 
    m_QueryString, m_RemoteHost, m_ContentType, m_ContentLength, m_HttpUserAgent, m_HttpAccept;
    
    void mParseQueryString();
    std::vector<std::string> mDecodeValuePair(std::string str);
    std::map<std::string, std::string> pairs;
    
};
#endif
