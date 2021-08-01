#pragma once

#include <PrimeNumber.Core/PrimeNumber.Core.API.h>
#include <vector>
#include <cmath>
#include <string>
#include <limits>

template <typename T>
class PRIMENUMBERCORE_API PrimeNumberCalculator
  {
  protected:
    std::vector<size_t> GetPrimes(size_t i_till_value);

  public:
    PrimeNumberCalculator();

    std::vector<T> GetPrimeNumbers(size_t i_till_value);
  };

template <typename T>
PrimeNumberCalculator<T>::PrimeNumberCalculator() = default;

template <typename T>
std::vector<size_t> PrimeNumberCalculator<T>::GetPrimes(size_t i_till_value)
  {
  std::vector<size_t> prime_numbers{};
  if (i_till_value < 2)
    {
    return prime_numbers;
    };

  std::vector<int8_t> natural_numbers(i_till_value + 1, 1);
  natural_numbers[0] = 0;
  natural_numbers[1] = 0;

  auto opt_outer_iteration_count = static_cast<size_t>(std::sqrt(natural_numbers.size()) + 1);
  size_t inner_iteration_count = natural_numbers.size();
  for (size_t i = 2; i < opt_outer_iteration_count; i++)
    {
    if (natural_numbers[i] == 0)
      {
      continue;
      }

    size_t j = i * i;
    while (j < inner_iteration_count)
      {
      natural_numbers[j] = 0;
      j += i;
      }
    }

  prime_numbers.reserve(natural_numbers.size());

  for (size_t i = 0; i < natural_numbers.size(); i++)
    {
    if (natural_numbers[i] != 0)
      {
      prime_numbers.push_back(i);
      }
    }

    return prime_numbers;
  }


template <typename T>
std::vector<T> PrimeNumberCalculator<T>::GetPrimeNumbers(size_t i_till_value)
  {

  static_assert (std::is_same_v<T, size_t>
                 || std::is_same_v<T, int>
                 || std::is_same_v<T, double>
                 || std::is_same_v<T, std::string>
                 || std::is_same_v<T, std::wstring>);

  auto primes_as_size_t = GetPrimes(i_till_value);

  if constexpr (std::is_same_v<T, size_t>)
    {
    return primes_as_size_t;
    }

  if constexpr (std::is_same_v<T, int>)
    {

    if (i_till_value > std::numeric_limits<int>::max())
      {
      throw std::overflow_error("can`t put 'i_till_value' in 'integer' type");
      }

    std::vector<int> primes_as_int;

    for (const auto& num : primes_as_size_t)
      {
      primes_as_int.push_back(static_cast<int>(num));
      }

    return primes_as_int;
    }

  if constexpr (std::is_same_v<T, double>)
    {
    std::vector<double> primes_as_double;

    for (const auto& num : primes_as_size_t)
      {
      primes_as_double.push_back(static_cast<double>(num));
      }

    return primes_as_double;
    }

  if constexpr (std::is_same_v<T, std::string>)
    {
    std::vector<std::string> primes_as_string;
    for (const auto& num : primes_as_size_t)
      {
      primes_as_string.push_back(std::to_string(num));
      }
    return primes_as_string;
    }

  if constexpr (std::is_same_v<T, std::wstring>)
    {
    std::vector<std::wstring> primes_as_wstring;
    for (const auto& num : primes_as_size_t)
      {
      primes_as_wstring.push_back(std::to_wstring(num));
      }
    return primes_as_wstring;
    }

  }

  