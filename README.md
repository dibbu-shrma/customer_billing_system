# customer_billing_system

📌 Project Title

Customer Billing System (C++)

📖 Description

A console-based billing system built in C++ that manages customers in a queue and generates itemized bills. It uses data structures like stacks, queues (linked list), and vectors to handle real-time billing and customer processing.

⚙️ Features
Add new customers to queue
Manage pending customers
Add/remove items using stack (LIFO)
Generate detailed bill with total calculation
Store and display billed customers


🧠 Concepts Used

Stack (for item handling)
Queue using Linked List (for customers)
Vectors (for storing billed records)
Object-Oriented Programming (OOP)


🛠️ Tech Used

C++
STL (stack, vector, string)


▶️ How to Run

g++ customer_billing_system.cpp -o app
./app


📂 Project Structure

customer_billing_system.cpp → Complete implementation
🧾 Sample Output

<img width="382" height="455" alt="image" src="https://github.com/user-attachments/assets/0e99e92e-c9d3-4737-ba03-1ce39b361b58" />

<img width="477" height="136" alt="image" src="https://github.com/user-attachments/assets/dcd20349-8080-4073-85b2-e0049f346ce3" />

⚠️ Limitations

No database/file storage (data resets on exit)
Console-based UI only
Customer search is name-based (no unique validation)
