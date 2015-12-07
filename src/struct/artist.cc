#include "artist.hh"

Artist::Artist (std::string name)
{
  name_ = name;
}

Artist::~Artist ()
{
  name_ = "";
}

void Artist::checkartist (char* name)
{
    std::string s (name);
    name_ = s;
}

void Artist::pushAlbum (Album goodsong, Mp3 mp3)
{
    std::list<Album>::iterator it;
    bool ok = true;

    for (it = list_.begin (); it != list_.end (); ++it)
    {
        if (it->get_info () == goodsong.get_info ())
        {
            it->pushMp3 (mp3);
            ok = false;
        }
    }
    if (ok)
    {
        goodsong.pushMp3 (mp3);
        list_.push_back (goodsong);
    }
}

void Artist::print ()
{
  if (name_ == "")
    name_ = "Unknown";
  std::cout << "# " << name_ << std::endl;
  std::list<Album>::iterator it;

  for (it = list_.begin (); it != list_.end (); ++it)
    it->print ();

}

void Artist::printfile (std::ofstream* fichier)
{
  if (*fichier)
  {
      if (name_ == "")
          name_ = "Unknown";
      *fichier << "# " << name_ << "\n";
      std::list<Album>::iterator it;
      for (it = list_.begin (); it != list_.end (); ++it)
          it->printfile (fichier);
  }
  else
      std::cerr << "impossible de cree le fichier" << std::endl;

}

std::string Artist::get_info ()
{
  return (name_);
}
