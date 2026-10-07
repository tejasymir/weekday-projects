#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>

using namespace std;

void shutdownPC(int seconds) {
    string command = "shutdown /s /t " + to_string(seconds);
    system(command.c_str());
}

void restartPC(int seconds) {
    string command = "shutdown /r /t " + to_string(seconds);
    system(command.c_str());
}

void cancelShutdown() {
    system("shutdown /a");
}

void lockPC() {
    LockWorkStation();
}

void sleepPC() {
    system("rundll32.exe powrprof.dll,SetSuspendState 0,1,0");
}

void launchProgram(const string& program) {
    system(("start " + program).c_str());
}

void showUptime() {
    ULONGLONG milliseconds = GetTickCount64();

    ULONGLONG seconds = milliseconds / 1000;
    ULONGLONG minutes = seconds / 60;
    ULONGLONG hours = minutes / 60;
    ULONGLONG days = hours / 24;

    hours %= 24;
    minutes %= 60;
    seconds %= 60;

    cout << "\nSystem uptime: "
         << days << " days, "
         << hours << " hours, "
         << minutes << " minutes, "
         << seconds << " seconds\n";
}

void showMenu() {
    cout << "\n";
    cout << "================================\n";
    cout << "       WINDOWS CONTROLLER       \n";
    cout << "================================\n";
    cout << "1. Shutdown in X seconds\n";
    cout << "2. Restart in X seconds\n";
    cout << "3. Cancel scheduled shutdown\n";
    cout << "4. Lock PC\n";
    cout << "5. Sleep PC\n";
    cout << "6. Launch application\n";
    cout << "7. Show system uptime\n";
    cout << "8. Exit\n";
    cout << "================================\n";
    cout << "Choose: ";
}

int main() {
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            int seconds;
            cout << "Shutdown after how many seconds? ";
            cin >> seconds;

            shutdownPC(seconds);
            cout << "Shutdown scheduled.\n";
        }

        else if (choice == 2) {
            int seconds;
            cout << "Restart after how many seconds? ";
            cin >> seconds;

            restartPC(seconds);
            cout << "Restart scheduled.\n";
        }

        else if (choice == 3) {
            cancelShutdown();
            cout << "Scheduled shutdown cancelled.\n";
        }

        else if (choice == 4) {
            lockPC();
        }

        else if (choice == 5) {
            sleepPC();
        }

        else if (choice == 6) {
            string program;
            cout << "Enter application (e.g. chrome): ";
            cin >> program;

            launchProgram(program);
        }

        else if (choice == 7) {
            showUptime();
        }

        else if (choice == 8) {
            cout << "Exiting...\n";
            break;
        }

        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}