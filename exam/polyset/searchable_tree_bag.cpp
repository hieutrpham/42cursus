#include "tree_bag.hpp"
#include "searchable_bag.hpp"

class searchable_tree_bag : public tree_bag, public searchable_bag
{
    public:
        searchable_tree_bag();
        searchable_tree_bag(const searchable_tree_bag &copy);
        searchable_tree_bag &operator=(const searchable_tree_bag &other);
        virtual ~searchable_tree_bag();

        virtual bool has(int x) const;

};

searchable_tree_bag::searchable_tree_bag() : tree_bag(){};

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &copy) : tree_bag(copy){};
searchable_tree_bag &searchable_tree_bag::operator=(const searchable_tree_bag &other) {
    if (this != &other)
        tree_bag::operator=(other);
    return *this;
}

searchable_tree_bag::~searchable_tree_bag(){};

bool searchable_tree_bag::has(int x) const
{
	const node *cur = this->tree_;

	while (cur != 0)
	{
		if (x == cur->value)
			return true;

		if (x < cur->value)
			cur = cur->l;
		else
			cur = cur->r;
	}
	return false;
}
