// Copyright 2017 falsecam

#ifndef CRASHCPP_MAILREPORT_H
#define CRASHCPP_MAILREPORT_H

#include <crashcpp/crashcpp_api.h>
#include <crashcpp/report.h>
#include <string>

namespace crashcpp {

class CRASHCPP_API MailReport : public Report {

public:
  MailReport();

  MailReport(std::string host, std::string user, std::string password,
             std::string recipient);

  virtual void report(std::string title, std::string body, std::string report);

protected:
  std::string host;
  int port = 25;
  std::string user;
  std::string password;
  std::string recipient;
};
} // crashcpp
#endif
