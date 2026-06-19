#include "List.h"

#include <stdexcept>

void List::push(const std::wstring &data) {
    if (tail_ == nullptr) {
        tail_ = new Node();
        tail_->data = data;
        head_ = tail_;
    } else {
        const auto node = new Node();
        node->data = data;
        node->next = tail_;
        tail_ = node;
    }
    size_++;
}

std::wstring List::top() const {
    if (tail_ == nullptr) {
        throw std::out_of_range("list is empty");
    }
    return tail_->data;
}

std::wstring List::back() const {
    if (head_ == nullptr) {
        throw std::out_of_range("list is empty");
    }
    return head_->data;
}

void List::pop() {
    if (tail_ == nullptr) {
        throw std::out_of_range("list is empty");
    }
    const Node *deleted = tail_;
    tail_ = tail_->next;
    if (tail_ == nullptr) {
        head_ = nullptr;
    }
    size_--;
    delete deleted;
}

int List::size() const {
    return size_;
}

bool List::is_empty() const {
    return tail_ == nullptr;
}

void List::copy(const List &other) {
    if (other.tail_ == nullptr) {
        size_ = 0;
        tail_ = nullptr;
        head_ = nullptr;
        return;
    }
    size_ = 1;
    tail_ = new Node();
    tail_->data = other.tail_->data;
    tail_->next = nullptr;
    head_ = tail_;
    Node *other_cur = other.tail_->next;
    while (other_cur != nullptr) {
        const auto node = new Node();
        node->data = other_cur->data;
        node->next = nullptr;
        head_->next = node;
        head_ = node;
        size_++;
        other_cur = other_cur->next;
    }
}
