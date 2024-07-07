#pragma once
#include <memory>

template<typename T>
using t_uptr = std::unique_ptr<T>;

template<typename T>
using t_sptr = std::shared_ptr<T>;

template<typename T>
using t_wptr = std::weak_ptr<T>;
