#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User {
private:
    int age;
    std::string user_id;
    std::string password;
    std::string country;
    std::string gender;

public:
    // Constructor
    User(int age, const std::string& user_id, const std::string& password, const std::string& country, const std::string& gender);

    // Getter methods
    int getAge() const;
    std::string getUserId() const;
    std::string getPassword() const;
    std::string getCountry() const;
    std::string getGender() const;

    // Setter methods
    void setAge(int new_age);
    void setPassword(const std::string& new_password);
    void setCountry(const std::string& new_country);

    // Display user info
    void displayUserInfo() const;
};

#endif // USER_H
