// User.h
#ifndef USER_H
#define USER_H
#pragma once

#include <iostream>
#include <fstream>
#include <string>


using namespace std;
// User class to represent user information
class User {
private:
    string username;
    string password;
    int age;

public:
    User(string& username,  string& password);

    // Getters
    string getUsername() const;
    string getPassword() const;
    int getAge() const;

    // Setter for age
    void setAge(int newAge);

    // Display user information
    void displayUserInfo() const;
};



#endif // USER_H
