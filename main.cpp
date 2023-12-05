#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include<cstdlib>


#include "Countries.h"
#include "User.h"


using namespace std;



string encrypt(const string& data)
{

    string encrypted = data;
    for (char& c : encrypted)
    {
        c += 5;
    }
    return encrypted;
}

int encrypt(const int& data)
{

    int encrypted = data;
    encrypted = (encrypted + 7) % 10;
    return encrypted;
}

string decrypt(const string& data) {

    string decrypted = data;
    for (char& c : decrypted)
    {
        c -= 5;

    }
    return decrypted;

}

int decrypt(const int& data)
{

    int encrypted = data;
    encrypted = (encrypted + 3) % 10;
    return encrypted;
}

// Function to check if a user exists in the database
bool userAuthentication(const string& username, const string& password) {
    ifstream file("UserDatabase.txt");
    string line;

    string decryptedName = encrypt(username);
    string decrypedPass = encrypt(password);

    while (getline(file, line)) {
        if (line.find(decryptedName) != string::npos && line.find(decrypedPass) != string::npos) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Function to create a new user in the database
void createUser(const User& newUser ) {
    ofstream file("UserDatabase.txt", ios::app);

   


    if (file.is_open()) {
        file << encrypt(newUser.getUsername()) << " " << encrypt(newUser.getPassword()) << "\n";
        file.close();
    }
    else {
        cout << "Error opening the database file." << endl;
    }
}

// Function to update user information in the database
void updateUser(const User& updatedUser) {
    // Read all existing users from the file
    ifstream infile("UserDatabase.txt");
    ofstream outfile("temp.txt");

    string line;
    while (getline(infile, line)) {
        // Check if the line contains the username of the user to be updated
        if (line.find(updatedUser.getUsername()) != string::npos) {
            // Replace the line with the updated user information
            outfile << updatedUser.getUsername() << " " << updatedUser.getPassword() << " " << updatedUser.getAge() << "\n";
        }
        else {
            // Keep other lines unchanged
            outfile << line << "\n";
        }
    }

    infile.close();
    outfile.close();

    // Rename the temporary file to the original file
    remove("UserDatabase.txt");
    rename("temp.txt", "UserDatabase.txt");
}



class AdviceProvider {
public:
    string getAdvice(const string& diagnosis) {
        if (diagnosis == "TEENAGER STRESS") {
            return "Teenagers often face stress due to academic pressure, social challenges, and other factors.\n"
                "It's important to manage time effectively, prioritize tasks, and engage in relaxation techniques.\n"
                "Consider talking to a trusted adult or seeking professional help if stress becomes overwhelming.\n";
        }
        else if (diagnosis == "ADULT STRESS") {
            return "Adults commonly experience stress from work, family, and other responsibilities.\n"
                "Balancing work and personal life, setting realistic goals, and practicing self-care are essential.\n"
                "Consider seeking support from friends, family, or a mental health professional to manage stress.\n";
        }
        else if (diagnosis == "TEENAGER DEPRESSION") {
            return "Teenagers facing depression may benefit from talking to a counselor, therapist, or a trusted adult.\n"
                "Engaging in activities they enjoy, maintaining a healthy routine, and seeking social support are crucial.\n"
                "Encourage communication and consider involving a mental health professional for support.\n";
        }
        else if (diagnosis == "ADULT DEPRESSION") {
            return "Adults dealing with depression should prioritize self-care, including regular exercise and sufficient sleep.\n"
                "Building a strong support network, seeking professional help, and setting achievable goals are important.\n"
                "Encourage open communication with loved ones and consider therapy or counseling as part of the treatment plan.\n";
        }
        else if (diagnosis == "TEENAGER ANXIETY") {
            return "Teenagers with anxiety may benefit from learning and practicing relaxation techniques";
        }
        else if (diagnosis == "ADULT ANXIETY") {
            return "Adults with anxiety may benefit from learning and practicing new hobbies";
        }
        else {
            return "No specific advice found for the given diagnosis.";
        }
    }
};

void DailyMentalupdate()
{
    // Variables to store user inputs
    int gender, age, activity, anxiety, depression, stress;
    string country;

    // Function to gather input and validate against the provided choices
    auto gatherInput = [](const std::string& question, int minChoice, int maxChoice) -> int {
        int choice;
        while (true) {
            cout << question << std::endl;
            cin >> choice;

            if (cin.fail() || choice < minChoice || choice > maxChoice) {
                cin.clear(); // clear input buffer to restore cin to a usable state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore last input
                cout << "Invalid answer. Please enter a valid choice." << endl;
            }
            else {
                break;
            }
        }
        return choice;
    };

    // Function to gather open-ended input
    auto gatherStringInput = [](const string& question) -> string {
        string input;
        cout << question << endl;
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
        getline(cin, input);
        return input;
    };

    // Gather user inputs
    country = gatherStringInput("What country do you live in?");
    gender = gatherInput("What is your gender?\n1) male 2) female 3) other", 1, 3);
    age = gatherInput("In which age range below do you fall?\n1) under 18 2) over 18", 1, 2);
    activity = gatherInput("What of these activities do you practice?\n1) education (school/college)\n2) work/career\n3) education AND work", 1, 3);


    anxiety = gatherInput("On a scale of 1-10, how do you rate your anxiety? (1 being good levels, 10 being the worst)", 1, 10);
    depression = gatherInput("On a scale of 1-10, how do you rate your depression level? (1 being good levels, 10 being the worst)", 1, 10);
    stress = gatherInput("On a scale of 1-10, how do you rate your stress levels? (1 being good levels, 10 being the worst)", 1, 10);

    // Print gathered inputs for confirmation
    cout << "\nPlease confirm your answers:\n";
    cout << "Country: " << country << endl;
    cout << "Gender: " << gender << endl;
    cout << "Age: " << age << endl;
    cout << "Activity: " << activity << endl;
    //Default information within users profile

    cout << "Anxiety Level: " << anxiety << endl;
    cout << "Depression Level: " << depression << endl;
    cout << "Stress Level: " << stress << endl;


    // Gather confirmation
    string confirmation;
    cout << "\nIs this information correct? (YES/NO): ";
    std::cin >> confirmation;

    if (confirmation == "YES" || confirmation == "yes" || confirmation == "Yes") {
        //cout << "Matching..." << endl;
        string diagnosis;
        if (age == 1) {
            if (stress >= 7) {
                diagnosis = "TEENAGER STRESS";
            }
            else if (depression >= 7) {
                diagnosis = "TEENAGER DEPRESSION";
            }
            else if (anxiety >= 7) {
                diagnosis = "TEENAGER ANXIETY";
            }
        }
        else {
            if (stress >= 7) {
                diagnosis = "ADULT STRESS";
            }
            else if (depression >= 7) {
                diagnosis = "ADULT DEPRESSION";
            }
            else if (anxiety >= 7) {
                diagnosis = "ADULT ANXIETY";
            }
        }

        cout << "Diagnosis: " << diagnosis << endl;
        AdviceProvider adviceProvider;
        string advice = adviceProvider.getAdvice(diagnosis);
        cout << advice << endl;
    }

}
int DepressionQuestionaire()
{
    int total = 0;
    int answer;
    cout << "We will now begin the questionaire to diagnose any depressive behavior disorder!\n";
    cout << "Over the last 2 weeks, how often have you been\n bothered by any of the following problems?\n";
    cout << "0 = not at all | 1 = several days | 2 = More than half the days | 3 = Nearly every day\n";
    

    cout << "1. Little interest or pleasure in doing things\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;
    
    cout << "2. Feeling down, depressed, or hopeless\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "3. Trouble falling or staying asleep, or sleeping too much\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "4. Feeling tired or having little energy\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "5. Poor appetite or overeating\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "6. Feeling bad about yourself or that you are a failure or \n have let yourself or your family down\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "7. Trouble concentrating on things, such as reading the newspaper or watching television\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "8. Moving or speaking so slowly that other people could\n have noticed.Or the opposite being so figety or\n restless that you have been moving around a lot more\n than usual\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "9. Thoughts that you would be better off dead, or of hurting yourself\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    return total;


}

int AnxietyQuestionaire()
{
    int total = 0;
    int answer;
    cout << "We will now begin the questionaire to diagnose any depressive behavior disorder!\n";
    cout << "Over the last 2 weeks, how often have you been\n bothered by any of the following problems?\n";
    cout << "0 = not at all | 1 = several days | 2 = More than half the days | 3 = Nearly every day\n";

    cout << "1. Feeling nervous, anxious or on edge?\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "2. Not being able to stop or control worrying?\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "3. Worrying too much about different things?\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "4. Trouble relaxing?\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "5. Being so restless that it is hard to sit still?\n";
    cin >> answer; 
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "6. Becoming easily annoyed or irritable?\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "7. Feeling afraid as if something awful might happen?\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    return total;
}

int StressQuestionaire()
{
    int total = 0;
    int answer;
    cout << "We will now begin the questionaire to diagnose any depressive behavior disorder!\n";
    cout << "Over the last 2 weeks, how often have you been\n bothered by any of the following problems?\n";
    cout << "0 = not at all | 1 = several days | 2 = More than half the days | 3 = Nearly every day\n";


    cout << "1. Do you have trouble staying focused on the present moment?\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "2. How often do you feel overwhelmed with your life? \n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "3. Do you struggle to fall asleep at night?\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "4. On average, do you get less than 7-8 hours of sleep a night?\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "5. Poor appetite or overeating\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "6. Do you experience headaches or muscle tension?\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "7. Trouble concentrating on things, such as reading the newspaper or watching television\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "8. Do you feel like withdrawing from family, friends, and isolating yourself?\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    cout << "9. Do you feel irritable, annoyed, or angry over trivial issues?\n";
    cin >> answer;
    while (answer < 0 || answer > 3 || !isdigit(answer))
    {
        cout << "Please enter an appropriate value: ";
        cin >> answer;
    }
    total += answer;

    return total;
}

void SigninMenu()
{

    int choice;
    string username, password;


    cout << "Welcome to Happy Buddy!" << endl;
 
    // Sign-in or create a new user
    cout << "1. Sign-in\n";
    cout << "2. Create account\n";
    cin >> choice;
    while (choice < 1 || choice > 2 || !isdigit(choice))
    {
        cout << "Please enter valid choice!\n";
        cin >> choice;
    }
    if (choice == 1)
    {
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        while (!userAuthentication(username, password))
        {
            cout << "Username or Password incorrect!\n";
            cout << "Please re-enter Username and Password\n";
            cout << "Type \"back\" to return to sign-in screen\n";
            cout << "Username: ";
            cin >> username;
            if (username == "back")
                SigninMenu();
            cout << "Password: ";
            cin >> password;
        }
        cout << "Welcome back, "; //Users name 
        //Gather users data from file 

    }
    else if (choice == 2)
    {
        cout << "Please enter your username: ";
        cin >> username;

        cout << "Please enter your password: ";
        cin >> password;

        User newUser(username, password);

        createUser(newUser);
        cout << "Account created successfully!\n";
        
        ofstream userFile(username + ".txt");

        userFile << encrypt(username) << endl;
        




    }

 }


    int main() {
        //Initialize Countries List object with csv data
        CountryList HappinessIndex("happiness.csv");



        //Startup Menu
        SigninMenu();



        int age;
        int choice;

        






        // Update user information
        int choice;
        cout << "1. Update age\n2. Exit\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter your new age: ";
            cin >> age;

            // Load user information from the database and update the age
            User updatedUser(username, password, age);
            updateUser(updatedUser);

            cout << "Age updated successfully!\n";
        }
        else {
            cout << "Goodbye!\n";

        }

        return 0;

}
