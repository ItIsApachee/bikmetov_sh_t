#include <memory>

#ifndef PRIORITY_QUEUE_H_2022_09_28
#define PRIORITY_QUEUE_H_2022_09_28

class QueueP {
private:
    class Node {
    public:
        Node(int value, std::unique_ptr<Node> next = nullptr): value{value}, next(move(next)) {}
        Node(const Node&) = delete;
        Node(Node&&) = default;
        Node& operator=(const Node&) = delete;
        Node& operator=(Node&&) = default;

        ~Node() = default;

        int value{0};
        std::unique_ptr<Node> next{nullptr};
    };

public:
    QueueP() = default;
    QueueP(const QueueP&);
    QueueP(QueueP&&) = default;
    QueueP& operator=(const QueueP&);
    QueueP& operator=(QueueP&&) = default;

    void push(int);
    // returns smallest element if !this.empty() or throws exception otherwise
    int pop();
    bool isEmpty() const;

    ~QueueP() = default;

private:
    std::unique_ptr<Node> head{nullptr};
};

#endif