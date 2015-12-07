#ifndef FILEMP3_HH_
# define FILEMP3_HH_
# include <iostream>
# include <list>
# include <algorithm>
# include <string>
# include <fstream>

class Mp3
{
public:
  Mp3 (std::string path);
  ~Mp3 ();
  std::string get_info ();
  void print ();
  void printfile (std::ofstream *file);
  void checkname (char *path);
  void checkpath (char *path);
  void checkversion (std::string path);
  void checkunsync (const char *path);
  void checkextended (const char *path);
  void checkfooter (const char *path);
  void checktrack (char *path);
  void checkcomposer (char *path);
  void checkdisc (char *path);
  void checkstyle (char *path);
  void checkbmp (char *path);
  void checkcomment (char *path);

private:
  std::string   name_;
  std::string   path_;
  std::string  version_;
  std::string  unsync_;
  std::string  extended_;
  std::string  footer_;
  std::string  track_;
  std::string  composer_;
  std::string  disc_;
  std::string  style_;
  std::string  bmp_;
  std::string  comment_;

};

#endif /* FILEMP3_HH_ */
