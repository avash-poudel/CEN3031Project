#include "User.h"





User::User(string& username, string& password)
{
    this->username = username;
    this->password = password;

}

string User::getUsername() const
{
    return username;
}

string User::getPassword() const
{
    return password;
}

int User::getAge() const
{
    return age;
}

void User::setAge(int newAge)
{
    age = newAge;
}

void User::displayUserInfo() const
{
    cout << username << " " << password << " " << age << endl;
}
