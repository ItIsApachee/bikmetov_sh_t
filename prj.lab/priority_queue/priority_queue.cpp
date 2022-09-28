#include <priority_queue/priority_queue.h>
#include <memory>
#include <stdexcept>

QueueP::QueueP(const QueueP&) {
    throw;
}

QueueP& QueueP::operator=(const QueueP&) {
    throw;
}

void QueueP::push(int value) {
    if (empty()) {
        head = std::unique_ptr<QueueR>(new QueueR(value));
        return;
    }

    if (head->value > value) {
        std::unique_ptr<QueueR> node = std::make_unique<QueueR>(value, move(head));
        head = move(node);
        return;
    }

    std::unique_ptr<QueueR>* current = &head;
    while ((*current)->next && (*current)->next->value <= value) {
        current = &(*current)->next;
    }

    // either (*current)->next is nullptr, or (*current)->next->value > value
    std::unique_ptr<QueueR> node = std::make_unique<QueueR>(value, move((*current)->next));
    (*current)->next = move(node);
}

int QueueP::pop() {
    if (empty()) {
        throw std::out_of_range("can't pop from an empty queue");
    }
    int result = head->value;

    std::unique_ptr<QueueR> old_head(move(head));
    head = move(old_head->next);

    return result;
}

bool QueueP::empty() {
    // if head is nullptr, then true
    // else false
    return !head;
}