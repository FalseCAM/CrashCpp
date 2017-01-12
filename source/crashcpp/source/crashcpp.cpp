// Copyright 2017 falsecam

#include <crashcpp/crashcpp-version.h>
#include <crashcpp/crashcpp.h>

#ifdef __linux__
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#elif _WIN32
#else
#endif

void CrashCpp::handler(int sig)
{
#ifdef __linux__
    // source: http://stackoverflow.com/questions/77005/how-to-generate-a-stacktrace-when-my-gcc-c-app-crashes
    void *array[10];
      size_t size;

      // get void*'s for all entries on the stack
      size = backtrace(array, 10);

      // print out all the frames to stderr
      fprintf(stderr, "Error: signal %d:\n", sig);
      backtrace_symbols_fd(array, size, STDERR_FILENO);
      exit(1);
#elif _WIN32
#else
#endif
}

void CrashCpp::init()
{
#ifdef __linux__
    signal(SIGSEGV, handler);
#elif _WIN32
#else
#endif
}
