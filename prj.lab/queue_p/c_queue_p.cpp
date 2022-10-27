#include <queue_p/c_queue_p.h>
#include <queue_p/queue_p.hpp>
#include <stdexcept>
#include <map>

class Manager {
public:
    Manager(const Manager&) = delete;
    Manager(Manager&&) = delete;
    Manager& operator=(const Manager&) = delete;
    Manager& operator=(Manager&&) = delete;

    static Manager& getInstance() {
        static Manager manager{};

        return manager;
    }

    QueueHandler createQueue() noexcept {
        last_handle_id++;
        QueueHandler handler = last_handle_id;
        handles[handler] = QueueP();
        return handler;
    }

    QueueHandler cloneQueue(QueueHandler source) {
        if (handles.count(source) == 0)
            throw std::invalid_argument("bad handle");
        QueueHandler handler = createQueue();
        handles[handler] = handles[source];
        return handler;
    }

    bool destroyQueue(QueueHandler q) noexcept {
        return handles.erase(q) != 0;
    }

    void pop(QueueHandler q) {
        if (handles.count(q) == 0)
            throw std::invalid_argument("bad handle");
        handles[q].pop();
    }

    void push(QueueHandler q, int32_t value) {
        if (handles.count(q) == 0)
            throw std::invalid_argument("bad handle");
        handles[q].push(value);
    }

    bool isEmpty(QueueHandler q) {
        if (handles.count(q) == 0)
            throw std::invalid_argument("bad handle");
        return handles[q].isEmpty();
    }

    int32_t top(QueueHandler q) {
        if (handles.count(q) == 0)
            throw std::invalid_argument("bad handle");
        return handles[q].top();
    }

private:
    Manager() = default;
    ~Manager() = default;

    std::map<QueueHandler, QueueP> handles;
    QueueHandler last_handle_id{0};
};

ErrorCode CreateQueue(QueueHandler* queue) {
    if (*queue != EMPTY_QUEUE_HANDLER) {
        return kHandlerError;
    }
    *queue = Manager::getInstance().createQueue();
    return kGood;
}

ErrorCode CloneQueue(QueueHandler source, QueueHandler* queue) {
    if (*queue != EMPTY_QUEUE_HANDLER) {
        return kHandlerError;
    }
    try {
        *queue = Manager::getInstance().cloneQueue(source);
    } catch (const std::invalid_argument& err) {
        return kHandlerError;
    }
    return kGood;
}

ErrorCode DestroyQueue(QueueHandler* queue) {
    if (*queue == EMPTY_QUEUE_HANDLER) {
        return kGood; // or kHandlerError
    }
    if (!Manager::getInstance().destroyQueue(*queue)) {
        return kHandlerError;
    }
    *queue = EMPTY_QUEUE_HANDLER;
    return kGood;
}

ErrorCode Pop(QueueHandler queue) {
    if (queue == EMPTY_QUEUE_HANDLER) {
        return kHandlerError;
    }
    try {
        Manager::getInstance().pop(queue);
    } catch (const std::invalid_argument& err) {
        return kHandlerError;
    }
    return kGood;
}

ErrorCode Push(QueueHandler queue, int32_t value) {
    if (queue == EMPTY_QUEUE_HANDLER) {
        return kHandlerError;
    }
    try {
        Manager::getInstance().push(queue, value);
    } catch (const std::invalid_argument& err) {
        return kHandlerError;
    }
    return kGood;
}

ErrorCode IsEmpty(QueueHandler queue, int32_t* result) {
    if (queue == EMPTY_QUEUE_HANDLER) {
        return kHandlerError;
    }
    try {
        *result = Manager::getInstance().isEmpty(queue);
    } catch (const std::invalid_argument& err) {
        return kHandlerError;
    }
    return kGood;
}

ErrorCode Top(QueueHandler queue, int32_t* result) {
    if (queue == EMPTY_QUEUE_HANDLER) {
        return kHandlerError;
    }
    try {
        *result = Manager::getInstance().top(queue);
    } catch(const std::invalid_argument& err) { 
        return kHandlerError;
    } catch(const std::out_of_range& err) {
        return kOutOfRange;
    }
    return kGood;
}

const char* WhatIs(ErrorCode err) {
    switch (err) {
        case kGood:
            return "";
        case kHandlerError:
            return "invalid QueueHandler";
        case kOutOfRange:
            return "out of range error";
        default:
            return "uknown error";
    }
}