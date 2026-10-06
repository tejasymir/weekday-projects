#include <iostream>
#include <string>
#include <cctype>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    string password;

    cout << "=============================\n";
    cout << "     PASSWORD ANALYZER\n";
    cout << "=============================\n\n";

    cout << "Enter password: ";
    getline(cin, password);

    if (password.empty()) {
        cout << "\nPassword cannot be empty.\n";
        return 0;
    }

    int score = 0;

    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    for (char c : password) {
        if (isupper(static_cast<unsigned char>(c)))
            hasUpper = true;
        else if (islower(static_cast<unsigned char>(c)))
            hasLower = true;
        else if (isdigit(static_cast<unsigned char>(c)))
            hasDigit = true;
        else
            hasSpecial = true;
    }

    int length = password.length();

    if (length >= 16)
        score += 35;
    else if (length >= 12)
        score += 30;
    else if (length >= 8)
        score += 20;
    else if (length >= 6)
        score += 10;

    if (hasUpper)
        score += 10;

    if (hasLower)
        score += 10;

    if (hasDigit)
        score += 10;

    if (hasSpecial)
        score += 15;

    set<char> uniqueChars(password.begin(), password.end());

    int repeated = length - uniqueChars.size();

    if (repeated == 0)
        score += 10;
    else if (repeated <= 2)
        score += 5;

    string lowerPassword = password;

    transform(lowerPassword.begin(), lowerPassword.end(),
              lowerPassword.begin(),
              [](unsigned char c) {
                  return tolower(c);
              });

    bool commonPattern = false;

    string commonWords[] = {
        "password",
        "qwerty",
        "admin",
        "welcome",
        "letmein",
        "iloveyou",
        "abc123",
        "123456"
    };

    for (string word : commonWords) {
        if (lowerPassword.find(word) != string::npos) {
            commonPattern = true;
            break;
        }
    }

    if (commonPattern)
        score -= 25;

    bool sequential = false;

    for (int i = 0; i + 2 < length; i++) {
        if (password[i + 1] == password[i] + 1 &&
            password[i + 2] == password[i] + 2) {
            sequential = true;
            break;
        }

        if (password[i + 1] == password[i] - 1 &&
            password[i + 2] == password[i] - 2) {
            sequential = true;
            break;
        }
    }

    if (sequential)
        score -= 10;

    score = max(0, min(100, score));

    string strength;

    if (score < 30)
        strength = "VERY WEAK";
    else if (score < 50)
        strength = "WEAK";
    else if (score < 70)
        strength = "MEDIUM";
    else if (score < 85)
        strength = "STRONG";
    else
        strength = "VERY STRONG";

    cout << "\n=============================\n";
    cout << "       ANALYSIS\n";
    cout << "=============================\n\n";

    cout << "Length:             " << length << '\n';
    cout << "Uppercase:          " << (hasUpper ? "YES" : "NO") << '\n';
    cout << "Lowercase:          " << (hasLower ? "YES" : "NO") << '\n';
    cout << "Numbers:            " << (hasDigit ? "YES" : "NO") << '\n';
    cout << "Special characters: " << (hasSpecial ? "YES" : "NO") << '\n';
    cout << "Repeated characters: " << repeated << '\n';
    cout << "Common pattern:     " << (commonPattern ? "YES" : "NO") << '\n';
    cout << "Sequential pattern: " << (sequential ? "YES" : "NO") << '\n';

    cout << "\n-----------------------------\n";
    cout << "Score:              " << score << "/100\n";
    cout << "Strength:           " << strength << '\n';
    cout << "-----------------------------\n";

    if (score < 50) {
        cout << "\nSuggestions:\n";
        cout << "- Use a longer password\n";
        cout << "- Add uppercase letters\n";
        cout << "- Add numbers\n";
        cout << "- Add special characters\n";
        cout << "- Avoid common words and patterns\n";
    }

    return 0;
}