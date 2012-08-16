#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <iosfwd>
#include <vector>

namespace Input {

  bool search_regex (const std::string & _value, const char * _regex);

  // ====================================== Field class ========================================
  class Field {

  public:

    Field (const std::string & _value = std::string ());

    const std::string & value () const;

    bool is_date () const;
    bool is_funny_id () const;
    bool is_website () const;

  private:

    std::string trim_ (const std::string & _value) const;

  private:
    std::string value_;
  };

  std::ostream & operator<< (std::ostream &, const Field &);

  // ============================== FieldType and Prompt =================================
  enum FieldType {
    title,
    date,
    blank_1,
    review,
    funny_id_1,
    funny_id_2,
    business,
    website_1,
    blank_2,
    website_2,
    NUM_FIELDS
  };

  // ===================================== Record class ========================================
  class Record {

  public:

    Record (const std::vector <Field> & _fields);

    void print (FILE * _fp) const;

    //  private:

    Field fields_[NUM_FIELDS];
  };

  // =====================================================================================
  std::ostream & operator<< (std::ostream &, const Record *);
  
  struct RecordDeleter {
    void operator () (Input::Record * _record) const 
    { delete _record; }
    };

} // namespace Input

#endif // INPUT_H
