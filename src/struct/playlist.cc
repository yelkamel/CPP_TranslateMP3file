#include "playlist.hh"

PlayList::PlayList (std::string path)
{
    path_ = path;
}

PlayList::~PlayList ()
{
    path_ = "";
}

void PlayList::print ()
{
  std::list<Artist>::iterator it;

  for (it = list_.begin (); it != list_.end (); ++it)
    it->print ();
}

void PlayList::printfile (std::ofstream *file)
{
  std::list<Artist>::iterator it;

  for (it = list_.begin (); it != list_.end (); ++it)
    it->printfile (file);
}

void PlayList::addsong (Album album,
          Artist artist,
          Mp3 mp3)
{
  std::list<Artist>::iterator it;
    bool ok = true;

  for (it = list_.begin (); it != list_.end (); ++it)
  {
      if (it->get_info () == artist.get_info ())
      {
          it->pushAlbum (album, mp3);
          ok = false;
      }
  }
  if (ok)
  {
  artist.pushAlbum (album, mp3);
  list_.push_back (artist);
  }
}

