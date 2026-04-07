#include "array_bag.hpp"
#include "searchable_bag.hpp"

class searchable_array_bag : public array_bag, public searchable_bag
{
    public:
        searchable_array_bag();
        searchable_array_bag(const searchable_array_bag &copy);
        searchable_array_bag &operator=(const searchable_array_bag &other);
        virtual ~searchable_array_bag();

        virtual bool has(int x) const;
};


searchable_array_bag::searchable_array_bag() : array_bag() {};

searchable_array_bag::searchable_array_bag(const searchable_array_bag &copy) : array_bag(copy) {};

searchable_array_bag &searchable_array_bag::operator=(const searchable_array_bag &other)
{
    if (this != &other)
        array_bag::operator=(other);
    return *this;
}

searchable_array_bag::~searchable_array_bag(){};

bool searchable_array_bag::has(int x) const
{
    if (this->size_ <= 0)
        return false;
    int i = 0;
    while(i < this->size_)
    {
        if (this->data_[i] == x)
            return true;
        i++;
    }
    return false;
}
