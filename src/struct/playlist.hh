#ifndef PLAYLIST_HH_
# define PLAYLIST_HH_
# include "artist.hh"
# include <iostream>
# include "album.hh"
# include "filemp3.hh"

class PlayList
{
public:
  PlayList (std::string path);
  ~PlayList ();
  void print ();
  void printfile (std::ofstream* file);
  void addsong (Album album,
          Artist artist,
          Mp3 mp3);
private:
  std::string          path_;
  std::list<Artist>    list_;
};

#endif /* PLAYLIST_HH_ */
