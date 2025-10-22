#include <iostream>
#include <string>
#include <vector>
#include <cctype>   // toupper
#include <cstdlib>  // exit
#include <limits>   // numeric_limits

class diabetes {
private:
    std::string name;
    float age = 0.0f;
    int wt = 0;
    float ht = 0.0f;
    char sex = 'M';
    std::vector<char> s; // symptom storage (indexed)

public:
    diabetes() : s(20, '\0') {} // reserve enough slots

    void welcome_screen();
    void getvalue();
    void diagnosis();
    void getlevel1_symptoms();
    void getlevel2_symptoms();
    void getlevel3_symptoms();
    int analyse_symptoms(int level);         // returns 0 (not diabetic/primary/etc.) or -1 (diabetic/secondary/etc.)
    char display_message(int level, int result); // returns user's Y/N (uppercase)
};

int main() {
    diabetes dts;
    dts.welcome_screen();
    dts.getvalue();
    dts.diagnosis();

    // Level 1
    dts.getlevel1_symptoms();
    int result = dts.analyse_symptoms(1);
    char choice = dts.display_message(1, result);
    if (choice != 'Y') return 0;

    // Level 2
    dts.getlevel2_symptoms();
    result = dts.analyse_symptoms(2);
    choice = dts.display_message(2, result);
    if (choice != 'Y') return 0;

    // Level 3
    dts.getlevel3_symptoms();
    result = dts.analyse_symptoms(3);
    choice = dts.display_message(3, result);
    // end
    return 0;
}

/* ---------- Implementations ---------- */

