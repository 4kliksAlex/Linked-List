# Linked-List-Student-Database
[Background overview]  
A university campus card transaction information management system should be able to manage multiple transaction information of multiple students, to register the recorded date and money in each transaction record, and to calculate the balance after each transaction.

[Basics]  
1. Student list:
    1. record student numbers and names;
    2. read and save student data;
    3. add new students;
    4. query student information;
    5. delete student information;
    6. sort student list information by student number or name.  
2. Transaction records:
    1. Recording transaction time and the remaining amount in the student campus card after each recharge or payment;
    2. When appending recharge or transaction records, the transaction information should be automatically arranged according to the transaction date;
    3. Recalculate the remaining amount in the account after adding or deleting transaction records;
    4. Arrange the transactions according to time or in the order of transaction amount or in reverse order;
    5. Read and write the corresponding transaction journal data file for each student.

// Written in C++11.  
// This project contains some legacy code because it is a deeply modified fusion of our two old sample linked list projects (which have been used for many years i guess) from my teacher. 
