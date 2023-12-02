#include "User.h"

// Constructor
User::User(int age, const std::string& user_id, const std::string& password, const std::string& country, const std::string& gender)
    : age(age), user_id(user_id), password(password), country(country), gender(gender) {}

// Getter methods
int User::getAge() const {
    return age;
}

std::string User::getUserId() const {
    return user_id;
}

std::string User::getPassword() const {
    return password;
}

std::string User::getCountry() const {
    return country;
}

std::string User::getGender() const {
    return gender;
}

// Setter methods
void User::setAge(int new_age) {
    age = new_age;
}


void User::setPassword(const std::string& new_password) {
    password = new_password;
}

void User::setCountry(const std::string& new_country) {
    country = new_country;
}

void User::displayUserInfo() const {
    std::cout << "User ID: " << user_id << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Country: " << country << std::endl;
    std::cout << "Gender: " << gender << std::endl;
}
