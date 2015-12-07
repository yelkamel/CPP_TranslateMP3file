#include "album.hh"

void Album::checkdate (char* name)
{
    std::string s (name);
    date_ = s;
}

Album::Album (std::string name) :  name_ (name), date_ ("")
{
}

void Album::checkalbum (char* okai)
{
    std::string s (okai);
    name_ = s;
}


void Album::pushMp3 (Mp3 file)
{
    std::list<Mp3>::iterator it;
    bool ok = true;

    for (it = list_.begin (); it != list_.end (); ++it)
    {
        if (it->get_info () == file.get_info ())
        {
            ok = false;
        }
    }
    if (ok)
    {
        list_.push_back (file);
    }
}

Album::~Album ()
{
  name_ = "";
}

std::string Album::get_info ()
{
  return (name_);
}

void Album::print ()
{
  if (date_ == "")
    {
      date_ = "0";
    }
  if (name_ == "")
    {
      name_ = "Unknown";
    }
  std::cout << "$" << date_ << "$ " << name_ << std::endl;
  std::list<Mp3>::iterator it;

  for (it = list_.begin (); it != list_.end (); ++it)
    it->print ();

}

void Album::printfile (std::ofstream *fichier)
{
        if (date_ == "")
        {
            date_ = "0";
        }
        if (name_ == "")
        {
            name_ = "Unknown";
        }
        *fichier << "$" << date_ << "$ " << name_ << "\n";
        std::list<Mp3>::iterator it;

        for (it = list_.begin (); it != list_.end (); ++it)
            it->printfile (fichier);
}
