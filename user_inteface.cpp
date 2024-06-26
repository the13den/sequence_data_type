#include <iostream>
#include "dynamic_array.h"
#include "linked_list.h"
#include "array_sequence.h"
#include "list_sequence.h"

using namespace std;

// Function Prototypes
void display_dynamic_array_menu();
void run_dynamic_array();
void display_linked_list_menu();
void run_linked_list();
void display_array_sequence_menu();
void run_array_sequence();
void display_list_sequence_menu();
void run_list_sequence();
void display_menu();
void run_main_menu();
void create_new_dynamic_array();
void copy_dynamic_array();
void delete_dynamic_array();
void get_item_by_index();
void get_size_of_dynamic_array();
void set_element_at_index();
void resize_dynamic_array();
void print_dynamic_array();
void create_new_linked_list();
void copy_linked_list();
void delete_linked_list();
void get_first_linked_list();
void get_last_linked_list();
void append_linked_list();
void prepend_linked_list();
void concat_linked_list();
void get_subsequence_linked_list();
void print_linked_list();
void create_new_array_sequence();
void copy_array_sequence();
void delete_array_sequence();
void get_first_array_sequence();
void get_last_array_sequence();
void append_array_sequence();
void prepend_array_sequence();
void get_subsequence_array_sequence();
void print_array_sequence();
void create_new_list_sequence();
void copy_list_sequence();
void delete_list_sequence();
void get_first_list_sequence();
void get_last_list_sequence();
void append_list_sequence();
void prepend_list_sequence();
void get_subsequence_list_sequence();
void print_list_sequence();

DynamicArray<int>* dynamic_array = nullptr;  // Global pointer to DynamicArray
LinkedList<int>* linked_list = nullptr;     // Global pointer to LinkedList
ArraySequence<int>* array_sequence = nullptr; // Global pointer to ArraySequence
ListSequence<int>* list_sequence = nullptr;  // Global pointer to ListSequence

void display_menu() {
    cout << "---------------------------------------------------------" << endl;
    cout << "                       Main menu                         " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Choose data structure by sending number of structure     " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "1. DynamicArray" << endl;
    cout << "2. LinkedList" << endl;
    cout << "3. ArraySequence" << endl;
    cout << "4. ListSequence" << endl;
    cout << "0. Exit\n" << endl;
}

void run_main_menu() {
    int choice;
    do {
        display_menu();
        cin >> choice;
        switch (choice) {
            case 1:
                run_dynamic_array();
                break;
            case 2:
                run_linked_list();
                break;
            case 3:
                run_array_sequence();
                break;
            case 4:
                run_list_sequence();
                break;
            case 0:
                cout << "Exit\n" << endl;
                return;
            default:
                cout << "\n***********      Warning: Invalid choice      ***********\n" << endl;
                break;
        }
    } while (true);
}

void display_dynamic_array_menu() {
    cout << "---------------------------------------------------------" << endl;
    cout << "                      DynamicArray                       " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Choose operation by sending number of operation          " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "1. Create new array" << endl;
    cout << "2. Copy array" << endl;
    cout << "3. Delete array" << endl;
    cout << "4. Get item by index" << endl;
    cout << "5. Get size of dynamic array" << endl;
    cout << "6. Set element at index" << endl;
    cout << "7. Resize array" << endl;
    cout << "8. Print array" << endl;
    cout << "0. Exit\n" << endl;
}

void create_new_dynamic_array() {
    int choice;
    cout << "Choose initialization method:\n1. Initialize by value\n2. Initialize by list of items\n";
    cin >> choice;
    if (choice == 1) {
        int size, fill_value;
        cout << "Enter size of array: ";
        cin >> size;
        cout << "Enter fill value: ";
        cin >> fill_value;
        dynamic_array = new DynamicArray<int>(size, fill_value);
        cout << "New dynamic array created." << endl;
    } else if (choice == 2) {
        int size;
        cout << "Enter size of array: ";
        cin >> size;
        int* items = new int[size];
        cout << "Enter " << size << " items:\n";
        for (int i = 0; i < size; i++) {
            cin >> items[i];
        }
        dynamic_array = new DynamicArray<int>(size, items);
        delete[] items;
        cout << "New dynamic array created." << endl;
    } else {
        cout << "Invalid choice." << endl;
    }
}

