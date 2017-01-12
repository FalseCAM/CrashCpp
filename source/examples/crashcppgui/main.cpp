
#include <crashcpp/crashcpp.h>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    crashcpp::CrashCpp crashCpp;
    return application.exec();
}
