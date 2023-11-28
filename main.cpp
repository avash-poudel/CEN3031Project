#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class AdviceProvider {
public:
    string getAdvice(const string& diagnosis) {
        if (diagnosis == "TEENAGER STRESS") {
            return "Teenagers often face stress due to academic pressure, social challenges, and other factors.\n"
                   "It's important to manage time effectively, prioritize tasks, and engage in relaxation techniques.\n"
                   "Consider talking to a trusted adult or seeking professional help if stress becomes overwhelming.\n";
        } else if (diagnosis == "ADULT STRESS") {
            return "Adults commonly experience stress from work, family, and other responsibilities.\n"
                   "Balancing work and personal life, setting realistic goals, and practicing self-care are essential.\n"
                   "Consider seeking support from friends, family, or a mental health professional to manage stress.\n";
        } else if (diagnosis == "TEENAGER DEPRESSION") {
            return "Teenagers facing depression may benefit from talking to a counselor, therapist, or a trusted adult.\n"
                   "Engaging in activities they enjoy, maintaining a healthy routine, and seeking social support are crucial.\n"
                   "Encourage communication and consider involving a mental health professional for support.\n";
        } else if (diagnosis == "ADULT DEPRESSION") {
            return "Adults dealing with depression should prioritize self-care, including regular exercise and sufficient sleep.\n"
                   "Building a strong support network, seeking professional help, and setting achievable goals are important.\n"
                   "Encourage open communication with loved ones and consider therapy or counseling as part of the treatment plan.\n";
        } else if (diagnosis == "TEENAGER ANXIETY") {
            return "Teenagers with anxiety may benefit from learning and practicing relaxation techniques";
        } else if (diagnosis == "ADULT ANXIETY") {
            return "Adults with anxiety may benefit from learning and practicing new hobbies";
        } else {
            return "No specific advice found for the given diagnosis.";
        }
    }
};


int main() {
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
            } else {
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
    cout << "Age Range: " << age << endl;
    cout << "Activity: " << activity << endl;
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
            } else if (depression >= 7) {
                diagnosis = "TEENAGER DEPRESSION";
            } else if (anxiety >= 7) {
                diagnosis = "TEENAGER ANXIETY";
            }
        } else {
            if (stress >= 7) {
                diagnosis = "ADULT STRESS";
            } else if (depression >= 7) {
                diagnosis = "ADULT DEPRESSION";
            } else if (anxiety >= 7) {
                diagnosis = "ADULT ANXIETY";
            }
            } 

        cout << "Diagnosis: " << diagnosis << endl;
        AdviceProvider adviceProvider;
        string advice = adviceProvider.getAdvice(diagnosis);
        cout << advice << endl;
    } else {
        // If NO, gather input again
        main(); 
    }

    return 0;
}