void diabetes::welcome_screen() {
    std::cout << "********* W E L C O M E *********\n";
    std::cout << "   CAMPION SCHOOL - MEDICAL DIAGNOSIS SOFTWARE\n";
    std::cout << "              DONE BY: Navi Arora\n\n";
    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void diabetes::getvalue() {
    std::cout << "\n=== PERSONAL INFORMATION ===\n";
    std::cout << "Name: ";
    std::getline(std::cin, name);
    if (name.empty()) { // if just hit enter previously, try again
        std::getline(std::cin, name);
    }
    std::cout << "Age: ";
    while (!(std::cin >> age)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid. Enter numeric Age: ";
    }
    std::cout << "Weight (kg): ";
    while (!(std::cin >> wt)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid. Enter numeric Weight: ";
    }
    std::cout << "Height (cm): ";
    while (!(std::cin >> ht)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid. Enter numeric Height: ";
    }
    std::cout << "Sex (M/F): ";
    std::cin >> sex;
    sex = static_cast<char>(std::toupper(static_cast<unsigned char>(sex)));
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nThank you. Press ENTER to proceed to diagnosis...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void diabetes::diagnosis() {
    std::cout << "\n** DIAGNOSIS WINDOW **\n";
    std::cout << "Let's have a look at symptoms. Please enter answers as prompted.\n";
    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void diabetes::getlevel1_symptoms() {
    std::cout << "\n*** MEDICAL DIAGNOSIS FORM - LEVEL 1 ***\n";
    int i = 0;
    auto ask = [&](const std::string &prompt) {
        std::cout << prompt << " : ";
        char c;
        std::cin >> c;
        s[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        ++i;
    };

    ask("APPETITE (H=HIGH / L=LOW / N=NORMAL)");
    ask("FREQUENCY OF THIRST (H/L/N)");
    ask("FREQUENCY OF URINATION (H/L/N)");
    ask("VISION (I=IMPAIRMENT / N=NORMAL)");
    ask("URINE SUGAR (P=PASSIVE / A=ACTIVE)");
    ask("KETONUREA (P=PASSIVE / A=ACTIVE)");
    ask("FASTING BLOOD SUGAR (H/L/N)");
    ask("RBS (H/L/N)");
    ask("FAMILY HISTORY OF DIABETES (P=PASSIVE / A=ACTIVE)");
    ask("OGTT (D=DIABETIC / N=NOT)");

    // clear leftover newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void diabetes::getlevel2_symptoms() {
    std::cout << "\n*** MEDICAL DIAGNOSIS FORM - LEVEL 2 ***\n";
    int j = 0;
    auto ask = [&](const std::string &prompt) {
        std::cout << prompt << " : ";
        char c;
        std::cin >> c;
        s[j] = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        ++j;
    };

    ask("PANCREATITIS (P/A)");
    ask("CARCINOMA (P/A)");
    ask("CIRRHOSIS (P/A)");
    ask("HCTS (H/L/N)");
    ask("HEPATITIS (P/A)");
    ask("HORMONAL DISORDER (P/A)");
    ask("PANCREATECTOMY (P/A)");

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void diabetes::getlevel3_symptoms() {
    std::cout << "\n*** MEDICAL DIAGNOSIS FORM - LEVEL 3 ***\n";
    int k = 0;
    auto ask = [&](const std::string &prompt) {
        std::cout << prompt << " : ";
        char c;
        std::cin >> c;
        s[k] = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        ++k;
    };

    ask("AGE (Y=Young / M=Middle / E=Elderly)");
    ask("BODY WEIGHT (N=Normal / A=Above normal / B=Below normal / O=Obese)");
    ask("DURATION (W=Weeks / M=Months / Y=Years)");
    ask("KETONUREA (P/A)");
    ask("AUTO ANTIBODIES (P/A)");

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int diabetes::analyse_symptoms(int n) {
    // Return -1 if criteria indicate diabetes (or secondary/NDID per level),
    // Return 0 otherwise
    int count = 0;
    int result = 0;

    switch (n) {
    case 1:
        // if OGTT (s[9]) == 'D' -> diabetic
        if (s.size() > 9 && s[9] == 'D') {
            result = -1;
        } else if (s.size() > 6 && s[5] == 'P' && s[6] == 'P' && s[7] == 'H') {
            // matches earlier logic: some combination -> diabetic
            result = -1;
        } else {
            for (int i = 0; i < 10; ++i) {
                char c = s[i];
                if (c == 'H' || c == 'P' || c == 'D' || c == 'I') ++count;
            }
            if (count > 5) result = -1;
            else result = 0;
        }
        break;

    case 2:
        // if any of indices 0..6 are 'P' or index 3 is 'H' then -1
        if ((s[0] == 'P') || (s[1] == 'P') || (s[2] == 'P') ||
            (s[3] == 'H') || (s[4] == 'P') || (s[5] == 'P') || (s[6] == 'P'))
            result = -1;
        else
            result = 0;
        break;

    case 3:
        // original code had some compound conditions; we approximate them here:
        // If pattern of first five characters matches certain combos -> result = 0 (insulin dependent)
        // else -> -1
        {
            bool ok = false;
            // pattern 1: Y N W P P
            if (s[0] == 'Y' && s[1] == 'N' && s[2] == 'W' && s[3] == 'P' && s[4] == 'P') ok = true;
            // pattern 2: Y B W P P
            if (s[0] == 'Y' && s[1] == 'B' && s[2] == 'W' && s[3] == 'P' && s[4] == 'P') ok = true;
            // pattern 3: Y N M P P
            if (s[0] == 'Y' && s[1] == 'N' && s[2] == 'M' && s[3] == 'P' && s[4] == 'P') ok = true;
            // pattern 4: Y N Y P P
            if (s[0] == 'Y' && s[1] == 'N' && s[2] == 'Y' && s[3] == 'P' && s[4] == 'P') ok = true;

            result = ok ? 0 : -1;
        }
        break;

    default:
        result = 0;
    }

    return result;
}

char diabetes::display_message(int n, int m) {
    char ch = 'N';
    std::cout << "\n-------------------------------------\n";
    if (n == 1) {
        if (m == 0) {
            std::cout << "THE PERSON IS NOT DIABETIC.\n";
            std::cout << "Press ENTER to quit.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            std::exit(0);
        } else { // m == -1
            std::cout << "THE PERSON IS DIABETIC.\n";
            std::cout << "Proceed to level 2? (Y/N): ";
            std::cin >> ch;
            ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return ch;
        }
    } else if (n == 2) {
        if (m == 0) {
            std::cout << "IT IS PRIMARY DIABETES.\n";
            std::cout << "Proceed to level 3? (Y/N): ";
            std::cin >> ch;
            ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return ch;
        } else { // m == -1
            std::cout << "IT IS SECONDARY DIABETES.\n";
            std::cout << "Press ENTER to quit.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            std::exit(0);
        }
    } else if (n == 3) {
        if (m == 0) {
            std::cout << "IT IS INSULIN DEPENDENT DIABETES.\n";
            std::cout << "Press ENTER to quit.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            std::exit(0);
        } else {
            std::cout << "IT IS NON-INSULIN DEPENDENT DIABETES.\n";
            std::cout << "Press ENTER to quit.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            std::exit(0);
        }
    }

    return ch;
}
