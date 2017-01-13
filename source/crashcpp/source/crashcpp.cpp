// Copyright 2017 falsecam

#include <crashcpp/crashcpp-version.h>
#include <crashcpp/crashcpp.h>

#ifdef __linux__
#include <cxxabi.h> // for __cxa_demangle
#include <dlfcn.h>  // for dladdr
#include <execinfo.h>
#include <execinfo.h> // for backtrace
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>
#elif _WIN32
#else
#endif

static std::vector<std::shared_ptr<crashcpp::Report>> reporters;

void CrashCpp::handler(int sig) {
#ifdef __linux__
  std::string report = Backtrace();
  sendReport("title", "body", report);
  exit(1);
#elif _WIN32
#else
#endif
}

std::string CrashCpp::Backtrace(int skip) {
  // source: https://gist.github.com/fmela/591333
  void *callstack[128];
  const int nMaxFrames = sizeof(callstack) / sizeof(callstack[0]);
  char buf[1024];
  int nFrames = backtrace(callstack, nMaxFrames);
  char **symbols = backtrace_symbols(callstack, nFrames);

  std::ostringstream trace_buf;
  for (int i = skip; i < nFrames; i++) {
    printf("%s\n", symbols[i]);

    Dl_info info;
    if (dladdr(callstack[i], &info) && info.dli_sname) {
      char *demangled = NULL;
      int status = -1;
      if (info.dli_sname[0] == '_')
        demangled = abi::__cxa_demangle(info.dli_sname, NULL, 0, &status);
      snprintf(buf, sizeof(buf), "%-3d %*p %s + %zd\n", i,
               int(2 + sizeof(void *) * 2), callstack[i],
               status == 0 ? demangled : info.dli_sname == 0 ? symbols[i]
                                                             : info.dli_sname,
               (char *)callstack[i] - (char *)info.dli_saddr);
      free(demangled);
    } else {
      snprintf(buf, sizeof(buf), "%-3d %*p %s\n", i,
               int(2 + sizeof(void *) * 2), callstack[i], symbols[i]);
    }
    trace_buf << buf;
  }
  free(symbols);
  if (nFrames == nMaxFrames)
    trace_buf << "[truncated]\n";
  return trace_buf.str();
}

void CrashCpp::addReporter(std::shared_ptr<crashcpp::Report> reporter) {
  reporters.push_back(reporter);
}

void CrashCpp::sendReport(std::string title, std::string body,
                          std::string report) {
  for (std::shared_ptr<crashcpp::Report> reporter : reporters) {
    reporter->report(title, body, report);
  }
}

void CrashCpp::init() {
#ifdef __linux__
  signal(SIGSEGV, handler);
#elif _WIN32
#else
#endif
}