void copy_dynamic_array() {
    if (dynamic_array == nullptr) {
        cout << "No array to copy." << endl;
        return;
    }
    DynamicArray<int> copied_dynamic_array(*dynamic_array);
    cout << "Array copied." << endl;
    // printing array
    int size = copied_dynamic_array.GetSize();
    cout << "Copied array contents: ";
    for (int i = 0; i < size; i++) {
        cout << copied_dynamic_array.Get(i) << " ";
    }
    cout << "Copied array was shown and was deleted now ^>^";
}

void delete_dynamic_array() {
    delete dynamic_array;
    dynamic_array = nullptr;
    cout << "Array deleted." << endl;
}

void get_item_by_index() {
    if (dynamic_array == nullptr) {
        cout << "No array exists." << endl;
        return;
    }
    int index;
    cout << "Enter index: ";
    cin >> index;
    try {
        int value = dynamic_array->Get(index);
        cout << "Item at index " << index << ": " << value << endl;
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }
}

void get_size_of_dynamic_array() {
    if (dynamic_array == nullptr) {
        cout << "No array exists." << endl;
        return;
    }
    int size = dynamic_array->GetSize();
    cout << "Size of dynamic array: " << size << endl;
}

void set_element_at_index() {
    if (dynamic_array == nullptr) {
        cout << "No array exists." << endl;
        return;
    }
    int index, value;
    cout << "Enter index: ";
    cin >> index;
    cout << "Enter value: ";
    cin >> value;
    try {
        dynamic_array->Set(index, value);
        cout << "Element set at index " << index << endl;
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }
}

void resize_dynamic_array() {
    if (dynamic_array == nullptr) {
        cout << "No array exists." << endl;
        return;
    }
    int new_size, fill_value;
    cout << "Enter new size: ";
    cin >> new_size;
    cout << "Enter fill value: ";
    cin >> fill_value;
    try {
        dynamic_array->Resize(new_size, fill_value);
        cout << "Array resized to " << new_size << " with fill value " << fill_value << endl;
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }
}

void print_dynamic_array() {
    if (dynamic_array == nullptr) {
        cout << "No array exists." << endl;
        return;
    }
    int size = dynamic_array->GetSize();
    cout << "Array contents: ";
    for (int i = 0; i < size; i++) {
        cout << dynamic_array[i] << " ";
    }
    cout << endl;  // To ensure the output ends with a newline
}

void run_dynamic_array() {
    int choice;
    do {
        display_dynamic_array_menu();
        cin >> choice;
        switch (choice) {
            case 1:
                create_new_dynamic_array();
                break;
            case 2:
                copy_dynamic_array();
                break;
            case 3:
                delete_dynamic_array();
                break;
            case 4:
                get_item_by_index();
                break;
            case 5:
                get_size_of_dynamic_array();
                break;
            case 6:
                set_element_at_index();
                break;
            case 7:
                resize_dynamic_array();
                break;
            case 8:
                print_dynamic_array();
                break;
            case 0:
                cout << "Exit\n" << endl;
                return;  // Return to main menu
            default:
                cout << "\n***********      Warning: Invalid choice      ***********\n" << endl;
                break;
        }
    } while (true);
}

void display_linked_list_menu() {
    cout << "---------------------------------------------------------" << endl;
    cout << "                        LinkedList                       " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Choose operation by sending number of operation          " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "1. Create new linked list" << endl;
    cout << "2. Copy linked list" << endl;
    cout << "3. Delete linked list" << endl;
    cout << "4. Get first item" << endl;
    cout << "5. Get last item" << endl;
    cout << "6. Append item" << endl;
    cout << "7. Prepend item" << endl;
    cout << "8. Concatenate lists" << endl;
    cout << "9. Get subsequence" << endl;
    cout << "10. Print linked list" << endl;
    cout << "0. Exit\n" << endl;
}

void create_new_linked_list() {
    linked_list = new LinkedList<int>();
    cout << "New linked list created." << endl;

    int size, value;
    cout << "Enter size of linked list: ";
    cin >> size;
    cout << "Enter " << size << " items:\n";
    for (int i = 0; i < size; i++) {
        cin >> value;
        linked_list->Append(value);
    }
    cout << "Linked list filled with items." << endl;
}

void copy_linked_list() {
    if (linked_list == nullptr) {
        cout << "No linked list to copy." << endl;
        return;
    }
    LinkedList<int> copied_list(*linked_list);
    cout << "Linked list copied." << endl;
    int size = copied_list.GetSize();
    cout << "Copied array contents: ";
    for (int i = 0; i < size; i++) {
        cout << copied_list.Get(i) << " ";
    }
    cout << "Copied array was shown and was deleted now ^>^";
}

