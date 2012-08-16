#include <iostream>

#include "../filereader.h"

int main (int argc, char * argv[])
{
  if (argc < 2) {

    std::cout << "usage: " << argv[0] << " <input file>" << std::endl;
    return 1;
  }

  const char * inputfile = argv[1];

  FileReader filereader (inputfile);

  while (!filereader.eof ()) {

    std::string line = filereader.get_line ();

    std::cout << line << "\n";
  }

  return 0;
}
