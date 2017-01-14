
#include <crashcpp/crashcpp.h>
#include <crashcpp/postreport.h>

#include <memory>

#include <QApplication>

// source:
// http://stackoverflow.com/questions/77005/how-to-generate-a-stacktrace-when-my-gcc-c-app-crashes
void baz() {
  int *foo = (int *)-1; // make a bad pointer
  printf("%d\n", *foo); // causes segfault
}

void bar() { baz(); }
void foo() { bar(); }

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  CrashCpp::init();
  CrashCpp::addReporter(std::make_shared<crashcpp::PostReport>(
      "http://localhost:3000/api/report"));
  foo();
  return application.exec();
}
