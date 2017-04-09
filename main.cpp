#include <iostream>
#include <string>

#include "HTTPLib.h"

int main(void)
{
    std::string val;

    //std::cout << "Content-Type: text/plain\n\n";
    HttpLib::HTTPResponse *res = new HttpLib::HTTPResponse();

    HttpLib::HTTPRequest *http = new HttpLib::HTTPRequest();
    
    //std::cout << http->getRequestMethod() << std::endl;
    //std::cout << http->getParameter("test") << std::endl;
    res->write(http->getRequestMethod());
    res->write(http->getParameter("test"));
    /*if(http->getRequestMethod().compare("POST") == 0){
        std::cin >> val;
        std::cout << val;
    }*/

    delete res;
    delete http;
    
    return 0;
}
