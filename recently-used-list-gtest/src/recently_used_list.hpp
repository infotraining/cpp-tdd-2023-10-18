#ifndef RCL_HPP
#define RCL_HPP

#include <deque>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <limits>

class RecentlyUsedList
{
	std::deque<std::string> items_;
	size_t capacity_ = std::numeric_limits<size_t>::max();

public:
	using value_type = std::string;
	using const_iterator = std::deque<std::string>::const_iterator;
	using iterator = std::deque<std::string>::iterator;

	RecentlyUsedList() = default;

	RecentlyUsedList(size_t capacity)
		: capacity_{ capacity }
	{
	}

	bool empty() const
	{
		return items_.empty();
	}

	size_t size() const
	{
		return items_.size();
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

	const std::string& operator[](size_t index) const
	{
		return items_[index];
	}

	void clear()
	{
		items_.clear();
	}

	const_iterator begin() const
	{
		return items_.begin();
	}

	const_iterator end() const
	{
		return items_.end();
	}

	size_t capacity() const
	{
		return capacity_;
	}

private:
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

