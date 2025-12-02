#pragma once

#include <array>

template <typename T> class Queue
{
  public:
    Queue() : data_{}, top_(data_.begin()) {}

    void push(T val)
    {
        if (top_ < data_.end())
        {
            *(top_) = val;
            top_++;
            std::cout << "pushed " << val << std::endl;
        }
        else
        {
            std::cout << "[error] stack full" << std::endl;
        }
    }

    T peek() const
    {
        T val = (top_ == data_.begin()) ? (0) : (*(top_ - 1));
        std::cout << "peeked " << val << std::endl;
        return val;
    }

    T pop()
    {
        if (top_ > data_.begin())
        {
            T val = *(top_ - 1);
            top_--;
            std::cout << "popped " << val << std::endl;
            return val;
        }
        else
        {
            std::cout << "[error] stack empty" << std::endl;
            return 0;
        }
    }

  private:
    std::array<T, 3> data_;
    typename std::array<T, 3>::iterator top_;
};