// Copyright 2017 falsecam

#ifndef CRASHCPP_REPORT_H
#define CRASHCPP_REPORT_H

#include <crashcpp/crashcpp_api.h>
#include <string>

namespace crashcpp {

/**
 * @brief The Report class
 * Interface for Reports
 */
class CRASHCPP_API Report {

public:
  Report() = default;
  virtual ~Report() = default;
  /**
   * @brief report
   * function that is executed when crash occures
   * @param title
   * @param body
   * @param report
   */
  virtual void report(std::string title, std::string body,
                      std::string report) = 0;
};
} // crashcpp
#endif
