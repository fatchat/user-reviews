#ifndef WIN32
#error GCC has not implemented regex_match, use input_boost.cpp instead
#endif

#include <cctype>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iomanip>
#include <regex>
#include <iterator>

#include "input.h"

namespace Input {

  // =====================================================================================
  static bool match_regex (const std::string & _value, const char * _regex)
  {
    const std::tr1::regex rx (_regex);
    return std::tr1::regex_match (_value.begin(), _value.end(), rx);
  }

  // =====================================================================================
  Field::Field (const std::string & _value)
  {
    value_ = trim_ (_value);
  }

  // =====================================================================================
  const std::string & Field::value () const
  {
    return value_;
  }

  // =====================================================================================
  bool Field::is_date () const
  {
    return match_regex (value_, "[0-9]{2}/[0-9]{2}/[0-9]{2}")
      || match_regex (value_, "(19|20)[0-9]{2}-[0-9]{2}-[0-9]{2}")
      || match_regex (value_, "(January|February|March|April|May|June|July|August|September|October|November|December) [0-9]{1,2}, (19|20)[0-9]{2}")
      ;
  }

  // =====================================================================================
  bool Field::is_funny_id () const
  {
    return match_regex (value_, "^-20ad");
  }
  
  // =====================================================================================
  bool Field::is_website () const
  {
    return match_regex (value_, "^http://");
  }
  
  // =====================================================================================
  std::string Field::trim_ (const std::string & _value) const
  {
    std::string retval = _value;

    retval.erase (std::remove (retval.begin(), retval.end(), '\n'), retval.end());

    if (retval.size () && retval.c_str () [0] == '"') {
      
      std::string::size_type end = retval.size () - 1;
      
      if (retval.c_str () [end] == '"')
		end--;
      
      retval = std::string (retval, 1, end);
    } 

    return retval;
  }
  
  // =====================================================================================
  std::ostream & operator<< (std::ostream & os, const Field & _field)
  {
    os << _field.value();
    return os;
  }

  // =====================================================================================
  struct Prompt {
    FieldType	  field;
    const char *  prompt;
  };
  
  Prompt prompt_array [] = {
    
    { title             , "Title"           },
    { date              , "Date"            },
    { review            , "Review"          },
    { funny_id_1        , "Funny ID 1"      },
    { funny_id_2        , "Funny ID 2"      },
    { business          , "Business"        },
    { website_1         , "Website 1"       },
    { website_2         , "Website 2"       },
  };
  
  // =====================================================================================
  Record::Record (const std::vector <Field> & _fields)
  {
    std::copy (_fields.begin(), _fields.end(), stdext::checked_array_iterator <Field *> (&fields_[0], NUM_FIELDS));
  }
  
  // =====================================================================================
  void Record::print (FILE * _fp) const
  {
    for (size_t i = 0; i < sizeof (prompt_array) / sizeof (prompt_array[0]); ++i) {

      const FieldType fieldtype = prompt_array [i].field;
		
      fprintf (_fp, "%10s: %s\n", prompt_array [i].prompt, fields_[fieldtype].value().c_str());
    }
  }
  
  // =====================================================================================
  std::ostream & operator<< (std::ostream & _os, const Record * _record)
  {
    for (size_t i = 0; i < sizeof (prompt_array) / sizeof (prompt_array[0]); ++i) {

      const FieldType fieldtype = prompt_array [i].field;

      _os << std::setw(10) << prompt_array[i].prompt << ": " << _record->fields_[fieldtype] << std::endl;
    }

    return _os;
  }
  
  /*
  std::ostream & operator << (std::ostream & _os, const Record * _record)
  {
	  _os << _record->fields_[business] << "####" << _record->fields_[review] << std::endl;
	  return _os;
  }*/

} // namespace Input
