// Copyright 2017 falsecam

#include <crashcpp/crashcpp-version.h>
#include <crashcpp/postreport.h>

#include <iostream>

#include <Poco/URI.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/SSLException.h>

void crashcpp::PostReport::report(std::string title, std::string body,
                                  std::string report) {
  try {
    Poco::URI uri(host);
    uri.addQueryParameter("title", title);
    uri.addQueryParameter("body", body);
    uri.addQueryParameter("report", report);

    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
    Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, uri.toString());
    req.setContentType("application/x-www-form-urlencoded\r\n");
    //req.setKeepAlive(true);

    //req.setContentLength(report.length());

    session.sendRequest(req);
    Poco::Net::HTTPResponse res;
    std::istream &rs = session.receiveResponse(res);
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}

crashcpp::PostReport::PostReport(std::string host) { this->host = host; }
