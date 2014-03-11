#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <cmath>

// read array 
// see if list contains it 

double readDouble(std::ifstream& input_file) {
  std::string double_string;
  std::getline(input_file, double_string);
  std::cout << double_string << std::endl;
  return (double) atof(double_string.c_str());
}

int main(int argc, char* argv[])
{
  std::ifstream input_file(SOURCE_DIR "/input.txt");
  std::ofstream output_file(SOURCE_DIR "/output.txt");
  int numbers_count;
  std::list<double> numbers;

  numbers_count = (int) readDouble(input_file);
    
  for (int i = 0; i < numbers_count; i++) {
    double a = readDouble(input_file);
    numbers.push_back(a);
  }
  

  while(!input_file.eof())
  {
    double pass;
    pass = readDouble(input_file);
    pass = std::floor(pass * 10000) / 10000;

    std::cout << " pass " << pass << std::endl;
    std::list<double>::iterator pos = std::find(numbers.begin(), numbers.end(), pass);
    if (pos != numbers.end())
      output_file << "YES" << std::endl;
    else
      output_file << "NO" << std::endl;

  }

  input_file.close();
  output_file.close();
}
