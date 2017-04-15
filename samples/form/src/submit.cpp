#include <iostream>
#include <string>

#include "../../include/HTTPLib.h"

int main(void)
{
    HttpLib::HTTPRequest req;
    HttpLib::HTTPResponse res;

    res.setContentType("text/html");

    res.write("<h3>Request Method " + req.getRequestMethod() + "</h3>");
    res.write("<h3>Hello ");
    res.write(req.getParameter("name"));
    res.write("!</h3>");

    return 0;
}
