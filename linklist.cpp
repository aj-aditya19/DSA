#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;

    Node(int val)
    {
        data = val;
        next = NULL;
    }
};

int main()
{
    Node *head = NULL;
    Node *tail = NULL;

    cout << "Enter values for linked list (-1 to stop):" << endl;

    while (true)
    {
        int x;
        cin >> x;

        if (x == -1)
        {
            break;
        }

        Node *newNode = new Node(x);

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    cout << "Linked List: ";
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;

    return 0;
}
