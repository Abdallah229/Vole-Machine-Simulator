#include "methods.h"

/// Get Instruction from File  Functions
string GetPath()
{
    string Res;
    cout << "\nPlease Enter The Path Like This Formula ---> C:\\Users\\YourUsername\\Documents\\example.txt" << endl << endl;
    cout << "Please Enter The Path Of The File: ";
    getline(cin, Res);
    return Res;
}
             ////////////////////////////////////////////////////////////////
string GetFileContent()
{
    string Result;

    while (true)
    {
        string Path = GetPath();
        ifstream File(Path); // Open the file using ifstream
        if (File.is_open())
        {                                                                           // Check if the file failed to open
            cout << Path << " Was Opened Successfully" << endl; // Debugging line
            stringstream Content;
            Content << File.rdbuf(); // Read the entire file content
            Result = Content.str();  // Store the content in a string
            File.close();            // Close the file
            break;
        }
        else
        { // File wasnt opened successfully
            cout << "Unable To Open The File " << Path <<  "Please Choose Another One With (.txt) Format" << endl;
        }
    }
    return Result; // Return the file content
}
                ///////////////////////////////////////////////////////////////
bool CheckInst(string Inst)
{
    if (!isdigit(Inst[0]) && (Inst[0] != 'B' || Inst[0] != 'C'))
        return false;

    return true;
}
                //////////////////////////////////////////////////////////////////
vector<string> ExtractInst(string Content )
{
    //string Content = GetFileContent();
    vector<string> inst;
    string temp;
    for (size_t i = 0; i < Content.size(); i++)
    {
        // Corrected the condition for alpha to ensure it checks both ranges properly
        bool alpha = isdigit(Content[i]) || (Content[i] >= 'A' && Content[i] <= 'F');
        // If temp has 4 characters, push them as two separate hex pairs
        if (temp.size() == 4)
        {
            if (CheckInst)
            {
                inst.push_back(temp.substr(0, 2));
                inst.push_back(temp.substr(2, 2));
                temp.clear();
            }
        }

        // If the character is a space and temp size is less than 4 or if the character is not valid, clear temp
        if ((isspace(Content[i]) && temp.size() < 4) || !alpha)
        {
            temp.clear(); // Invalid instruction
            continue;
        }

        // If the character is valid, add it to temp
        if (alpha)
        {
            temp += Content[i];
        }
    }

    // Ensure any remaining valid temp content is added
    if (!temp.empty() && temp.size() == 4)
    {
        inst.push_back(temp.substr(0, 2));
        inst.push_back(temp.substr(2, 2));
    }
    cout << endl;
    return inst;
}
//////////////////////////////////////////////////////////////////////////////////////
/// Converters Functions
int stringToInt(const string &str)
{
    int Temp = 0;
    bool isNegative = false;
    size_t i = 0;

    // Check for a negative sign
    if (str[0] == '-')
    {
        isNegative = true;
        i = 1; // Start conversion from the next character
    }
    // 0010->0001
    // Convert each character to its numeric value
    for (; i < str.size(); ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            Temp = Temp * 10 + (str[i] - '0');
        }
        else
        {
            cout << "Invalid input: non-numeric character found!" << endl;
            return 0; // or handle error as needed
        }
    }

    return isNegative ? -Temp : Temp;
}
            //////////////////////////////////////////////////////////////////

int hexToDec(std :: string hex)
{
    int dec = stoi(hex, nullptr, 16);
    return dec;
}
string decToHex(int dec)
{
    if (dec == 0)
    {
        return "00";
    }

    string hexDigits = "0123456789ABCDEF";
    string hexadecimal = "";

    while (dec > 0)
    {
        int remainder = dec % 16;
        hexadecimal = hexDigits[remainder] + hexadecimal;
        dec /= 16;
    }
    if (hexadecimal.length() < 2) hexadecimal = "0" + hexadecimal;
    return hexadecimal;
}
            //////////////////////////////////////////////////////////////////
string hexToBin(const string& hex) {
     string bin;
    for (char ch : hex) {
        int n = (ch >= '0' && ch <= '9') ? ch - '0' : ch - 'A' + 10;
        bin += bitset<4>(n).to_string();
    }
    return bin;
}
            //////////////////////////////////////////////////////////////////
