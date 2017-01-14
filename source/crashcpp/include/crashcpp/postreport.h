// Copyright 2017 falsecam

#ifndef CRASHCPP_POSTREPORT_H
#define CRASHCPP_POSTREPORT_H

#include <crashcpp/crashcpp_api.h>
#include <crashcpp/report.h>
#include <string>

namespace crashcpp {

class CRASHCPP_API PostReport : public Report {

public:
  PostReport() = delete;

  PostReport(std::string host);

  virtual void report(std::string title, std::string body, std::string report);

protected:
  std::string host;
};
} // crashcpp
#endif