void delete_linked_list() {
    delete linked_list;
    linked_list = nullptr;
    cout << "Linked list deleted." << endl;
}

void get_first_linked_list() {
    if (linked_list == nullptr) {
        cout << "No linked list exists." << endl;
        return;
    }
    try {
        int value = linked_list->GetFirst();
        cout << "First item: " << value << endl;
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }
}

void get_last_linked_list() {
    if (linked_list == nullptr) {
        cout << "No linked list exists." << endl;
        return;
    }
    try {
        int value = linked_list->GetLast();
        cout << "Last item: " << value << endl;
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }
}

void append_linked_list() {
    if (linked_list == nullptr) {
        cout << "No linked list exists." << endl;
        return;
    }
    int value;
    cout << "Enter value to append: ";
    cin >> value;
    linked_list->Append(value);
    cout << "Item appended." << endl;
}

void prepend_linked_list() {
    if (linked_list == nullptr) {
        cout << "No linked list exists." << endl;
        return;
    }
    int value;
    cout << "Enter value to prepend: ";
    cin >> value;
    linked_list->Prepend(value);
    cout << "Item prepended." << endl;
}

void concat_linked_list() {
    if (linked_list == nullptr) {
        cout << "No linked list exists to concatenate." << endl;
        return;
    }
    LinkedList<int>* other_list = new LinkedList<int>();
    int size, value;
    cout << "Enter size of the list to concatenate: ";
    cin >> size;
    cout << "Enter " << size << " items:\n";
    for (int i = 0; i < size; i++) {
        cin >> value;
        other_list->Append(value);
    }
    LinkedList<int>* concatenated_list = linked_list->Concat(other_list);
    int concatenated_size = concatenated_list->GetSize();
    cout << "Concatenated list content: ";
    for (int i = 0; i < concatenated_size; i++) {
        cout << concatenated_list->Get(i) << " ";
    }
    cout << endl;
    cout << "Concatenated list was shown and now deleted" << endl;
    delete concatenated_list;
    delete other_list;
}

void get_subsequence_linked_list() {
    if (linked_list == nullptr) {
        cout << "No linked list exists." << endl;
        return;
    }
    int start, end;
    cout << "Enter start index: ";
    cin >> start;
    cout << "Enter end index: ";
    cin >> end;
    try {
        LinkedList<int>* subsequence = linked_list->GetSubList(start, end);
        cout << "Subsequence: ";
        for (int i = 0; i < subsequence->GetSize(); i++) {
            cout << subsequence->Get(i) << " ";
        }
        cout << endl;
        delete subsequence;
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }
}

void print_linked_list() {
    if (linked_list == nullptr) {
        cout << "No linked list exists." << endl;
        return;
    }
    cout << "Linked list contents: ";
    for (int i = 0; i < linked_list->GetSize(); i++) {
        cout << linked_list->Get(i) << " ";
    }
    cout << endl;
}

void run_linked_list() {
    int choice;
    do {
        display_linked_list_menu();
        cin >> choice;
        switch (choice) {
            case 1:
                create_new_linked_list();
                break;
            case 2:
                copy_linked_list();
                break;
            case 3:
                delete_linked_list();
                break;
            case 4:
                get_first_linked_list();
                break;
            case 5:
                get_last_linked_list();
                break;
            case 6:
                append_linked_list();
                break;
            case 7:
                prepend_linked_list();
                break;
            case 8:
                concat_linked_list();
                break;
            case 9:
                get_subsequence_linked_list();
                break;
            case 10:
                print_linked_list();
                break;
            case 0:
                cout << "Exit\n" << endl;
                return;  // Return to main menu
            default:
                cout << "\n***********      Warning: Invalid choice      ***********\n" << endl;
                break;
        }
    } while (true);
}

void display_array_sequence_menu() {
    cout << "---------------------------------------------------------" << endl;
    cout << "                      ArraySequence                      " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Choose operation by sending number of operation          " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "1. Create new sequence" << endl;
    cout << "2. Copy sequence" << endl;
    cout << "3. Delete sequence" << endl;
    cout << "4. Get first item" << endl;
    cout << "5. Get last item" << endl;
    cout << "6. Append item" << endl;
    cout << "7. Prepend item" << endl;
    cout << "8. Get subsequence" << endl;
    cout << "9. Print sequence" << endl;
    cout << "0. Exit\n" << endl;
}

