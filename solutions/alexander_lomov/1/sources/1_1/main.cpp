#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

bool insignificantCharacter(char ch) {
  return (ch == ' ' || ch == '-' || ch == '\\');
}

std::string canonicalForm(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(), ::tolower);
  s.erase(std::remove_if(s.begin(), s.end(), ::insignificantCharacter), s.end());
  return s;
}

int main(int argc, char* argv[]) {
  std::ifstream input_file(BINARY_DIR "/input.txt");
  std::ofstream output_file(BINARY_DIR "/output.txt");
  std::string first_line;
  std::string first_line_canonical;
  std::string line;
  std::string line_canonical;

  std::getline(input_file, first_line);
  first_line_canonical = canonicalForm(first_line);

  while(!input_file.eof()) {
    std::getline(input_file, line);

    line_canonical = canonicalForm(line);
    
    std::size_t pos = first_line_canonical.find(line_canonical);
    if (pos != std::string::npos)
      output_file << "YES" << std::endl;
    else
      output_file << "NO" << std::endl;
  }

  input_file.close();
  output_file.close();
}
