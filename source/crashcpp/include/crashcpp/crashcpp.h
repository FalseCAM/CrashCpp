// Copyright 2017 falsecam

#ifndef CRASHCPP_H
#define CRASHCPP_H

#include <crashcpp/crashcpp_api.h>
#include <crashcpp/report.h>

#include <memory>
#include <vector>

class CRASHCPP_API CrashCpp {

public:
  static void init();
  static void handler(int sig);
  static std::string Backtrace(int skip = 1);

  /**
   * @brief addReporter
   * Adds the reporter to a list of reporters who will send crash report when
   * crash happens.
   * @param reporter
   */
  static void addReporter(std::shared_ptr<crashcpp::Report> reporter);

  static void sendReport(std::string title, std::string body,
                         std::string report);
};

#endif