void create_new_array_sequence() {
    int choice;
    cout << "Choose initialization method:\n1. Initialize by value\n2. Initialize by list of items\n";
    cin >> choice;
    if (choice == 1) {
        int size, fill_value;
        cout << "Enter size of sequence: ";
        cin >> size;
        cout << "Enter fill value: ";
        cin >> fill_value;
        array_sequence = new ArraySequence<int>(size, &fill_value);
        cout << "New array sequence created." << endl;
    } else if (choice == 2) {
        int size;
        cout << "Enter size of sequence: ";
        cin >> size;
        int* items = new int[size];
        cout << "Enter " << size << " items:\n";
        for (int i = 0; i < size; i++) {
            cin >> items[i];
        }
        array_sequence = new ArraySequence<int>(size, items);
        delete[] items;
        cout << "New array sequence created." << endl;
    } else {
        cout << "Invalid choice." << endl;
    }
}

void copy_array_sequence() {
    if (array_sequence == nullptr) {
        cout << "No sequence to copy." << endl;
        return;
    }
    ArraySequence<int> copied_array_sequence(*array_sequence);
    cout << "Sequence copied." << endl;
    int size = copied_array_sequence.GetSize();
    cout << "Copied sequence contents: ";
    for (int i = 0; i < size; i++) {
        cout << copied_array_sequence.Get(i) << " ";
    }
    cout << "Copied sequence was shown and was deleted now ^>^";
}

void delete_array_sequence() {
    delete array_sequence;
    array_sequence = nullptr;
    cout << "Sequence deleted." << endl;
}

void get_first_array_sequence() {
    if (array_sequence == nullptr) {
        cout << "No sequence exists." << endl;
        return;
    }
    try {
        int value = array_sequence->GetFirst();
        cout << "First item: " << value << endl;
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }
}

void get_last_array_sequence() {
    if (array_sequence == nullptr) {
        cout << "No sequence exists." << endl;
        return;
    }
    try {
        int value = array_sequence->GetLast();
        cout << "Last item: " << value << endl;
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }
}

void append_array_sequence() {
    if (array_sequence == nullptr) {
        cout << "No sequence exists." << endl;
        return;
    }
    int value;
    cout << "Enter value to append: ";
    cin >> value;
    array_sequence->Append(value);
    cout << "Item appended." << endl;
}

void prepend_array_sequence() {
    if (array_sequence == nullptr) {
        cout << "No sequence exists." << endl;
        return;
    }
    int value;
    cout << "Enter value to prepend: ";
    cin >> value;
    array_sequence->Prepend(value);
    cout << "Item prepended." << endl;
}

void get_subsequence_array_sequence() {
    if (array_sequence == nullptr) {
        cout << "No sequence exists." << endl;
        return;
    }
    int start, end;
    cout << "Enter start index: ";
    cin >> start;
    cout << "Enter end index: ";
    cin >> end;
    try {
        ArraySequence<int>* subsequence = array_sequence->GetSubsequence(start, end);
        cout << "Subsequence: ";
        for (int i = 0; i < subsequence->GetSize(); i++) {
            cout << subsequence->Get(i) << " ";
        }
        cout << endl;
        delete subsequence;
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }
}

void print_array_sequence() {
    if (array_sequence == nullptr) {
        cout << "No sequence exists." << endl;
        return;
    }
    cout << "Sequence contents: ";
    for (int i = 0; i < array_sequence->GetSize(); i++) {
        cout << array_sequence->Get(i) << " ";
    }
    cout << endl;
}

void run_array_sequence() {
    int choice;
    do {
        display_array_sequence_menu();
        cin >> choice;
        switch (choice) {
            case 1:
                create_new_array_sequence();
                break;
            case 2:
                copy_array_sequence();
                break;
            case 3:
                delete_array_sequence();
                break;
            case 4:
                get_first_array_sequence();
                break;
            case 5:
                get_last_array_sequence();
                break;
            case 6:
                append_array_sequence();
                break;
            case 7:
                prepend_array_sequence();
                break;
            case 8:
                get_subsequence_array_sequence();
                break;
            case 9:
                print_array_sequence();
                break;
            case 0:
                cout << "Exit\n" << endl;
                return;  // Return to main menu
            default:
                cout << "\n***********      Warning: Invalid choice      ***********\n" << endl;
                break;
        }
    } while (true);
}

