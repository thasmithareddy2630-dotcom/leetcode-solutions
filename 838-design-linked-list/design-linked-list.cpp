
class MyLinkedList {
private:
    struct Node {
        int val;
        Node* next;

        Node(int value) {
            val = value;
            next = nullptr;
        }
    };

    Node* head;
    int length;

public:
    MyLinkedList() {
        head = nullptr;
        length = 0;
    }

    int get(int index) {
        if (index < 0 || index >= length)
            return -1;

        Node* temp = head;

        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }

        return temp->val;
    }

    void addAtHead(int val) {
        Node* x = new Node(val);
        x->next = head;
        head = x;
        length++;
    }

    void addAtTail(int val) {
        Node* x = new Node(val);

        if (head == nullptr) {
            head = x;
        } else {
            Node* temp = head;

            while (temp->next != nullptr) {
                temp = temp->next;
            }

            temp->next = x;
        }

        length++;
    }

    void addAtIndex(int index, int val) {
        if (index < 0)
            index = 0;

        if (index > length)
            return;

        if (index == 0) {
            addAtHead(val);
            return;
        }

        Node* temp = head;

        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }

        Node* x = new Node(val);
        x->next = temp->next;
        temp->next = x;
        length++;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index >= length)
            return;

        if (index == 0) {
            Node* x = head;
            head = head->next;
            delete x;
            length--;
            return;
        }

        Node* temp = head;

        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }

        Node* x = temp->next;
        temp->next = x->next;
        delete x;
        length--;
    }
};
