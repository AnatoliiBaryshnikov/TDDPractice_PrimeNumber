#include <PrimeNumber.Core/PrimeNumberCalculator.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ::testing;

/*

Trying simple tests

*/

TEST(PrimeNumberCalculator_GetPrimeNumbers,
     Contains_2_When_Get_Primes_Up_to_5)
  {
  //setup
  PrimeNumberCalculator<size_t> calc;

  //act
  const auto result = calc.GetPrimeNumbers(5);

  //assert
  EXPECT_THAT(result, Contains(2));
  }

TEST(PrimeNumberCalculator_GetPrimeNumbers,
  Contains_3_When_Get_Primes_Up_to_5)
  {
  PrimeNumberCalculator<size_t> calc;

  const auto result = calc.GetPrimeNumbers(5);

  EXPECT_THAT(result, Contains(3));
  }

TEST(PrimeNumberCalculator_GetPrimeNumbers,
     NOT_Contains_4_When_Get_Primes_Up_to_15)
  {
  PrimeNumberCalculator<size_t> calc;

  const auto result = calc.GetPrimeNumbers(5);

  EXPECT_THAT(result, Not(Contains(4)));
  }

/*

Trying test fixtures to have common setup for some unit tests

*/

class TestFixture : public testing::Test
  {
    protected:
    PrimeNumberCalculator<size_t>* mp_prime_num_calc; // using raw pointer just to try resource management in constructor/destructor

    public:
    TestFixture()
      {
      mp_prime_num_calc = new PrimeNumberCalculator<size_t>;
      }

    virtual ~TestFixture()
      {
      delete mp_prime_num_calc;
      mp_prime_num_calc = nullptr;
      }
  };

TEST_F(TestFixture,
  Contains_Nothing_When_Argument_is_1)
  {
  ASSERT_THAT(mp_prime_num_calc->GetPrimeNumbers(1), ElementsAre());
  }

TEST_F(TestFixture,
  Contains_Nothing_When_Argument_is_0)
  {
  ASSERT_THAT(mp_prime_num_calc->GetPrimeNumbers(0), ElementsAre());
  }

TEST_F(TestFixture,
  Contains_Predetermined_Set_of_Primes_up_to_2)
  {
  ASSERT_THAT(mp_prime_num_calc->GetPrimeNumbers(2), ElementsAre(2));
  }

TEST_F(TestFixture,
  Contains_Predetermined_Set_of_Primes_up_to_3)
  {
  ASSERT_THAT(mp_prime_num_calc->GetPrimeNumbers(3), ElementsAre(2,3));
  }

TEST_F(TestFixture,
     NOT_Contains_Predetermined_Set_of_All_Numbers_up_to_15)
  {
  ASSERT_THAT(mp_prime_num_calc->GetPrimeNumbers(15), Not(ElementsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)));
  }

TEST_F(TestFixture,
  Contains_Predetermined_Set_of_Primes_up_to_15)
  {
  ASSERT_THAT(mp_prime_num_calc->GetPrimeNumbers(15), ElementsAre(2, 3, 5, 7, 11, 13));
  }

TEST_F(TestFixture,
  Contains_Predetermined_Set_of_Primes_up_to_17_including)
  {
  ASSERT_THAT(mp_prime_num_calc->GetPrimeNumbers(17), ElementsAre(2, 3, 5, 7, 11, 13, 17));
  }

TEST_F(TestFixture,
  Contains_Predetermined_Set_of_Primes_up_to_1000)
  {
  ASSERT_THAT(mp_prime_num_calc->GetPrimeNumbers(1000),
              ElementsAre(2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
              101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
              211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
              307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
              401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
              503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599,
              601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691,
              701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797,
              809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887,
              907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997));
  }

/*

Trying parametric tests to unify multiple tests with similar parameters checks
Also having fun with inheritance :)

*/

class TestParametric : public TestFixture, public ::testing::WithParamInterface<size_t>
  {

    public:
    TestParametric()
    {
    }

  };

// could take up to 1.5 minutes to finish in release mode with all compiler optimizations
TEST_P(TestParametric, NOT_Contains_Pseudo_Primes_up_to_2301745250)
  {
  EXPECT_THAT(mp_prime_num_calc->GetPrimeNumbers(GetParam() + 1), Not(Contains(GetParam()))); // GetPrimeNumbers(GetParam()+1) seems stupid but it is kinda optimization here
  }

INSTANTIATE_TEST_SUITE_P(Carmichael_Pseudo_Primes_up_to_2301745250,
  TestParametric,
  ::testing::Values( 561,        //0
                     1105,       //1
                     1729,       //2
                     2465,       //3
                     2821,       //4
                     6601,       //5
                     8911,       //6
                     10585,      //7
                     15841,      //8
                     29341,      //9
                     41041,      //10
                     46657,      //11
                     52633,      //12
                     62745,      //13
                     63973,      //14
                     75361,      //15
                     101101,     //16
                     115921,     //17
                     126217,     //18
                     162401,     //19
                     172081,     //20
                     188461,     //21
                     252601,     //22
                     278545,     //23
                     294409,     //24
                     314821,     //25
                     334153,     //26
                     340561,     //27
                     399001,     //28
                     410041,     //29
                     449065,     //30
                     488881,     //31
                     512461,     //32
                     56052361,   //33
                     118901521,  //34
                     172947529,  //35
                     216821881,  //36
                     228842209,  //37
                     1299963601, //38
                     2301745249  //39
                   ));



/*

Trying basics of TYPED_TEST

*/

template <typename T>
class TestTypedNumbers : public testing::Test {
  protected:
  PrimeNumberCalculator<T>* mp_prime_num_calc; // using raw pointer just to try resource management in constructor/destructor

  public:
  TestTypedNumbers()
    {
    mp_prime_num_calc = new PrimeNumberCalculator<T>;
    }

  virtual ~TestTypedNumbers()
    {
    delete mp_prime_num_calc;
    mp_prime_num_calc = nullptr;
    }

  };

using testing::Types;
typedef Types<size_t, int, double> Implementations;

TYPED_TEST_SUITE(TestTypedNumbers, Implementations);

TYPED_TEST(TestTypedNumbers,
  Contains_Predetermined_Set_of_Primes_up_to_15)
  {
  ASSERT_THAT(mp_prime_num_calc->GetPrimeNumbers(17), ElementsAre(2, 3, 5, 7, 11, 13, 17));
  }


template <typename T>
class TestTypedStrings : public TestTypedNumbers<T> {

  public:
  TestTypedStrings()
    {
    }

  };

typedef Types<std::string , std::wstring> ImplementationsForStrings;

TYPED_TEST_SUITE(TestTypedStrings, ImplementationsForStrings);

TYPED_TEST(TestTypedStrings,
  Contains_Predetermined_Set_of_Primes_up_to_17)
  {
  auto vec = mp_prime_num_calc->GetPrimeNumbers(17);
  auto first = std::stoll(vec.front());
  auto last = std::stoll(vec.back());

  ASSERT_EQ(first, 2);
  ASSERT_EQ(last, 17);
  }

/*

Some additional tests to check overflow after adding integer as possible template variant

*/

TEST(PrimeNumberCalculator_GetPrimeNumbers,
  MUST_Throw_Exception_When_Called_With_Value_That_Overflows_Integer)
  {
  PrimeNumberCalculator<int> calc;

  EXPECT_ANY_THROW(calc.GetPrimeNumbers(std::numeric_limits<int>::max() + 1));
  }

// TODO: adding Fermat primality test would be cool