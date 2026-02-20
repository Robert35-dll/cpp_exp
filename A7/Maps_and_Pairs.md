# Maps and Pairs

Here are some basic notes about using pairs, maps and multimaps.

## Pairs

Pairs are rather simple structs which can store values of any data type (*even pairs themselves*):
For nested pairs it's helpful to use `#define` statements to simplify long definitions:

```c++
#include <iostream>
#include <string>

using namespace std;

// Simple example

// Defining a new name for points' pairs
#define Point pair<int, int>

// Creating some pairs
Point p1(1, 1);
Point p2 = make_pair(2, 2);
pair<string, Point> namedPoint;

// Copying a pair
Point p3(p2);

// Accessing pair's values
namedPoint.first  = "A1";
namedPoint.second = p;

// A bit more complicated example :3
#define Coordinates pair<float, float>
#define District    pair<int, string>
#define Address     pair<string, string>
#define FullAddress pair<Address, Disctrict>
#define Location    pair<FullAddress, Coordinates>
```

## Maps

If you try to combine multiple pairs into a unite structure, you probably come to an implementation of a map.
Maps are data structures that store key-value pairs (*aka assosiative containers*) that have following properties:

- All keys are unique
- All keys are sorted by the comparison function (*either implicit by direct key comparison or explicit by map declaration*)
- Different keys may have same values

```c++
#include <map>

using namespace std;

// Creating a map
map<int, string> customers();

// Adding entries to the map
customers.insert({1, "Kazuma"});
customers.insert(make_pair(2, "Megumin"));

// Values with already included key won't be added
customers.insert({2, "Aqua"});

// Iterating over a map
for (auto i = customers.begin(); i != customers.end(); i++)
{
    // Some logic ...
}

// or looking at specific key with O(log n)
customers.find(2);  // -> iterator to "Megumin"
customers.find(12); // -> iterator past the last element

// Alternatively you can also access values like in arrays
customers.at(1);    // -> reference to "Kazuma"
customers[2];       // -> reference to "Megumin"
customers[0];       // -> out_of_range exception
```

See full list of available functions on [this cppreference](https://en.cppreference.com/w/cpp/container/map.html).

## Multimaps

A multimap is another implementation of a pair-based data structure.
Compared to a normal map this has couple of differences:

- Same key may be present multiple times
- Accessing value by its key may return any of the values with that key

```c++
#include <multimap>
#include <string>

using namespace std;

// Creating a multimap
multimap<int, string> multiCustomers();

// Adding entries to the multimap
multiCustomers.insert({1, "Kazuma"});
multiCustomers.insert({2, "Megumin"});
multiCustomers.insert({2, "Aqua"});
multiCustomers.insert({3, "Darkness"});

// Accessing multiple values with the same key

// Getting an iterator to the value of the first key's occurrence
auto firstSelectedCustomer = multiCustomers.lower_bound(2);
// Getting an iterator to the value past the last key's occurrence
auto lastSelectedCustomer = multiCustomers.upper_bound(2);
// Getting a pair of both iterators above
auto selectedCustomers = multiCustomers.equal_range(2);

// Iterating over unique keys
auto i = multiCustomers->begin();
while (i != multiCustomers->cend())
{
    // Some logic ...

    // Skipping all vehicles of a driver
    i = multiCustomers->upper_bound(i->first);
}
```

See full list of available functions on [this cppreference](https://en.cppreference.com/w/cpp/container/multimap.html).
