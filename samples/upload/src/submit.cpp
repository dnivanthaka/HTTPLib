// Compile as g++ submit.cpp -L ../../lib -lhttplib -o submit.cgi
#include <iostream>
#include <string>

#include "../../include/HTTPLib.h"

using namespace HttpLib;

int main(void)
{
    HTTPRequest req;
    HTTPResponse res;

    //res.setContentType(HTTPResponse::TYPE_HTML);

    //res.write("<pre>");
    res.write(req.getContentType()+"\n");
    res.write(req.getContentLength()+"\n");
    res.write(req.getHttpAccept()+"\n");
    //res.write("</pre>");
    res.write("<h3>Request Method " + req.getRequestMethod() + "</h3>");
    res.write("<h3>Hello ");
    res.write(req.getParameter("name"));
    res.write("!</h3>");
    res.write("<pre>");
    res.write(req.getQueryStringRaw());
    res.write("</pre>");

    return 0;
}
