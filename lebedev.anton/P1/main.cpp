#include <iostream>
#include <stdexcept>
#include "inc_seq.hpp"
#include "sub_max.hpp"

int main()
{
  int number = 0;
  using namespace lebedev;
  IncSeqCounter inc_seq_counter;
  SubMaxValue sub_max_value;
  do
  {
    std::cin >> number;
    if (!std::cin)
    {
      std::cerr << "Is not a sequence\n";
      return 1;
    }
    else if (number != 0)
    {
      try
      {
        inc_seq_counter.count(number);
        sub_max_value.compare(number);
      }
      catch (const std::exception& e)
      {
        std::cerr << "Error: " << e.what() << "\n";
        return 2;
      }
    }
  }
  while (number != 0);
  std::cout << inc_seq_counter.get_result() << "\n";
  try
  {
    std::cout << sub_max_value.get_result() << "\n";
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 2;
  }
  return 0;
}
