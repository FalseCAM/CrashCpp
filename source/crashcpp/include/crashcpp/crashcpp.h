// Copyright 2017 falsecam

#ifndef CRASHCPP_H
#define CRASHCPP_H

#include <crashcpp/crashcpp_api.h>

class CRASHCPP_API CrashCpp {

public:
  static void init();
  static void handler(int sig);
};

#endif
