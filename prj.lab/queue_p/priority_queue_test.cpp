#include <iostream>
#include <stdexcept>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>

#include <queue_p/priority_queue.h>

namespace Util {
    using It = std::vector<int>::const_iterator;
    constexpr char SEPARATOR = ' ';
    std::ostream& display(std::ostream& ostrm, It begin_, It end_) {
        for (It i = begin_; i != end_; i++) {
            ostrm << *i << SEPARATOR;
        }
        return ostrm;
    }
}

int main(int argc, char* argv[]) {
    std::mt19937 rng(1337); // rng to shuffle

    int test_size = 10;
    if (argc > 1) {
        test_size = std::atoi(argv[1]);
    }
    std::vector<int> arr(test_size);
    std::iota(arr.begin(), arr.end(), 0);
    std::shuffle(arr.begin(), arr.end(), rng);

    std::cout << "array: ";
    Util::display(std::cout, arr.begin(), arr.end());
    std::cout << std::endl;

    QueueP queue;
    for (auto v: arr)
        queue.push(v);
    arr.resize(0);
    while (!queue.empty())
        arr.push_back(queue.pop());
    
    std::cout << "sorted array: ";
    Util::display(std::cout, arr.begin(), arr.end());
    std::cout << std::endl;

    if (!std::is_sorted(arr.begin(), arr.end())) {
        std::cout << "insertion sort failed" << std::endl;
    }
    std::cout << "test OK" << std::endl;
}