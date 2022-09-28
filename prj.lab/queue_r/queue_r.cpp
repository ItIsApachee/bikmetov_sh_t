#include <queue_r/queue_r.h>

void QueueR::push(int value) {
    if (empty()) {
        head = new Node(value);
        return;
    }

    if (head->value > value) {
        Node* head_new = new Node(value, head);
        head = head_new;
        return;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->value <= value) {
        current = current->next;
    }

    Node* node = new Node(value, current->next);
    current->next = node;
}

int QueueR::pop() {
    if (empty()) {
        throw std::out_of_range("can't pop from an empty queue");
    }
    int result = head->value;

    Node* old_head = head;
    head = old_head->next;
    delete old_head;

    return result;
}

bool QueueR::empty() {
    return head == nullptr;
}


QueueR::~QueueR() {
    Node* current = head;
    while (current != nullptr) {
        Node* next_current = current->next;
        delete current;
        current = next_current;
    }
}