#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>
#include <string>
using namespace std;

struct item {
    string name;
    int quantity;
    double price;
};

/////////////////////////////////////////////////////////////
// CUSTOMER CLASS                                           //
/////////////////////////////////////////////////////////////
class Customer {
public:
    int id;
    string name;
    stack<item> items;
    Customer* next;
    static int counter;

    Customer(string n) {
        id = ++counter;
        name = n;
        next = NULL;
    }
};
int Customer::counter = 0;

/////////////////////////////////////////////////////////////
// CUSTOMER QUEUE CLASS                                    //
/////////////////////////////////////////////////////////////
class customer_queue {
    Customer* head;
    Customer* tail;

public:
    customer_queue() {
        head = tail = NULL;
    }

    void enqueue(string name) {
        Customer* newnode = new Customer(name);
        if (head == NULL)
            head = tail = newnode;
        else {
            tail->next = newnode;
            tail = newnode;
        }
    }

    Customer* getFront() {
        if (head == NULL) return NULL;
        return head;
    }

    Customer* findCustomer(string cname) {
        Customer* temp = head;
        while (temp != NULL) {
            if (temp->name == cname) return temp;
            temp = temp->next;
        }
        return NULL;
    }

    Customer* dequeue() {
        if (head == NULL) return NULL;
        Customer* temp = head;
        head = head->next;
        if (head == NULL) tail = NULL;
        temp->next = NULL;
        return temp;
    }

