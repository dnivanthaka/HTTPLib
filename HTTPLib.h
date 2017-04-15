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
            void header(std::string url);
            void redirect(std::string url);
            void flush();
            static const std::string TYPE_HTML;
            static const std::string TYPE_TEXT;
            static const std::string TYPE_CSS;
            static const std::string TYPE_JAVASCRIPT;
            static const std::string TYPE_JSON;
            static const std::string TYPE_ZIP;
            static const std::string TYPE_PDF;
            static const std::string TYPE_XML;
            static const std::string TYPE_MPEG;
            static const std::string TYPE_VORBIS;
            static const std::string TYPE_PNG;
            static const std::string TYPE_JPEG;
            static const std::string TYPE_GIF;
        private:
            std::string contentType;
            std::vector<std::string> response;
            bool m_HeaderSent;
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
            void mParseMultipartData(std::string boundary);
            std::vector<std::string> mGetValuePair(std::string str);
            std::string mDecodeHtml(std::string str);
            std::map<std::string, std::string> pairs;
            char *m_pMultipartData;
            
        };
};

#endif
