#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

int main(int argc, char* argv[])
{
  std::ifstream input_file(SOURCE_DIR "/input.txt");
  std::ofstream output_file( BINARY_DIR "/output_example.txt" );
  std::string line;
  
  while(!input_file.eof())
  {
    std::getline(input_file, line);

    if( equal(line.begin(), line.begin() + line.size()/2, line.rbegin()) )
      output_file << "YES" << std::endl;
    else
      output_file << "NO" << std::endl;

  }

  input_file.close();
  output_file.close();
}