void display_list_sequence_menu() {
    cout << "---------------------------------------------------------" << endl;
    cout << "                      ListSequence                       " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Choose operation by sending number of operation          " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "1. Create new sequence" << endl;
    cout << "2. Copy sequence" << endl;
    cout << "3. Delete sequence" << endl;
    cout << "4. Get first item" << endl;
    cout << "5. Get last item" << endl;
    cout << "6. Append item" << endl;
    cout << "7. Prepend item" << endl;
    cout << "8. Get subsequence" << endl;
    cout << "9. Print sequence" << endl;
    cout << "0. Exit\n" << endl;
}

void create_new_list_sequence() {
    list_sequence = new ListSequence<int>();
    cout << "New list sequence created." << endl;

    int size, value;
    cout << "Enter size of list sequence: ";
    cin >> size;
    cout << "Enter " << size << " items:\n";
    for (int i = 0; i < size; i++) {
        cin >> value;
        list_sequence->Append(value);
    }
    cout << "List sequence filled with items." << endl;
}

void copy_list_sequence() {
    if (list_sequence == nullptr) {
        cout << "No sequence to copy." << endl;
        return;
    }
    ListSequence<int> copied_list_sequence(*list_sequence);
    cout << "Sequence copied." << endl;
    int size = copied_list_sequence.GetSize();
    cout << "Copied sequence contents: ";
    for (int i = 0; i < size; i++) {
        cout << copied_list_sequence.Get(i) << " ";
    }
    cout << "Copied sequence was shown and was deleted now ^>^";
}

void delete_list_sequence() {
    delete list_sequence;
    list_sequence = nullptr;
    cout << "Sequence deleted." << endl;
}

void get_first_list_sequence() {
    if (list_sequence == nullptr) {
        cout << "No sequence exists." << endl;
        return;
    }
    try {
        int value = list_sequence->GetFirst();
        cout << "First item: " << value << endl;
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }
}

void get_last_list_sequence() {
    if (list_sequence == nullptr) {
        cout << "No sequence exists." << endl;
        return;
    }
    try {
        int value = list_sequence->GetLast();
        cout << "Last item: " << value << endl;
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }
}

void append_list_sequence() {
    if (list_sequence == nullptr) {
        cout << "No sequence exists." << endl;
        return;
    }
    int value;
    cout << "Enter value to append: ";
    cin >> value;
    list_sequence->Append(value);
    cout << "Item appended." << endl;
}

void prepend_list_sequence() {
    if (list_sequence == nullptr) {
        cout << "No sequence exists." << endl;
        return;
    }
    int value;
    cout << "Enter value to prepend: ";
    cin >> value;
    list_sequence->Prepend(value);
    cout << "Item prepended." << endl;
}

void get_subsequence_list_sequence() {
    if (list_sequence == nullptr) {
        cout << "No sequence exists." << endl;
        return;
    }
    int start, end;
    cout << "Enter start index: ";
    cin >> start;
    cout << "Enter end index: ";
    cin >> end;
    try {
        ListSequence<int>* subsequence = list_sequence->GetSubsequence(start, end);
        cout << "Subsequence: ";
        for (int i = 0; i < subsequence->GetSize(); i++) {
            cout << subsequence->Get(i) << " ";
        }
        cout << endl;
        delete subsequence;
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }
}

void print_list_sequence() {
    if (list_sequence == nullptr) {
        cout << "No sequence exists." << endl;
        return;
    }
    cout << "Sequence contents: ";
    for (int i = 0; i < list_sequence->GetSize(); i++) {
        cout << list_sequence->Get(i) << " ";
    }
    cout << endl;
}

void run_list_sequence() {
    int choice;
    do {
        display_list_sequence_menu();
        cin >> choice;
        switch (choice) {
            case 1:
                create_new_list_sequence();
                break;
            case 2:
                copy_list_sequence();
                break;
            case 3:
                delete_list_sequence();
                break;
            case 4:
                get_first_list_sequence();
                break;
            case 5:
                get_last_list_sequence();
                break;
            case 6:
                append_list_sequence();
                break;
            case 7:
                prepend_list_sequence();
                break;
            case 8:
                get_subsequence_list_sequence();
                break;
            case 9:
                print_list_sequence();
                break;
            case 0:
                cout << "Exit\n" << endl;
                return;  // Return to main menu
            default:
                cout << "\n***********      Warning: Invalid choice      ***********\n" << endl;
                break;
        }
    } while (true);
}

int main() {
    run_main_menu();
    return 0;
}
