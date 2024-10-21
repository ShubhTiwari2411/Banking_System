# Banking System:
A simple console-based banking system written in C++ that allows users to manage bank accounts. The system supports opening new accounts, depositing, withdrawing funds, balance enquiries, closing accounts, and displaying all accounts. The data is persistently stored in a file, ensuring account information is saved between sessions.

# Features
-> Open Account: Create a new bank account with a unique account number, first name, last name, and initial balance.
-> Balance Enquiry: Check the balance of an existing account by entering the account number.
-> Deposit: Deposit money into an existing account.
-> Withdraw: Withdraw money from an account, provided the balance doesn't go below the minimum required balance.
-> Close Account: Delete an account from the system.
-> Show All Accounts: Display details of all bank accounts stored in the system.

# Minimum Balance
The system enforces a minimum balance of ₹500 for all accounts. Attempting to withdraw an amount that would reduce the balance below this threshold will raise an Insufficient_Funds exception.

# Requirements
-> C++ Compiler: You need a working C++ compiler like g++ to compile and run the code.
-> File I/O: The system uses a file named Bank.data for storing account information. Ensure that the file is created in the same directory as the compiled executable.

# Exception Handling
The system includes exception handling for insufficient funds when attempting to withdraw money that would reduce the balance below the minimum required amount.

# Data Persistence
All account data is stored in the Bank.data file, allowing the system to retain account information across different sessions.

