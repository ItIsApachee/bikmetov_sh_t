#include <memory>

#ifndef PRIORITY_QUEUE_H_2022_09_28
#define PRIORITY_QUEUE_H_2022_09_28

class QueueP {
private:
    class QueueR {
    public:
        QueueR(int value, std::unique_ptr<QueueR> next = nullptr): value{value}, next(move(next)) {}
        QueueR(const QueueR&) = delete;
        QueueR(QueueR&&) = default;
        QueueR& operator=(const QueueR&) = delete;
        QueueR& operator=(QueueR&&) = default;

        ~QueueR() = default;

        int value{0};
        std::unique_ptr<QueueR> next{nullptr};
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
    bool empty();

    ~QueueP() = default;

private:
    std::unique_ptr<QueueR> head{nullptr};
};

#endif