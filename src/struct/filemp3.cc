#include "filemp3.hh"

Mp3::Mp3 (std::string path)
{
    path_ = path;
    version_ = "0";
    unsync_ = "0";
    extended_ = "0";
    footer_ = "0";
    track_ = "0";
    composer_ = "0";
    disc_ = "0";
    style_ = "0";
    bmp_ = "0";
    comment_ = "0";

}

Mp3::~Mp3 ()
{
    name_ = "";
    path_ = "";
}

void Mp3::checkname (char *path)
{
    std::string s (path);

    if (path)
    {
        name_ = s;
    }
    else
        name_ = "unknown";
}
void Mp3::checkpath (char *path)
{
    std::string s (path);

    if (path)
    {
        path_ = s;
    }
    else
        path_ = "unknown";

}
void Mp3::checkversion (std::string path)
{
    if (path != "")
    {
        version_ = path;
    }
    else
        version_ = "3";

}
void Mp3::checkunsync (const char *path)
{
    if (path)
    {
        unsync_ = "1";
    }
}
void Mp3::checkextended (const char *path)
{
    if (path)
    {
        extended_ = "1";
    }
}

void Mp3::checkfooter (const char *path)
{
    if (path)
    {
        extended_ = "1";
    }
}

void Mp3::checktrack (char *path)
{
    std::string s (path);

    if (path)
    {
        track_ = s;
    }
    else
        track_ = "0";
}

void Mp3::checkcomposer (char *path)
{
    std::string s (path);
    if (path)
    {
        composer_ = s;
    }
    else
        composer_ = "0";

}
void Mp3::checkdisc (char *path)
{
    std::string s (path);
    if (path)
    {
        disc_ = s;
    }
    else
        disc_ = "0";

}
void Mp3::checkstyle (char *path)
{
    std::string s (path);
    if (path)
    {
        style_ = s;
    }
    else
        style_ = "0";

}
void Mp3::checkbmp (char *path)
{
    std::string s (path);
    if (path)
    {
        bmp_ = s;
    }
    else
        bmp_ = "0";
}
void Mp3::checkcomment (char *path)
{
    std::string s (path);
    if (path)
    {
        comment_ = s;
    }
    else
        comment_ = "0";
}

std::string Mp3::get_info ()
{
    return (name_);
}

void Mp3::printfile (std::ofstream *fichier)
{
    *fichier << "~" << name_ << "\n";
    *fichier << "        VERSION " << version_ << "\n";
    if (extended_ == "1")
        *fichier << "        EXTENDED " << "\n";
    if (footer_ == "1")
        *fichier << "        FOOTER " << "\n";
    if (unsync_ == "1")
        *fichier << "        UNSYNC " << "\n";
    if (track_ != "0")
        *fichier << "        TRACK"<<  track_ << "\n";
    if (composer_ != "0")
        *fichier << "        COMPOSER" <<  composer_ << "\n";
    if (disc_ != "0")
        *fichier << "        DISC" <<  disc_ << "\n";
    if (style_ != "0")
        *fichier << "        STYLE" << style_ << "\n";
    if (bmp_ != "0")
        *fichier << "        BMP" << bmp_ << "\n";
    if (comment_ != "0")
        *fichier << "        COMMENT" << comment_ << "\n";
}

void Mp3::print ()
{
    std::cout << "~" << name_ << "\n";
    std::cout << "        VERSION " << version_ << "\n";
    if (extended_ == "1")
        std::cout << "        EXTENDED " << "\n";
    if (footer_ == "1")
        std::cout << "        FOOTER " << "\n";
    if (unsync_ == "1")
        std::cout << "        UNSYNC " << "\n";
    if (track_ != "0")
        std::cout << "        TRACK"<<  track_ << "\n";
    if (composer_ != "0")
        std::cout << "        COMPOSER" <<  composer_ << "\n";
    if (disc_ != "0")
        std::cout << "        DISC" <<  disc_ << "\n";
    if (style_ != "0")
        std::cout << "        STYLE" << style_ << "\n";
    if (bmp_ != "0")
        std::cout << "        BMP" << bmp_ << "\n";
    if (comment_ != "0")
        std::cout << "        COMMENT" << comment_ << std::endl;
}
