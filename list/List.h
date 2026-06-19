#pragma once

#include <string>

class List {
    struct Node {
        std::wstring data;
        Node *next = nullptr;
    };

    int size_{};
    Node *tail_{};
    Node *head_{};

public:
    void push(const std::wstring &data);

    std::wstring top() const;

    std::wstring back() const;

    void pop();

    List() = default;

    List(const List &other) {
        copy(other);
    }

    List &operator=(const List &other) {
        if (this == &other) return *this;
        while (!is_empty()) pop();
        copy(other);
        return *this;
    }

    ~List() {
        while (!is_empty()) {
            pop();
        }
    }

    int size() const;

    bool is_empty() const;

    class Iterator {
        Node *node;

    public:
        explicit Iterator(Node *n) : node(n) {
        }

        std::wstring &operator*() const {
            return node->data;
        }

        Iterator &operator++() {
            node = node->next;
            return *this;
        }

        bool operator!=(const Iterator &other) const {
            return node != other.node;
        }
    };

    Iterator begin() const {
        return Iterator(tail_);
    }

    static Iterator end() {
        return Iterator(nullptr);
    }

private:
    void copy(const List &other);
};
