#ifndef ALBUM_HH_
# define ALBUM_HH_
# include "filemp3.hh"
# include <iostream>
# include <string>
# include <fstream>

class Album
{
public:
  Album (std::string name);
  ~Album ();
  std::string get_info ();
  void set_info ();
  void checkalbum (char* okai);
  void checkdate (char* okai);
  void pushMp3 (Mp3 file);
  void print ();
  void printfile (std::ofstream *fichier);
private:
  std::string       name_;
  std::string       date_;
  std::list<Mp3>    list_;
};

#endif /* ALBUM_HH_ */
