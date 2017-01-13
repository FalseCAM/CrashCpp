// Copyright 2017 falsecam

#include <crashcpp/crashcpp-version.h>
#include <crashcpp/logreport.h>

#include <Poco/Logger.h>

crashcpp::LogReport::LogReport()
{

}

void crashcpp::LogReport::report(std::string title, std::string body, std::string report)
{
    Poco::Logger &logger = Poco::Logger::get("[crash]");
    std::string message = title + "\n" + body + "\n" + report;
    logger.fatal(message);
}
