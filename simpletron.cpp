/*  This program creates a simple machine with 100-word memory, each word is 
    a four digit signed integer. And it can understand it own
    "Simpletron Machine Language" (SML). The first two digits of a word
    are an instruction, while the other two are a memory location

*/

#include <iostream>
#include <iomanip>
#include <array>        
#include <cstddef>      
#include <algorithm>    
#include <stdexcept>     
#include <iterator>     

using namespace std;

// display all registers and contents of memory
void registerMemoryDump(const int mem[], int a, int iC, int iR, int oC, int op);


int main()
{
    // special registers
    int accumulator{ 0 };           // accumulator register
    int memory[100]{};              // 100-word memory
    int instructionCounter{ 0 };    // memory location
    int operationCode{ 0 };         // operation
    int operand{ 0 };               // memory location for operation
    int instructionRegister{ 0 };   // transfered instruction
    
    // display header
    cout << "Welcome to Simpletron!\n";
    cout << "Please enter your program one instruction\n";
    cout << "(or data word) at a time. I will type the\n";
    cout << "location number and a question mark(?).\n";
    cout << "You then type the word for that location.\n";
    cout << "Type the sentinel -99999 to stop entering\n";
    cout << "your program.\n" << endl;
    
    
    
    int input{ 0 };             // user input  
    size_t index{ 0 };          // input memory location
    bool terminate{ false };
    
    // accept input until sentinel is entered or system runs out of memory
    while (input != -99999 && index<100 ) {

        // next instruction
        cout << setw(2) << setfill('0') << index << " ?+ ";
        cin >> input;

        // value range check
        while (input != -99999 && (input < -9999 || input>9999) ) {
            cout << "Invalid input, please reenter:\n";
            cout << setw(2) << setfill('0') << index << " ? ";
            cin >> input;
        }

        // input operation is assigned to a memory location
        if (input!=-99999){
            memory[index++] = input;
        }
    }
    
    cout << endl;

    // process every instruction, maximum operations is 100
    while (instructionCounter < 100 && !terminate) {

        // fetch contents and extract operation code and operand
        instructionRegister = memory[instructionCounter];
        operationCode = instructionRegister / 100;          
        operand = instructionRegister % 100;                


        switch (operationCode) {

        case (10): // input value
            cout << "? ";
            cin >> memory[operand];
            ++instructionCounter;   

            // value is out of range
            if (memory[operand] < -9999 || memory[operand]>9999) {
                cout << "\n\nValue out of range\n";
                cout << "Simpletron execution abnormally terminated" << endl;
                terminate = true;
            }
            break;


        case(11): // output value stored in memory 
            cout << "Simpletron says: " << memory[operand] << endl;
            ++instructionCounter;   
            break;


        case(20): // load value from memory to accumulator
            accumulator = memory[operand];
            ++instructionCounter;
            break;


        case(21): // store a value in the memory
            memory[operand] = accumulator;
            ++instructionCounter;
            break;


        case(30): // add value to accumulator
            accumulator += memory[operand];

            // overflow error
            if (accumulator < -9999 || accumulator>9999) {
                cout << "\n\nOverflow\n";
                cout << "Simpletron execution abnormally terminated" << endl;
                terminate = true;
            }
            ++instructionCounter;
            break;


        case(31): // substract a value from accumulator
            accumulator -= memory[operand];
           
            // overflow error
            if (accumulator < -9999 || accumulator>9999) {
                cout << "\n\nOverflow\n";
                cout << "Simpletron execution abnormally terminated" << endl;
                terminate = true;
            }
            ++instructionCounter;
            break;


        case(32): //divide values
         
            // divide by zero is made
            if (memory[operand]==0) {
                cout << "\n\nError divide by zero\n";
                cout << "Simpletron execution abnormally terminated" << endl;
                terminate = true;
            }
            else {  //divide
                accumulator /= memory[operand];
            }
            ++instructionCounter; 
            break;


        case(33):  // multiply accumulator by value
            accumulator *= memory[operand];
            
            // overflow error
            if (accumulator < -9999 || accumulator>9999) {
                cout << "\n\nOverflow\n";
                cout << "Simpletron execution abnormally terminated" << endl;
                terminate = true;
            }

            ++instructionCounter; 
            break;


        case(40): // branch to the memory location indicated

            // bounds check
            if (operand < 0 || operand>99) {
                cout << "\n\nAttempt to access element out of array bounds\n";
                cout << "Simpletron execution abnormally terminated" << endl;
                terminate = true;
            }
            else {
                instructionCounter = operand;
            }
            break;

        case(41): // branch if accumulator is negative, else continue sequence

            // bounds check
            if (operand < 0 || operand>99) {
                cout << "\n\nAttempt to access element out of array bounds\n";
                cout << "Simpletron execution abnormally terminated" << endl;
                terminate = true;
            }

            // branch if value is negative, else continue with next operation
            else if (accumulator < 0) {
                instructionCounter = operand;
            }
            else {
                ++instructionCounter; 
            }
            break;


        case(42): // branch if accumulator is zero, else continue sequence
            if (operand < 0 || operand>99) {
                cout << "\n\nAttempt to access element out of array bounds\n";
                cout << "Simpletron execution abnormally terminated" << endl;
                terminate = true;
            }

            // branch if value is zero, else continue with next operation
            else if (accumulator == 0) {
                instructionCounter = operand;
            }
            else {
                ++instructionCounter;
            }
            break;


        case(43): // terminate program
            cout << "\nSimpletron execution terminated" << endl;
            instructionCounter = index;
            terminate = true;
            break;


        default: // unrecognized operation, terminates program
            cout << "Invalid operation code" << endl;
            terminate = true;
            break;
        }
    }


    // always display register memory dump
    registerMemoryDump(memory, accumulator, instructionCounter,
        instructionRegister, operationCode, operand);


}   //end of main

 

// display all the registers and contents of memory
void registerMemoryDump(const int mem[], int a, int iC, int iR, int oC, int op) {

    cout << "\nREGISTERS:\n";

    cout << showpos << setfill('0') << internal;
    cout << "accumulator\t\t" << setw(5) << a;

    cout << noshowpos << setfill('0') << internal;
    cout << "\nInstructionCounter\t   " << setw(2) << iC;

    cout << showpos << setfill('0') << internal;
    cout << "\nInstructionRegister\t" << setw(5) << iR;

    cout << noshowpos << setfill('0') << internal;
    cout << "\noperationCode\t\t   " << setw(2) << oC;
    cout << "\noperand\t\t\t   " << setw(2) << op;
    

    // memory subscript header 0-10
    cout << "\n\nMEMORY:\n   ";
    for (int x{ 0 };x < 10;x++) {
        cout << noshowpos << setfill(' ') << internal;
        cout << setw(5) << x << " ";
    }

    
    // contents of memory displayed in tabular form
    for (size_t index{ 0 }; index < 100;index++) {
        cout << noshowpos << setfill(' ') << internal;
        if (index % 10 == 0) {
            cout << endl;
            cout << setw(2) << index << " ";
        }
        cout << showpos << setfill('0') << internal;
        cout << setw(5) << mem[index] << " ";
    }

    cout << endl;
}
