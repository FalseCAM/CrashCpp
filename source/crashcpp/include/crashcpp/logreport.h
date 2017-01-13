// Copyright 2017 falsecam

#ifndef CRASHCPP_LOGREPORT_H
#define CRASHCPP_LOGREPORT_H

#include <crashcpp/crashcpp_api.h>
#include <crashcpp/report.h>
#include <string>

namespace crashcpp {

class CRASHCPP_API LogReport : public Report {

public:
  LogReport();

  virtual void report(std::string title, std::string body, std::string report);

protected:
};
} // crashcpp
#endif
