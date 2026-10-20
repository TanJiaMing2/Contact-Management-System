#include <iostream>
#include <string>

using namespace std;

// Define a structure for storing contact details
struct Contact
{
    string fName;
    string lName;
    string email;
    long long phNo;

    // Constructor to initialize contact details
    Contact(string fName, string lName, string email, long long phNo)
    {
        this->fName = fName;
        this->lName = lName;
        this->email = email;
        this->phNo = phNo;
    }
};

// Define a structure for a node in the linked list
struct Node
{
    Contact contact;
    Node *next;

    // Constructor to initialize node with a contact
    Node(Contact contact) : contact(contact), next(nullptr) {}
};

// Define a class for the contact management system using linked list
class ContactList
{
private:
    Node *head; // Head of the linked list

public:
    // Constructor to initialize an empty linked list
    ContactList() : head(nullptr) {}

    // Destructor to free memory allocated for nodes
    ~ContactList()
    {
        Node *current = head;
        while (current)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }

    // Function to add a new contact to the linked list
    void addContact(const Contact &contact)
    {
        // Check if a contact with the same phone number already exists
        Node *current = head;
        while (current)
        {
            if (current->contact.phNo == contact.phNo)
            {
                cout << "A contact with the same phone number already exists." << endl;
                return; // Exit function without adding the contact
            }
            current = current->next;
        }

        // If no contact with the same phone number exists, add the new contact
        Node *newNode = new Node(contact);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            current = head;
            while (current->next)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void displayAllContacts()
    {
        Node *current = head;
        while (current)
        {
            displayContact(current->contact);
            current = current->next;
        }
    }

    void displayContact(const Contact &contact)
    {
        cout << "Name: " << contact.fName << " " << contact.lName << " " << "Phone: " << contact.phNo << " " << "Email: " << contact.email << endl;
    }

    // Function to search for a contact by first name
    void searchByFirstName(string &fName)
    {
        Node *current = head;
        bool found = false;
        while (current)
        {
            if (current->contact.fName == fName)
            {
                displayContact(current->contact);
                found = true;
                break;
            }
            current = current->next;
        }
        if (!found)
        {
            cout << "Contact not found." << endl;
        }
    }
    // Function to edit a contact by first name
    void editContact(string &fName)
    {
        if (!head)
        {
            cout << "No contact available." << endl;
            return;
        }
        Node *current = head;
        while (current)
        {
            if (current->contact.fName == fName)
            {
                cout << "Editing contact for " << fName << " " << current->contact.lName << endl;
                cout << "Enter new first name(Press Enter to skip changes): ";
                string newFName;

                getline(cin, newFName);
                if (!newFName.empty())
                {
                    current->contact.fName = newFName;
                }

                cout << "Enter new last name(Press Enter to skip changes):  ";
                string newLName;
                getline(cin, newLName);
                if (!newLName.empty())
                {
                    current->contact.lName = newLName;
                }

                cout << "Enter new phone (Press Enter to skip changes):  ";
                string newPhNoStr;
                getline(cin, newPhNoStr);

                while (!newPhNoStr.empty())
                {
                    try
                    {
                        long long newPhNo = stoll(newPhNoStr);
                        current->contact.phNo = newPhNo;
                        break; // Exit the loop if input is valid
                    }
                    catch (const invalid_argument &)
                    {
                        cout << "Invalid number, try again or press Enter to skip changes: ";
                        getline(cin, newPhNoStr);
                    }
                }

                cout << "Enter new email(Press Enter to skip changes):  ";
                string newEmail;
                getline(cin, newEmail);
                if (!newEmail.empty())
                {
                    current->contact.email = newEmail;
                }

                cout << "Contact updated successfully." << endl;
                return;
            }
            current = current->next;
        }
        cout << "Contact not found." << endl;
    }

    // Function to delete a contact by first name
    void deleteByFirstName(string &fName)
    {
        if (!head)
        {
            cout << "Contact list is empty." << endl;
            return;
        }
        if (head->contact.fName == fName)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            cout << "Contact deleted successfully." << endl;
            return;
        }
        Node *current = head->next;
        Node *prev = head;
        while (current)
        {
            if (current->contact.fName == fName)
            {
                prev->next = current->next;
                delete current;
                cout << "Contact deleted successfully." << endl;
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "Contact not found." << endl;
    }

    // Function to sort contacts alphabetically by last name (using bubble sort)
    void sortContactsByName()
    {
        if (!head || !head->next)
        {
            return; // No need to sort if the list is empty or has only one element
        }

        bool swapped;
        do
        {
            swapped = false;
            Node *current = head;
            Node *prev = nullptr;
            Node *next = head->next;

            while (next)
            {
                if (current->contact.fName > next->contact.fName)
                {
                    if (prev)
                    {
                        prev->next = next;
                    }
                    else
                    {
                        head = next;
                    }
                    current->next = next->next;
                    next->next = current;
                    swapped = true;
                    prev = next;
                    next = current->next;
                }
                else
                {
                    prev = current;
                    current = next;
                    next = next->next;
                }
            }
        } while (swapped);
    }
};

int main()
{
    ContactList contactList;

    int choice;
    long long phNo;
    string fName, lName, email;

    while (true)
    {
        cout << "\nContact Management System";
        cout << "\n+----------------------+";
        cout << "\n[1] Add contact";
        cout << "\n[2] List all contacts";
        cout << "\n[3] Search for contact";
        cout << "\n[4] Edit contact";
        cout << "\n[5] Delete contact";
        cout << "\n[0] Exit";
        cout << "\n+----------------------+";
        cout << "\nChoose an option: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character left in the input buffer

        switch (choice)
        {
        case 1:
            cout << "Enter first name: ";
            getline(cin, fName); // Use getline to read the full line
            cout << "Enter last name: ";
            getline(cin, lName); // Use getline to read the full line

            while (true)
            {
                cout << "Enter phone: ";
                cin >> phNo;

                if (cin.fail())
                {                // Check if the input is not an integer
                    cin.clear(); // Clear the error flag
                    string invalidInput;
                    cin >> invalidInput; // Read the invalid input as a string
                    cout << "Invalid number, try again." << endl;
                }
                else
                {
                    cin.ignore(); // Ignore the newline character left in the input buffer
                    break;
                }
            }

            cout << "Enter email: ";
            getline(cin, email); // Use getline to read the full line
            contactList.addContact(Contact(fName, lName, email, phNo));
            cout << "Contact added successfully. Returning to the main menu..." << endl;
            break;

        case 2:
            cout << "\nList of all contacts:" << endl;
            contactList.sortContactsByName();
            contactList.displayAllContacts();
            break;
        case 3:
            cout << "Enter first name to search: ";
            getline(cin, fName); // Use getline to read the full line
            cout << "\nSearch Result:" << endl;
            contactList.searchByFirstName(fName);
            break;
        case 4:
            cout << "Enter first name to edit: ";
            getline(cin, fName); // Use getline to read the full line
            contactList.editContact(fName);
            break;
        case 5:
            cout << "Enter first name to delete: ";
            getline(cin, fName); // Use getline to read the full line
            contactList.deleteByFirstName(fName);
            break;
        case 0:
            cout << "\nThank you for using Contact Management System." << endl;
            return 0;
        default:
            cout << "Invalid option" << endl;
        }
    }

    return 0;
}