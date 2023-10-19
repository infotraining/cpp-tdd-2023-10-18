#ifndef RUL_HPP
#define RUL_HPP

#include <algorithm>
#include <deque>
#include <stdexcept>
#include <string>
#include <limits>

class RecentlyUsedList
{
public:
    using iterator = typename std::deque<std::string>::iterator;
    using const_iterator = typename std::deque<std::string>::const_iterator;

    explicit RecentlyUsedList(size_t capacity = std::numeric_limits<size_t>::max())
        : capacity_{capacity}
    {
    }

    size_t capacity() const
    {
        return capacity_;
    }

    size_t size() const
    {
        return items_.size();
    }

    bool empty() const
    {
        return items_.empty();
    }

    void add(const std::string& item)
    {
        check_is_valid(item);

        auto duplicate_pos = std::find(items_.begin(), items_.end(), item);

        if (duplicate_pos != items_.end())
            move_duplicate_to_front(duplicate_pos);
        else
        {
            if (capacity_ == size())
                items_.pop_back();
            items_.push_front(item);
        }
    }

    const std::string& front() const
    {
        return items_.front();
    }

    const std::string& back() const
    {
        return items_.back();
    }

    const std::string& operator[](size_t index) const
    {
        return items_[index];
    }

    const_iterator begin() const
    {
        return items_.begin();
    }

    const_iterator end() const
    {
        return items_.end();
    }

private:
    std::deque<std::string> items_;
    size_t capacity_;

    void move_duplicate_to_front(iterator duplicate_pos)
    {
        std::rotate(items_.begin(), duplicate_pos, duplicate_pos + 1);
    }

    void check_is_valid(const std::string& item)
    {
        if (item == "")
            throw std::invalid_argument("empty string is not allowed");
    }
};

#endif