#pragma once

#include <cstddef>

namespace intrusive {
struct default_tag;

template <typename Tag = default_tag>
struct list_element {};

template <typename T, typename Tag = default_tag>
struct list {
  using iterator = void;
  using const_iterator = void;

  // Constructs an empty list.
  list() noexcept;
  // Unlinks all the elements from the list.
  ~list() noexcept;

  list(const list&) noexcept = delete;
  list& operator=(const list&) noexcept = delete;
  // Transfers all the elements from other into *this.
  list(list&& other) noexcept;
  // Unlinks all the elements out of this
  //     and transfers all the elements from other to *this.
  list& operator=(list&& other) noexcept;

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  // Returns a reference to the first element in the list.
  // Calling front on an empty list causes UB.
  T& front() noexcept;
  const T& front() const noexcept;
  // Returns a reference to the last element in the list.
  // Calling back on an empty list causes UB.
  T& back() noexcept;
  const T& back() const noexcept;

  std::size_t size() const noexcept;
  bool empty() const noexcept;

  // Appends exactly value (not copy) to the beginning of the list.
  // If any list contained value before calling push_front,
  //     it gets unlinked out of that list.
  void push_front(T& value) noexcept;
  // Appends exactly value (not copy) to the end of the list.
  // If any list contained value before calling push_back,
  //     it gets unlinked out of that list.
  void push_back(T& value) noexcept;
  // Unlinks the first element of the list.
  // Calling push_back on an empty list causes UB.
  void pop_front() noexcept;
  // Unlinks the last element of the list.
  // Calling pop_back on an empty list causes UB.
  void pop_back() noexcept;

  // Inserts exactly value (not copy) before pos.
  // Returns an iterator pointing to value.
  // If any list contained value before calling insert,
  //     it gets unlinked out of that list.
  iterator insert(const_iterator pos, T& elem) noexcept;
  // Unlinks the element at pos. The iterator pos must not be end().
  iterator erase(const_iterator pos) noexcept;

  // pos must be an iterator into *this,
  //     first and last must be iterators into other.
  // Transfers the elements in the range [first, last) from other into *this.
  // The elements are inserted before pos.
  // It's allowed for *this and other to be the same object.
  void splice(const_iterator pos, list& other, const_iterator first,
              const_iterator last) noexcept;
};
} // namespace intrusive
