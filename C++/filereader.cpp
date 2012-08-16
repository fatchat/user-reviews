// ================================== filereader.cpp =================================

#include <cassert>
#include <fstream>

#include "filereader.h"

// ================================== constructor ====================================
FileReader::FileReader (const char * _filename)
  : start_ (0)
  , end_ (0)
{
  // open file
#ifdef WIN32
  fopen_s (&ifp_, _filename, "r");
#else
  ifp_ = fopen (_filename, "r");
#endif
  // read if open succeeded
  if (!eof ())
    read_next_block_ ();
}

// ================================== eof check =====================================
bool FileReader::eof () const
{
  return (!ifp_ || !!feof (ifp_)) && (start_ == end_); 
}

// ================================== destructor ====================================
FileReader::~FileReader ()
{
  fclose (ifp_);
  ifp_ = 0;
}

// ============================= get next token ==============================
std::string FileReader::get_line ()
{
  return get_line_recursive_ ();
}

// ============================= get next token ==============================
std::string FileReader::get_line_recursive_ ()
{
  if (start_ == end_) {

    read_next_block_ ();

    if (start_ == end_)
      return std::string ();
  }

  std::string retval;
  iter_type iter;

  // iterate through buffer until next \n
  for (iter = start_; iter != end_ && *iter != '\n'; ++iter)
    ;

  // copy from buffer, advance start_ to one past the comma
  retval.append (start_, (size_t) (iter - start_));

  // end of buffer reached
  if (iter == end_) {

    // force a read in the recursive call
    start_ = end_;

    // we ASSUME that delimiters are not so sparse that they occur less than once per 16K!
    // So the recursion level should never cross 2
    return retval + get_line_recursive_ ();
  }

  // else we are still in the buffer and we hit a newline
  assert (*iter == '\n');

  // advance to one past the newline for next time
  start_ = iter + 1;
  
  return retval;  
}

// ================================== private members =======================================
const unsigned int FileReader::BUFSIZE_ = 8192;

// ================================ read from file into buffer  =============================
void FileReader::read_next_block_ ()
{
  // reset start_ index
  start_ = &buffer_[0];

  // read into buffer_
  const size_t nread = fread ((void*) start_, sizeof(char), BUFSIZE_, ifp_);

  // set end_ iterator
  end_ = &buffer_[nread];
}



