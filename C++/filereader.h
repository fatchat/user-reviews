#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <cstdlib>

class FileReader {

public:
  FileReader (const char * _filename);
  ~FileReader ();
  
  bool            eof () const;
  std::string     get_line ();
	
private:

  std::string     get_line_recursive_ ();
  void            read_next_block_ ();

  typedef char * iter_type;
  static const unsigned int BUFSIZE_;

private:

  FILE *			ifp_;
  char				buffer_ [/*BUFSIZE_*/ 8192];
  iter_type                     start_;
  iter_type                     end_;
};

#endif // FILEREADER_H

