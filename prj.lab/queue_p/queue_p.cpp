#include <queue_p/queue_p.h>
#include <memory>
#include <stdexcept>
#include <utility>

QueueP::QueueP(const QueueP& other) {
    if (other.isEmpty())
        return;
    head = std::make_unique<Node>(other.head->value);

    Node* other_ptr = other.head.get();
    Node* ptr = head.get();
    while (other_ptr->next) {
        ptr->next = std::make_unique<Node>(other_ptr->next->value);

        ptr = ptr->next.get();
        other_ptr = other_ptr->next.get();
    }
}

QueueP& QueueP::operator=(const QueueP& other) {
    if (&other == this)
        return *this;
    
    return *this = std::move(QueueP(other));
}

void QueueP::push(int value) {
    if (isEmpty()) {
        head = std::unique_ptr<Node>(new Node(value));
        return;
    }

    if (head->value > value) {
        std::unique_ptr<Node> node = std::make_unique<Node>(value, move(head));
        head = move(node);
        return;
    }

    Node* current = head.get();
    while (current->next && current->next->value <= value) {
        current = current->next.get();
    }

    // either (*current)->next is nullptr, or (*current)->next->value > value
    std::unique_ptr<Node> node = std::make_unique<Node>(value, move(current->next));
    current->next = move(node);
}

int QueueP::pop() {
    if (isEmpty()) {
        throw std::out_of_range("can't pop from an empty queue");
    }
    int result = head->value;

    std::unique_ptr<Node> old_head(move(head));
    head = move(old_head->next);

    return result;
}

bool QueueP::isEmpty() const {
    // if head is nullptr, then true
    // else false
    return !head;
}