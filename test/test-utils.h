#pragma once

#include <gtest/gtest.h>

template <typename C>
void mass_push_back(C&) {}

template <typename C, typename Element, typename... Elements>
void mass_push_back(C& cont, Element& element, Elements&... elements) {
  cont.push_back(element);
  mass_push_back(cont, elements...);
}

template <typename C>
void mass_push_front(C&) {}

template <typename C, typename Element, typename... Elements>
void mass_push_front(C& cont, Element& element, Elements&... elements) {
  cont.push_front(element);
  mass_push_front(cont, elements...);
}

template <typename E, typename A>
void expect_eq_impl(E expected_first, E expected_last, A actual_first, A actual_last) {
  for (;;) {
    bool expected_ended = expected_first == expected_last;
    bool actual_ended = actual_first == actual_last;
    EXPECT_EQ(expected_ended, actual_ended);

    if (expected_ended || actual_ended) {
      break;
    }

    EXPECT_EQ(*expected_first, *actual_first);
    ++expected_first;
    ++actual_first;
  }
}

template <typename C>
void expect_eq(C& cont, std::initializer_list<int> values) {
  expect_eq_impl(values.begin(), values.end(), cont.begin(), cont.end());
  expect_eq_impl(std::make_reverse_iterator(values.end()), std::make_reverse_iterator(values.begin()),
                 std::make_reverse_iterator(cont.end()), std::make_reverse_iterator(cont.begin()));
}

struct copyable_node : intrusive::list_element<> {
  explicit copyable_node(int value) : value(value) {}

  operator int() const {
    return value;
  }

  int value;
};

struct node : intrusive::list_element<> {
  explicit node(int value) : value(value) {}

  node(const node& other) = delete;
  node(node&& other) = delete;
  node& operator=(const node& other) = delete;
  node& operator=(node&& other) = delete;

  operator int() const {
    return value;
  }

  int value;
};

struct multi_node : intrusive::list_element<struct tag_a>, intrusive::list_element<struct tag_b> {
  explicit multi_node(int value) : value(value) {}

  multi_node(const multi_node& other) = delete;
  multi_node(multi_node&& other) = delete;
  multi_node& operator=(const multi_node& other) = delete;
  multi_node& operator=(multi_node&& other) = delete;

  operator int() const {
    return value;
  }

  int value;
};

inline void magic(node& n) {
  n.value = 42;
}

inline void magic([[maybe_unused]] const node& n) {}