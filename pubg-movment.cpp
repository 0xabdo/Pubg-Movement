#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

void printHeader() {
    cout << "============================================\n";
    cout << "           github.com/0xabdo                 \n";
    cout << "             Pubg Movement                   \n";
    cout << "                 v1.0                      \n";
    cout << "============================================\n\n";
}

int main() {
    printHeader();

    cout << "[INFO] Starting process..." << endl;
    cout << "[INFO] Please wait...\n" << endl;
    this_thread::sleep_for(chrono::seconds(3)); // 3 sec delay

    // Get APPDATA safely
    char* appData = nullptr;
    size_t len = 0;
    if (_dupenv_s(&appData, &len, "APPDATA") || appData == nullptr) {
        cout << "[ERROR] Failed to get APPDATA path." << endl;
        cout << "[EXIT] Press Enter to exit...";
        cin.get();
        return 1;
    }

    // Build file path
    string filePath = string(appData) + "\\AndroidTbox\\TVM_100.xml";
    free(appData);

    // Open file
    ifstream inFile(filePath);
    if (!inFile) {
        cout << "[ERROR] Failed to open file: " << filePath << endl;
        cout << "[EXIT] Press Enter to exit...";
        cin.get();
        return 1;
    }

    // Read content
    stringstream buffer;
    buffer << inFile.rdbuf();
    string content = buffer.str();
    inFile.close();

    cout << "[INFO] Processing XML..." << endl;
    this_thread::sleep_for(chrono::seconds(3)); // 3 sec delay

    // Strings
    string target = "Type=\"CrossKey\" speed=\"0\"";
    string replacement = "Type=\"CrossKey\" speed=\"100\"";
    string alreadyDone = "Type=\"CrossKey\" speed=\"100\"";

    // Check if already modified
    if (content.find(alreadyDone) != string::npos) {
        cout << "[SUCCESS] Speed is already set to 100. No changes needed." << endl;
        cout << "\n[EXIT] Press Enter to exit...";
        cin.get();
        return 0;
    }

    size_t pos = 0;
    int count = 0;

    while ((pos = content.find(target, pos)) != string::npos) {
        content.replace(pos, target.length(), replacement);
        pos += replacement.length();
        count++;
    }

    if (count == 0) {
        cout << "[WARNING] Target not found. No changes applied." << endl;
        cout << "\n[EXIT] Press Enter to exit...";
        cin.get();
        return 0;
    }

    // Write back
    ofstream outFile(filePath);
    if (!outFile) {
        cout << "[ERROR] Failed to write file." << endl;
        cout << "[EXIT] Press Enter to exit...";
        cin.get();
        return 1;
    }

    outFile << content;
    outFile.close();

    cout << "[SUCCESS] XML updated successfully! " << count << " entry(ies) modified." << endl;
    cout << "[INFO] Please restart Gameloop to see results." << endl;
    cout << "\n[EXIT] Press Enter to exit...";
    cin.get();

    return 0;
}