    void removeCustomer(string cname) {
        Customer* temp = head;
        Customer* prev = NULL;
        while (temp != NULL) {
            if (temp->name == cname) {
                if (prev == NULL)
                    head = temp->next;
                else
                    prev->next = temp->next;
                if (temp == tail) tail = prev;
                delete temp;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }

    void display() {
        if (head == NULL) {
            cout << "\nNo pending customers!\n";
            return;
        }
        cout << "\n----------------------------------------\n";
        cout << "Pending Customers:\n";
        cout << "----------------------------------------\n";
        Customer* temp = head;
        while (temp != NULL) {
            cout << temp->id << ". " << temp->name << endl;
            temp = temp->next;
        }
        cout << "----------------------------------------\n";
    }

    bool isEmpty() {
        return head == NULL;
    }
};

/////////////////////////////////////////////////////////////
// BILLING CLASS                                            //
/////////////////////////////////////////////////////////////
class billing {
public:
    void addItem(Customer* c) {
        if (c == NULL) {
            cout << "No customer found!\n";
            return;
        }
        char more;
        do {
            item it;
            cout << "\nEnter Item Name: ";
            getline(cin, it.name);
            cout << "Enter Quantity: ";
            cin >> it.quantity;
            cout << "Enter Price per unit: ";
            cin >> it.price;
            cin.ignore();

            c->items.push(it);
            cout << "Item added successfully!\n";

            cout << "Do you want to remove the last added item? (Y/N): ";
            char rem;
            cin >> rem;
            cin.ignore();
            if (rem == 'Y' || rem == 'y') {
                if (!c->items.empty()) {
                    cout << "Removing item: " << c->items.top().name << endl;
                    c->items.pop();
                } else {
                    cout << "No items to remove!\n";
                }
            }

            cout << "Add more items? (Y/N): ";
            cin >> more;
            cin.ignore();
        } while (more == 'Y' || more == 'y');
    }

    double viewBill(Customer* c) {
        if (c == NULL) {
            cout << "No customer to show bill!\n";
            return 0;
        }
        cout << "\n========================================\n";
        cout << "              BILL SUMMARY              \n";
        cout << "========================================\n";
        cout << "Customer Name: " << c->name << endl;
        cout << "----------------------------------------\n";
        cout << "Item\tQty\tPrice\tSubtotal\n";
        cout << "----------------------------------------\n";

        stack<item> temp = c->items;
        double total = 0;

        while (!temp.empty()) {
            item it = temp.top();
            temp.pop();
            double subtotal = it.quantity * it.price;
            cout << it.name << "\t" << it.quantity << "\t" << it.price
                 << "\t" << subtotal << endl;
            total += subtotal;
        }
        cout << "----------------------------------------\n";
        cout << "Total Bill: " << total << endl;
        cout << "========================================\n";
        return total;
    }
};

/////////////////////////////////////////////////////////////
// STRUCT TO STORE BILLED CUSTOMER INFO                     //
/////////////////////////////////////////////////////////////
struct BilledInfo {
    string name;
    vector<item> items;
    double total;
};

/////////////////////////////////////////////////////////////
// MAIN FUNCTION                                            //
/////////////////////////////////////////////////////////////
int main() {
    system("cls");
    customer_queue q;
    billing b;
    vector<BilledInfo> billedCustomers;
    int choice;

    do {
        cout << "\n==================== BILLING SYSTEM ====================\n";
        cout << "1. Enter New Customer\n";
        cout << "2. Show Pending Customers\n";
        cout << "3. Show Billed Customers\n";
        cout << "4. Exit\n";
        cout << "========================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string cname;
            cout << "\nEnter Customer Name: ";
            getline(cin, cname);

            q.enqueue(cname);
            cout << "\nCustomer added successfully!\n";

            Customer* c = q.getFront();
            cout << "\n1. Add Items for " << cname;
            cout << "\n2. Go to Main Menu\nEnter choice: ";
            int opt;
            cin >> opt;
            cin.ignore();

            if (opt == 1) {
                b.addItem(c);
                double total = b.viewBill(c);

                // Save billed info (preserve order)
                stack<item> temp = c->items;
                vector<item> stored;
                while (!temp.empty()) {
                    stored.insert(stored.begin(), temp.top());
                    temp.pop();
                }
                billedCustomers.push_back({c->name, stored, total});

                Customer* done = q.dequeue();
                delete done;
                cout << "Customer billed successfully!\n";

                if (!q.isEmpty()) {
                    cout << "\nPending customers left:\n";
                    q.display();
                }
            } else {
                cout << "Returning to Main Menu...\n";
            }
        }

        else if (choice == 2) {
            if (q.isEmpty()) {
                cout << "No pending customers!\n";
            } else {
                q.display();
                cout << "\n1. Add items for pending customer";
                cout << "\n2. Go to Main Menu\n";
                cout << "Enter your choice: ";
                int opt;
                cin >> opt;
                cin.ignore();

                if (opt == 1) {
                    string pname;
                    cout << "Enter pending customer name: ";
                    getline(cin, pname);
                    Customer* pendingC = q.findCustomer(pname);

                    if (pendingC) {
                        b.addItem(pendingC);
                        double total = b.viewBill(pendingC);

                        stack<item> temp = pendingC->items;
                        vector<item> stored;
                        while (!temp.empty()) {
                            stored.insert(stored.begin(), temp.top());
                            temp.pop();
                        }
                        billedCustomers.push_back({pendingC->name, stored, total});

                        q.removeCustomer(pname);
                        cout << "Customer billed successfully!\n";
                    } else {
                        cout << "Customer not found in pending list!\n";
                    }
                } else {
                    cout << "Returning to Main Menu...\n";
                }
            }
        }

        // ================= FIXED BILLED CUSTOMERS SECTION =================
        else if (choice == 3) {
    cout << "\n============== BILLED CUSTOMERS ==============\n";
    if (billedCustomers.empty())
        cout << "No billed customers yet.\n";
    else {
        for (int i = 0; i < billedCustomers.size(); i++) {
            cout << i + 1 << ". " << billedCustomers[i].name << " :: ";

            // Print items in compact format
            for (int j = 0; j < billedCustomers[i].items.size(); j++) {
                item it = billedCustomers[i].items[j];
                cout << it.name << "(" << it.quantity << ")";
                if (j != billedCustomers[i].items.size() - 1)
                    cout << ", ";
            }

            cout << "  Bill: " << billedCustomers[i].total << endl;
        }
    }
    cout << "\n=============================================\n";
}


        else if (choice == 4) {
            cout << "Exiting... Thank you!\n";
        }

        else {
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 4);

    return 0;
}