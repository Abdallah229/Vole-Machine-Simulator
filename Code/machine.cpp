#include "machine.h"
#define GREEN "\e[32m"
#define RESET "\e[0m"

void Machine::loadMemory(  vector<  string> Instructions)
{

    while (true)
    {
        cout << "Starting Memory Cell: ";
        string S;
        cin >> S;


        if (!cin.fail())
        {
            if (isHex(S) && IsStartValid(S))
            {
                int Start_Dec_temp = hexToDec(S); // Convert the starting address to decimal format
                if (Start_Dec_temp < 0 || Start_Dec_temp > 256 )
                {
                    cout << "Invalid location. Please choose another one!" << endl;
                    continue;
                }
                StartIterate = S;
                break;
            }
            else
            {
                cout << "Invalid Start. Please ensure it's not between 00 -> 0A." << endl;
                cin.clear();                                                   // Clear any error state flags
                cin.ignore(  numeric_limits<  streamsize>::max(), '\n'); // Remove all characters up to and including newline
                continue;
            }
        }
        else
        {
            cout << "Invalid input." << endl;
            cin.clear();                                                   // Clear any error state flags
            cin.ignore(  numeric_limits<  streamsize>::max(), '\n'); // Remove all characters up to and including newline
            cout << "Please enter a hexadecimal input like (01... FF)" << endl;
        }
    }
    cout << "\nLoading memory..." << endl;
    
    int Start_Dec = hexToDec(StartIterate); // Convert the starting address to decimal format
    // Load instructions sequentially into memory, starting from the available cell
    for (size_t i = 0; i < Instructions.size(); i++)
    {
        int address = Start_Dec + i;                        // Calculate the current memory address as decimal
        string hexAddress = decToHex(address);         // Convert address to hex format
        memoryMachine.setCell(hexAddress, Instructions[i]); // Store instruction in memory
    }

   cout<<endl;
}

void Machine::loadProgram()
{
    // Convert the starting address from hexadecimal to decimal
    int Start_Dec = hexToDec(StartIterate);
    cout << "Loading program..." << endl << endl;

    // Calculate the ending address for the program instructions based on the start address and instruction size
    int end = InstSize + Start_Dec;
     cpu.setPc( StartIterate  ) ;
    // Loop through memory from the starting address to the end of the instructions
    for (int i = Start_Dec; i < end; i++)
    {
        
        cpu.control(memoryMachine ); // Execute the current instruction in the control unit (CPU)
        // Handle any jump if specified
        if (cpu.IsJump != 0) // Check if a jump instruction was executed
        {
            i += cpu.IsJump - 1;                              // Adjust loop counter to reflect jump (subtract 1 due to the loop's increment)
            cout << "There is a Jump has been Done " << endl; // Output jump amount
            cpu.IsJump = 0;                                   // Reset jump value after handling
        }
        // Check if the CPU has faced a halt command
        if (cpu.IsHalt)
        {
            IsHalt = true;          // Set the machine's halt flag
            cout << "Halt" << endl; // Print halt message to indicate end of program execution
            break;                  // Exit the loop as program has halted
        }

        // Introduce a delay before the stateOut() function
        this_thread::sleep_for(  chrono::milliseconds(1750));
        stateOut(); // Output the current state of the machine
        // if(memoryMachine.getCell("FF") != "00")
        // {
        //     cout << "Memory Full !! "<<endl; 
        //     break;  
        // }
    }
}

void DisplayMemory(Memory Mem)
{
    cout << "     "; // Initial spacing for the top row of column headers

    // Print column headers (0-9 and A-F) for the memory layout
    for (size_t i = 0; i < 16; i++)
    {
        if (i >= 10 && i <= 15)
            cout << static_cast<char>('A' + (i - 10)) << "    "; // Convert values 10-15 to 'A'-'F'
        else
            cout << i << "    "; // Print numbers 0-9 as-is
    }

    cout << endl << endl; 

    // Iterate through rows for displaying memory content
    for (size_t i = 0; i < 16; i++)
    {
        // Print row header (0-9 and A-F) to the left
        if (i >= 10 && i <= 15)
            cout << static_cast<char>('A' + (i - 10)) << "    "; // Convert values 10-15 to 'A'-'F'
        else
            cout << i << "    "; // Print numbers 0-9 as-is

        // First hex digit of the address for the current row
        char firstDigit = ConvertDigit(i);

        // Iterate through columns for each memory cell in the row
        for (size_t j = 0; j < 16; ++j) // Second hex digit (0 to F)
        {
            char secondDigit = ConvertDigit(j);                         // Convert column index to hex digit
            string key = string(1, firstDigit) + secondDigit; // Form the full memory address
            int tempo = hexToDec(key);
            tempo -= 1; 
            // Print the memory cell content at the current address
            if (Mem.getCell(key) != "00" || ((Mem.getCell(decToHex(tempo))[0] != '0') && tempo >= 0)){
                cout << GREEN << Mem.getCell(key) << RESET << "   ";
            }
            else
            {
                cout << Mem.getCell(key) << "   ";
            }
        }

        cout << endl; 
    }
}


void Machine::stateOut()
{
    cout << "state out..." <<endl << endl ;
    DisplayMemory(memoryMachine);
    cout << endl<< endl;
    cpu.DisplayRegister();
    cout <<endl; 
   
}
void Machine::RunMachine()
{
    InstSize = Instructions.size() / 2 ; 
    loadMemory(Instructions);
    loadProgram();
    stateOut();
}
void Machine::setInstructions(vector<string> Inst)
{
    Instructions = Inst ;
}