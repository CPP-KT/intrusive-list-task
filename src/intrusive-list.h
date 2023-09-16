#pragma once

#include <cstddef>
#include <type_traits>

namespace intrusive {

class default_tag;

template <typename Tag = default_tag>
class list_element {};

template <typename T, typename Tag = default_tag>
class list {
  static_assert(std::is_base_of_v<list_element<Tag>, T>, "T must derive from list_element");

public:
  using iterator = void;
  using const_iterator = void;

public:
  // O(1)
  list() noexcept;

  // O(1)
  ~list();

  list(const list&) = delete;
  list& operator=(const list&) = delete;

  // O(1)
  list(list&& other) noexcept;

  // O(1)
  list& operator=(list&& other) noexcept;

  // O(1)
  bool empty() const noexcept;

  // O(n)
  size_t size() const noexcept;

  // O(1)
  T& front() noexcept;

  // O(1)
  const T& front() const noexcept;

  // O(1)
  T& back() noexcept;

  // O(1)
  const T& back() const noexcept;

  // O(1)
  void push_front(T& value) noexcept;

  // O(1)
  void push_back(T& value) noexcept;

  // O(1)
  void pop_front() noexcept;

  // O(1)
  void pop_back() noexcept;

  // O(1)
  void clear() noexcept;

  // O(1)
  iterator begin() noexcept;

  // O(1)
  const_iterator begin() const noexcept;

  // O(1)
  iterator end() noexcept;

  // O(1)
  const_iterator end() const noexcept;

  // O(1)
  iterator insert(const_iterator pos, T& value) noexcept;

  // O(1)
  iterator erase(const_iterator pos) noexcept;

  // O(1)
  void splice(const_iterator pos, list& other, const_iterator first, const_iterator last) noexcept;
};

} // namespace intrusive
