#ifndef ARTIST_HH_
# define ARTIST_HH_
# include "album.hh"
# include <fstream>
# include <iostream>
# include <string>

class Artist
{
public:
  Artist (std::string name);
  ~Artist ();
  std::string get_info ();
  void pushAlbum (Album goodsong, Mp3 mp3);
    void checkartist (char* name);
  void set_info ();
  void print ();
  void printfile (std::ofstream* file);
private:
  std::string         name_;
  std::list<Album>    list_;
};

#endif /* ARTIST_HH_ */
