#include <memory>

#ifndef PRIORITY_QUEUE_RAW_H_2022_09_28
#define PRIORITY_QUEUE_RAW_H_2022_09_28

class QueueR {
private:
    class Node {
    public:
        Node(int value, Node* next = nullptr): value{value}, next(next) {}
        Node(const Node&) = delete;
        Node(Node&&) = default;
        Node& operator=(const Node&) = delete;
        Node& operator=(Node&&) = default;

        // can't delete next in desctuctor since it implies
        // you can't delete Node in the middle of queue
        ~Node() = default;

        int value{0};
        Node* next;
    };

public:
    QueueR() = default;
    QueueR(const QueueR&) = delete; // no requirements to implement this
    QueueR(QueueR&&) = default;
    QueueR& operator=(const QueueR&) = delete; // no requirement to implement this
    QueueR& operator=(QueueR&&) = default;

    void push(int);
    // returns smallest element if !this.empty() or throws exception otherwise
    int pop();
    bool empty();

    ~QueueR();

private:
    Node* head{nullptr};
};

#endif