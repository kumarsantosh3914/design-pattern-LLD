/**
 * Creating the DBConnection class
 * - We are going to create a DBConnection class that ensures only one
 *   instance of the class is created. This will manage our database
 *   connection.
 * 
 * - Without the Singleton pattern, multiple instances of DBConnection could
 *   be created, leading to multiple database connections. This can cause
 *   resource contention, inconsistent states, and excessive use of resources.
 * 
 * - The Singleton pattern ensures that only one instance of DBConnection
 *   exists. This instance is shared across the entire application, providing a
 *   single point of access to the database connection. and ensuring resource
 *   efficiency and consistency.
 */

 #include<iostream>
 #include<memory>

 class DBConnection {
 private:
    // Private constructor
    DBConnection() {
        std::cout << "DBConnection created." << std::endl;
    }

    // Disable copy constructor and assignment operator
    DBConnection(const DBConnection&) = delete;
    DBConnection& operator=(const DBConnection&) = delete;

    // Disable move constructor and move assignment operator
    DBConnection(DBConnection&&) = delete;
    DBConnection& operator=(DBConnection&&) = delete;

    // Private static instance
    static std::shared_ptr<DBConnection> instance;

public:
    // Example connect method
    void connect() {
        std::cout << "Connected to database." << std::endl;
    }

    // Public static method to get the instance
    static std::shared_ptr<DBConnection> getInstance() {
        if(!DBConnection::instance) {
            DBConnection::instance = std::shared_ptr<DBConnection>(new DBConnection());
        }

        return DBConnection::instance;
    }
 };

//  Initialize the static instance
std::shared_ptr<DBConnection> DBConnection::instance = nullptr;

int main() {
    // Get the singleton instance and use it to connect to the database
    std::shared_ptr<DBConnection> db1 = DBConnection::getInstance();
    db1->connect();

    // Get the singleton instance again and use it
    std::shared_ptr<DBConnection> db2 = DBConnection::getInstance();
    db2->connect();

    return 0;
}