
#include <crashcpp/crashcpp.h>
#include <crashcpp/logreport.h>

#include <Poco/AutoPtr.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/FileChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/Logger.h>
#include <Poco/PatternFormatter.h>
#include <Poco/SplitterChannel.h>

#include <memory>

using Poco::FileChannel;
using Poco::SplitterChannel;
using Poco::ConsoleChannel;
using Poco::AutoPtr;
using Poco::FormattingChannel;
using Poco::PatternFormatter;

// source:
// http://stackoverflow.com/questions/77005/how-to-generate-a-stacktrace-when-my-gcc-c-app-crashes
void baz() {
  int *foo = (int *)-1; // make a bad pointer
  printf("%d\n", *foo); // causes segfault
}

void bar() { baz(); }
void foo() { bar(); }

int main(int argc, char *argv[]) {
  AutoPtr<ConsoleChannel> pCons(new ConsoleChannel);
  AutoPtr<FileChannel> pFile(new FileChannel);
  pFile->setProperty("path", "crashcpp.log");
  pFile->setProperty("rotation", "1 M");
  pFile->setProperty("archive", "timestamp");
  pFile->setProperty("purgeCount", "10");
  AutoPtr<SplitterChannel> pSplitter(new SplitterChannel);
  pSplitter->addChannel(pCons);
  pSplitter->addChannel(pFile);
  AutoPtr<PatternFormatter> pPF(new PatternFormatter);
  pPF->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s: %t");
  AutoPtr<FormattingChannel> pFC(new FormattingChannel(pPF, pSplitter));
  Poco::Logger::root().setChannel(pFC);

  CrashCpp::init();
  CrashCpp::addReporter(std::make_shared<crashcpp::LogReport>());
  foo();
  return 1;
}
