#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "filereader.h"
#include "input.h"

// =================== usage message ===============
void print_usage (std::ostream & _os, const char * _program_name)
{
  _os << "usage: " << _program_name << " <input file> [<number of records>]\n";
}

// =================== main ========================
int main (int argc, char * argv[])
{
  const char * inputfile = (argc > 1) ? argv[1]
                                      : 0;

  const int num_records = (argc > 2) ? atoi (argv[2])
                                     : -1;

  if (!inputfile) {
    print_usage (std::cout, argv[0]);
    return 1;
  }

  // set up filereader and run
  FileReader	                   filereader (inputfile);
  int                              counter = 0;
  std::vector <Input::Record *>    records;
  std::vector <Input::Field>       current_record;

  // skip 11 header fields
  for (int i = 0; i < 11; ++i)
    filereader.get_line ();

  Input::Field current, previous;
  current = filereader.get_line ();

  while (!filereader.eof () && (num_records < 0 || counter < num_records)) {

    previous = current;
    current = filereader.get_line ();

    if (current.is_date () && current_record.size ()) {

      if (current_record.size () <= Input::NUM_FIELDS) {
	++counter;
	records.push_back (new Input::Record (current_record));
	current_record.clear ();
      }
      else {
	  std::cout << "Error: Could not process [";
	  std::copy (current_record.begin(), current_record.end(), std::ostream_iterator <Input::Field> (std::cout));
	  std::cout << "]\n";
	  break;
      }
    }

    current_record.push_back (previous);

  } // end while

  // print to stdout
  const std::string record_separator ("\n");
  //const std::string record_separator (std::string (80, '=') + "\n");
  std::copy (records.begin(), records.end(), std::ostream_iterator<Input::Record*> (std::cout, record_separator.c_str ()));

  // delete Record objects
  std::for_each (records.begin(), records.end(), Input::RecordDeleter ());

  return 0;
}