// Convert binary string to hex string
string binToHex(const string& bin) {
    int  dec = stoi(bin, nullptr,2);
//    cout<<"decimal :"<<dec<<endl;
    string hex = decToHex(dec);
    return hex;
}
//////////////////////////////////////////////////////////////////////////////////////
char ConvertDigit(int i)
{
    char Digit;
    if (i < 10)
    {
        Digit = '0' + i; // '0' to '9'
    }
    else
    {
        Digit = 'A' + (i - 10); // 'A' to 'F'
    }
    return Digit;
}
//////////////////////////////////////////////////////////////////////////////////////
/// Operations On Binary Functions
string addBin(string bin1, string bin2)
{
    string result_bin;
    int carry = 0;

    // Add binary strings from the last bit to the first
    for (int i = bin1.size() - 1; i >= 0; --i)
    {
        int bit1 = bin1[i] - '0';
        int bit2 = bin2[i] - '0';
        int sum = bit1 + bit2 + carry;
        result_bin = char((sum % 2) + '0') + result_bin;
        carry = sum / 2;
    }

    if (carry == 1)
    {
        result_bin = "1" + result_bin;
    }

    return result_bin;
 }

 //////////////////////////////////////////////////////////////////
 string subBin(const string &bin1, const string &bin2)
 {
     string result;
     int borrow = 0;

     for (int i = 0; i < bin1.size(); ++i)
     {
         int bit1 = i < bin1.size() ? bin1[bin1.size() - 1 - i] - '0' : 0;
         int bit2 = i < bin2.size() ? bin2[bin2.size() - 1 - i] - '0' : 0;
         int diff = bit1 - bit2 - borrow;

         if (diff < 0)
         {
             diff += 2;
             borrow = 1;
         }
         else
         {
             borrow = 0;
         }
         result = to_string(diff) + result;
     }

     // Remove leading zeros
     while (result.size() > 1 && result[0] == '0')
     {
         result = result.substr(1);
     }

     return result;
}
//////////////////////////////////////////////////////////////////////////////////////
/// Functions To Generate The Machine Components
void GenerateMemory( map< string,  string> &m)
{
    for (size_t i = 0; i < 16; ++i) // First hex digit (0 to F)
    {
        char firstDigit;
        if (i < 10)
        {
            firstDigit = '0' + i; // '0' to '9'
        }
        else
        {
            firstDigit = 'A' + (i - 10); // 'A' to 'F'
        }

        for (size_t j = 0; j < 16; ++j) // Second hex digit (0 to F)
        {
            char secondDigit;
            if (j < 10)
            {
                secondDigit = '0' + j; // '0' to '9'
            }
            else
            {
                secondDigit = 'A' + (j - 10); // 'A' to 'F'
            }

             string key =  string(1, firstDigit) + secondDigit;
            m[key] = "00"; // Initialize the map with "00"
        }
    }
}
            //////////////////////////////////////////////////////////////////
void GenerateRegister(map<string, string> &r)
{
    for (size_t i = 0; i < 16; ++i) // First hex digit (0 to F)
    {
        char firstDigit;
        if (i < 10)
        {
            firstDigit = '0' + i; // '0' to '9'
        }
        else
        {
            firstDigit = 'A' + (i - 10); // 'A' to 'F'
        }
         string key = "";
        key += firstDigit;
        r[key] = "00"; // Initialize the map with empty values
    }
}
//////////////////////////////////////////////////////////////////////////////////////
/// Functions For Menu
char GetChoice(const string &Message, const string &Choices, char Start, char End)
{
    char Choice;

    while (true)
    {
        cout << endl
             << Message << endl;
        cout << Choices << endl;
        cout << "Your Choice: ";

        string input;
        cin >> input;

        // Check if input length is 1 to ensure single character entry
        if (input.length() != 1)
        {
            cout << "Invalid input. Please enter a single character." << endl;
            continue;
        }

        // Get the first character and convert to uppercase
        Choice = toupper(input[0]);

        // Check if the character is either Start or End
        if (Choice == Start || Choice == End)
        {
            break;
        }
        else
        {
            cout << "Invalid choice. Please choose a valid one (" << Start << " / " << End << ")." << endl;
        }
    }

    return Choice;
}

            //////////////////////////////////////////////////////////////////
bool IsPowerOf2(int num)
{
    if (num <= 0)
        cout << "Error : Invalid Size !!" << endl;
    while (num % 2 == 0)
    {
        num = num / 2;
    }
    return (num == 1);
}
//////////////////////////////////////////////////////////////////////////////////////
bool IsStartValid(string &str)
{
    try
    {
        int tmp = hexToDec(str);
        return tmp >= 10;
    }
    catch (const out_of_range &)
    {
        // Handle the case where the hex string is too large to convert to int
        cout << "Error: The entered hex value is out of range." << endl;
        return false;
    }
    catch (const invalid_argument &)
    {
        // Handle the case where hexToDec fails due to an invalid argument
        cout << "Error: Invalid hexadecimal format." << endl;
        return false;
    }
}
////////////////////////////////////////////////////////////////////////////
bool isHex( string &str)
{
    // Check if all characters in the string are valid uppercase hex digits
    for (char c : str)
    {
        if (! isxdigit(c) || ( isalpha(c) && ! isupper(c)))
        {
            return false; // Return false if any character is not a hex digit or not uppercase
        }
    }
    return true;
}
