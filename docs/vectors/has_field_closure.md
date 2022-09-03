---
layout: default
title: sp::has_field_closure
parent: vectors
---

## `sp::has_field_closure`

---

<pre>
template&lt;class Field>
bool constexpr sp::has_field_closure = /* see below */;
</pre>

---

### Possible implementation
<pre>

template&lt;typename Field>
bool constexpr sp::has_field_closure = requires(Field a, Field b) {
    { a + b } -> <a href="https://en.cppreference.com/w/cpp/concepts/convertible_to">std::convertible_to</a>&lt;Field>;
    { a - b } -> <a href="https://en.cppreference.com/w/cpp/concepts/convertible_to">std::convertible_to</a>&lt;Field>;
    { a * b } -> <a href="https://en.cppreference.com/w/cpp/concepts/convertible_to">std::convertible_to</a>&lt;Field>;
    { a / b } -> <a href="https://en.cppreference.com/w/cpp/concepts/convertible_to">std::convertible_to</a>&lt;Field>;

    { a += b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Field&>;
    { a -= b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Field&>;
    { a *= b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Field&>;
    { a /= b } -> <a href="https://en.cppreference.com/w/cpp/concepts/same_as">std::same_as</a>&lt;Field&>;
};
</pre>

