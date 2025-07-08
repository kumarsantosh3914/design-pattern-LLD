/**
 * Dependency Inversion Principle (DIP):
 * High-level modules should not depend on low-level modules;
 * both should depend on abstractions.
 */

/**
 * Code Example:
 * Let's consider a example where we have a EmailService class that sends emails
 * using a specific email provider (e.g., Gmail)
 */

#include<iostream>

class GmailClient {
public:
    void sendEmail(const string& recipient, const string& subject, const string& body) {
        cout << "Sending email via Gmail:" << endl;
    }
};

class EamilService {
private:
    GmailClient gmialClient;
public:
    void sendEmail(const string& recipient, const string& subject, const string& body) {
        gmialClient.sendEmail(recipient, subject, body);
    }
};

/**
 * In this example EmailService class clearly depends on the GmailClient class,
 * a low-level module that implements the details of sending emails using the Gmail API.
 * this violates DIP.
 */

// To adhere to the DIP, we can introduce an abstraction (interface) for email clients:
class EmailClient {
public:
    virtual  sendEmail(const string& recipient, const string& subject, const string& body) = 0;
    virtual ~EmailClient() {}
};

// GmailClient implementation
class GmailClient : public EmailClient {
public:
    void sendEmail(const string& recipient, const string& subject, const string& body) override {
        cout << "Sending email via Gmail:" << endl;
    }
};

// OutlookClient implementation
class OutlookClient : public EmailClient {
public:
    void sendEmail(const string& recipient, const string& subject, const string& body) override {
        cout << "Sending email via Outlook:" << endl;
    }
};