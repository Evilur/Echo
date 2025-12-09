#pragma once

#include "linked_list.h"
#include "util/hash.h"

/**
 * Simple minimalistic implementation of hash map
 * @author Evilur <the.evilur@gmail.com>
 * @tparam K Key typename
 * @tparam T Element typename
 */
template <typename K, typename T>
class HashMap final {
struct Node;
public:
    /**
     * @param capacity Maximum number of elements without resizing
     */
    explicit HashMap(unsigned short capacity) noexcept;

    /**
     * Free the memory
     */
    ~HashMap() noexcept;

    /**
     * Delete the copy constructor
     */
    HashMap(const HashMap&) noexcept = delete;

    /**
     * Delete the copy operator
     */
    HashMap& operator=(const HashMap&) noexcept = delete;

    /**
     * Put an element into the hash map
     * @param key The key that can be used to retrieve the element
     * @param element Element to put into the map
     */
    void Put(K key, T element);

    /**
     * Get the element from the hash map by the key
     * @param key The key to get the element by
     * @return Element with the similar key; nullptr if there is no such element
     */
    T& Get(K key) const;

    /**
     * Iterator to go through the hash map
     */
    class Iterator {
    public:
        explicit Iterator(unsigned short index,
                          unsigned short capacity,
                          const LinkedList<Node>* lists,
                          LinkedList<Node>::Iterator iterator
                          ) noexcept;

        bool operator!=(const Iterator& other) const noexcept;

        const Node& operator*() const noexcept;

        Iterator& operator++() noexcept;

    private:
        /**
         * Index of the current bucket in the hash table
         */
        unsigned short _index;
        /**
         * Total number of buckets in the hash table
         */
        const unsigned short _capacity;
        /**
         * Pointer to the array of linked lists (buckets)
         * that make up the hash table
         */
        const LinkedList<Node>* const _buckets;
        /**
         * Iterator pointing to the current node
         * inside the current bucket's linked list
         */
        LinkedList<Node>::Iterator _iterator;
    };

    /**
     * Get the iterator for the first element
     * @return iterator for the first element
     */
    Iterator begin() const noexcept;

    /**
     * Get the iterator after the last element
     * @return iterator after the last element
     */
    Iterator end() const noexcept;

private:
    /**
     * Node to keep the element and its key in the linked list
     */
    struct Node {
        K key;
        T element;
    };

    /**
     * A pointer to the dynamic array with linked lists for resolving collisions
     */
    LinkedList<Node>* const _buckets;

    /**
     * A size of the array with linked lists
     */
    const unsigned short _capacity;

    /**
     * Compare two keys
     * @return true if the keys are equal, otherwise - false
     */
    static bool Equal(K key1, K key2) noexcept;
};

template <typename K, typename T>
HashMap<K, T>::HashMap(const unsigned short capacity) noexcept :
        _buckets(new LinkedList<Node>[capacity]), _capacity(capacity) { }

template <typename K, typename T>
HashMap<K, T>::~HashMap() noexcept { delete[] _buckets; }

template <typename K, typename T>
void HashMap<K, T>::Put(K key, T element) {
    /* Calculate the key hash */
    const unsigned short hash = Hash::Get(key) % _capacity;

    /* Try to get the node from the linked list */
    for (Node node : _buckets[hash])
        if (Equal(node.key, key))
            throw std::runtime_error(
                "HashMap: Put() an element with such a key already exists"
            );

    /* If there is no an element with such a key yet,
     * put the node to the one of the buckets, according to the hash */
    _buckets[hash].Push({ key, element });
}

template <typename K, typename T>
T& HashMap<K, T>::Get(K key) const {
    /* Calculate the key hash */
    const unsigned short hash = Hash::Get(key) % _capacity;

    /* Try to get the node from the linked list */
    for (Node node : _buckets[hash])
        if (Equal(node.key, key))
            return node.element;

    /* If there is NOT an element in the linked list, throw an error */
    throw std::runtime_error("HashMap::Get() no such an element");
}

template <typename K, typename T>
HashMap<K, T>::Iterator HashMap<K, T>::begin() const noexcept {
    /* Iterate over all buckets */
    for (unsigned short i = 0; i < _capacity; ++i)
        /* If the current bucket is not empty,
         * return iterator to its first element */
        if (_buckets[i].begin() != _buckets[i].end())
            return Iterator(i, _capacity, _buckets, _buckets[i].begin());

    /* If all buckets are empty, return end() iterator */
    return end();
}

template <typename K, typename T>
HashMap<K, T>::Iterator HashMap<K, T>::end() const noexcept {
    /* Construct an iterator representing the end position:
     * index == capacity and internal list iterator == nullptr */
    return Iterator(_capacity, _capacity, _buckets,
                    typename LinkedList<Node>::Iterator(nullptr));
}

template <typename K, typename T>
bool HashMap<K, T>::Equal(K key1, K key2) noexcept {
    if constexpr (std::is_same_v<K, const char*>)
        return strcmp(key1, key2) == 0;
    else
        return key1 == key2;
}

template <typename K, typename T>
HashMap<K, T>::Iterator::Iterator(
    const unsigned short index,
    const unsigned short capacity,
    const LinkedList<Node>* const lists,
    const typename LinkedList<Node>::Iterator iterator
) noexcept : _index(index), _capacity(capacity),
             _buckets(lists), _iterator(iterator) { }

template <typename K, typename T>
bool HashMap<K, T>::Iterator::operator!=(const Iterator& other) const noexcept {
    /* If both iterators are "end" iterators, they are equal */
    if (_index == _capacity && other._index == other._capacity) return false;

    /* If they point to different buckets, they are not equal */
    if (_index != other._index) return true;

    /* Otherwise compare underlying list iterators */
    return _iterator != other._iterator;
}

template <typename K, typename T>
const HashMap<K, T>::Node& HashMap<K, T>::Iterator::operator*() const noexcept {
    return *_iterator;
}

template <typename K, typename T>
HashMap<K, T>::Iterator& HashMap<K, T>::Iterator::operator++() noexcept {
    /* If iterator is already at end(), do nothing */
    if (_index == _capacity) return *this;

    /* If still inside a non-empty bucket, stop here */
    if (++_iterator != _buckets[_index].end()) return *this;

    /* Skip empty buckets until a non-empty one is found */
    while (++_index < _capacity) {
        if (_buckets[_index].begin() != _buckets[_index].end()) {
            _iterator = _buckets[_index].begin();
            return *this;
        }
    }

    /* If no more buckets contain elements, set iterator to end() */
    _index = _capacity;
    _iterator = typename LinkedList<Node>::Iterator(nullptr);
    return *this;
}