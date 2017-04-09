#ifndef HTTPLIB_H
#define HTTPLIB_H

#include <string>
#include <vector>
#include <map>

namespace HttpLib{
    class HTTPResponse{
        public:
            HTTPResponse();
            ~HTTPResponse();
            void setContentType(std::string str);
            void write(std::string str);
        private:
            std::string contentType;
            std::vector<std::string> response;
            void m_SendOutput();
    };
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
            
            std::string getParameter(std::string key);
            
        private:
            std::string m_RequestMethod, m_PathInfo, m_PathTranslated, m_ScriptName, 
            m_QueryString, m_RemoteHost, m_ContentType, m_ContentLength, m_HttpUserAgent, m_HttpAccept;
            
            void mParseQueryString();
            std::vector<std::string> mGetValuePair(std::string str);
            std::string mDecodeHtml(std::string str);
            std::map<std::string, std::string> pairs;
            
        };
};

#endif
