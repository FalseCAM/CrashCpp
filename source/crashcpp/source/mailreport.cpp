// Copyright 2017 falsecam

#include <crashcpp/crashcpp-version.h>
#include <crashcpp/mailreport.h>

#include <iostream>

#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/SMTPClientSession.h>

crashcpp::MailReport::MailReport() {}

crashcpp::MailReport::MailReport(std::string host, std::string user,
                                 std::string password, std::string recipient) {
  this->host = host;
  this->user = user;
  this->password = password;
}

void crashcpp::MailReport::report(std::string title, std::string body,
                                  std::string report) {
  std::string subject = Poco::Net::MailMessage::encodeWord(title, "UTF-8");
  std::string content = body + "\n" + report;
  Poco::Net::MailMessage message;
  message.setSender(this->user);
  message.addRecipient(Poco::Net::MailRecipient(
      Poco::Net::MailRecipient::PRIMARY_RECIPIENT, this->recipient));
  message.setSubject(subject);
  message.setContentType("text/plain; charset=UTF-8");
  message.setContent(content, Poco::Net::MailMessage::ENCODING_8BIT);
  try {
    Poco::Net::SMTPClientSession session(host, port);
    session.open();
    try {
      session.login(Poco::Net::SMTPClientSession::AUTH_NONE, user, password);
      session.sendMessage(message);
      std::cout << "Message successfully sent" << std::endl;
      session.close();
    } catch (Poco::Net::SMTPException &e) {
      std::cerr << e.displayText() << std::endl;
      session.close();
      return;
    }
  } catch (Poco::Net::NetException &e) {
    std::cerr << e.displayText() << std::endl;
    return;
  }
}
