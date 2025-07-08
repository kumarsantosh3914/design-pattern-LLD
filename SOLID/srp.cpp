/**
 * Single Responsibility Principle (SRP):
 * A class should have only one reason to change, meaning it should have only one job or responsibility.
 */

#include <iostream>

// this class voilates the Single Responsibility Principle (SRP)
// because it has multiple responsibilities: user authentication, profile management, and email notifications.
class Manager {
public:
    void uthenticateUser(const std::string& username, const std::string& password) {
        // Logic to authenticate user
        std::cout << "Authenticating user: " << username << std::endl;
    }

    void updateUserProfile(const std::string& username, const std::string& newProfileData) {
        // Logic to update user profile
        std::cout << "Updating profile for user: " << username << std::endl;
    }

    void sendEmailNotification(const std::string& email, const std::string& message) {
        // Logic to send email notification
        std::cout << "Sending email to: " << email << " with message: " << message << std::endl;
    }
};


// To adhere the SRP, we can split this class into three separate classes,
// each with a single responsibility.

class UserAuthenticator {
public:
    void authenticateUser(const std::string& username, const std::string& password) {
        // Logic to authenticate user
        std::cout << "Authenticating user: " << username << std::endl;
    }
};

class UserProfileManager {
public:
    void updateUserProfile(const std::string& username, const std::string& newProfileData) {
        // Logic to update user profile
        std::cout << "Updating profile for user: " << username << std::endl;
    }
};


class EmailNotifier {
public:
    void sendEmailNotification(const std::string& email, const std::string& message) {
        // Logic to send email notification
        std::cout << "Sending email to: " << email << " with message: " << message << std::endl;
    }
};