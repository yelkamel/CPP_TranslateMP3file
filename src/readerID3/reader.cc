#include "reader.hh"

    Reader::Reader (std::string path, Mp3 *zik)
: path_ (path),
    zik_ (zik),
    artist_ (NULL),
    album_ (NULL)
{
    file_.open (path, std::ios::out | std::ios::binary);
}


    Reader::Reader (std::string path, Artist *artist)
: path_ (path),
    zik_ (NULL),
    artist_ (artist),
    album_ (NULL)
{
    file_.open (path, std::ios::out | std::ios::binary);
}

    Reader::Reader (std::string path, Album *album)
: path_ (path),
    zik_ (NULL),
    artist_ (NULL),
    album_ (album)
{
    file_.open (path, std::ios::out | std::ios::binary);
}

Reader::~Reader ()
{
}

void Reader::frames (char* f, char* data)
{
    data[0] = ' ';
    if (strncmp (f, "TRCK", 4) == 0)
    {
        if (data[2] > '9' || data[2] < '0')
            data[2] = '\0';
        else
            data[3] = '\0';
        zik_->checktrack (data);
    }
    if (strncmp (f, "TCOM", 4) == 0)
        zik_->checkcomposer (data);
    if (strncmp (f, "TPOS", 4) == 0)
        zik_->checkdisc (data);
    if (strncmp (f, "TCON", 4) == 0)
    {
        data[6] = '\0';
        zik_->checkstyle (data);
    }
    if (strncmp (f, "TBPM", 4) == 0)
        zik_->checkbmp (data);
    if (strncmp (f, "COMM", 4) == 0)
        zik_->checkcomment (data);
    if (strncmp (f, "TIT2", 4) == 0)
        zik_->checkname (data);
}

void Reader::artistframe (char* f, char* data)
{
    if (strncmp (f, "TPE1", 4) == 0)
        artist_->checkartist (data);
    if (strncmp (f, "TPE2", 4) == 0)
        artist_->checkartist (data);
}

void Reader::albumframe (char* f, char* data)
{
    if (strncmp (f, "TALB", 4) == 0)
        album_->checkalbum (data);
    if (strncmp (f, "TDRL", 4) == 0)
        album_->checkdate (data);
    if (strncmp (f, "TYER", 4) == 0)
        album_->checkdate (data);
}


void Reader::takalbum_end (int n, int s)
{
    int size_ = s - n + n;
    int size = 0;
    char* title;
    char* frame;
    char* tmp;
    int vers;

    tmp = new char[4];

    while (size_ > 2500)
    {
        frame = new char[4];
        file_.read (frame, 4);
        size = 0;
        file_.read (tmp, 4);
        for (int i = 0; i < 4; i++)
        {
            size = size << 8;
            size += tmp[i];
        }
        file_.read (reinterpret_cast<char*>(&vers), 2);
        if (size > 0)
        {
            title = new char[size];
            file_.read (title, size);
            size_ -= size;
            albumframe (frame, title);
            delete title;
        }
        else
            file_.read (title, size);
    }
    file_.close ();
}

void Reader::takartist_end (int n, int s)
{
    int size_ = s - n + n;
    int size = 0;
    char* title;
    char* frame;
    char* tmp;
    int vers;

    tmp = new char[4];

    while (size_ > 2500)
    {
        frame = new char[4];
        file_.read (frame, 4);
        size = 0;
        file_.read (tmp, 4);
        for (int i = 0; i < 4; i++)
        {
            size = size << 8;
            size += tmp[i];
        }
        file_.read (reinterpret_cast<char*>(&vers), 2);
        if (size > 0)
        {
            title = new char[size];
            file_.read (title, size);
            size_ -= size;
            artistframe (frame, title);
            delete title;
        }
        else
            file_.read (title, size);
    }
    file_.close ();
}

void Reader::read_end (int n, int s)
{
    int size_ = s - n + n;
    int size = 0;
    char* title;
    char* frame;
    char* tmp;
    int vers;

    tmp = new char[4];

    while (size_ > 2500)
    {
        frame = new char[4];
        file_.read (frame, 4);
        size = 0;
        file_.read (tmp, 4);
        for (int i = 0; i < 4; i++)
        {
            size = size << 8;
            size += tmp[i];
        }
        file_.read (reinterpret_cast<char*>(&vers), 2);
        if (size > 0)
        {
            title = new char[size];
            file_.read (title, size);
            size_ -= size;
            frames (frame, title);
            delete title;
        }
        else
            file_.read (title, size);
    }
    file_.close ();
}

std::string Reader::convertInt (int number)
{
    char okai[2];
    okai[0] = number + '0';
    okai[1] = '\0';
    std::string ss (okai);
    return ss;
}

void Reader::read ()
{
    char* id3 = new char[3];
    char* tmp;
    int vers;
    char* flags = new char[1];
    int size;
    int size_;
    int n = 0;
    std::bitset<8> bit;

    if (file_.is_open ())
    {
        file_.read (id3, 3);
        file_.read (reinterpret_cast<char*>(&vers), 2);
        this->zik_->checkversion (convertInt (vers));
        file_.read (flags, 1);
        bit = std::bitset<8>(flags[0]);
        if (bit[7] == 1)
            zik_->checkunsync ("1");
        if (bit[6] == 1)
            zik_->checkextended ("1");
        tmp = new char[4];
        file_.read (tmp, 4);
        for (int i = 0; i < 4; i++)
        {
            size = size << 8;
            size += tmp[i];
        }
        size_ = size;
        n += 10;
        if (bit[4] == 1)
        {
            file_.read (tmp, 4);
            size = 0;
            for (int i = 0; i < 4; i++)
            {
                size = size << 8;
                size += tmp[i];
            }
            tmp = new char[4];
            file_.read (tmp, size - 4);
            zik_->checkfooter ("1");
            n += size;
        }
        read_end (n , size_);
    }
    else
        std::cout << "Unable to open file" << std::endl;
}

void Reader::takalbum ()
{
    char* id3 = new char[3];
    char* tmp;
    int vers;
    char* flags = new char[1];
    int size;
    int size_;
    int n = 0;
    std::bitset<8> bit;

    if (file_.is_open ())
    {
        file_.read (id3, 3);
        file_.read (reinterpret_cast<char*>(&vers), 2);
        file_.read (flags, 1);
        bit = std::bitset<8>(flags[0]);
        tmp = new char[4];
        file_.read (tmp, 4);
        for (int i = 0; i < 4; i++)
        {
            size = size << 8;
            size += tmp[i];
        }
        size_ = size;
        n += 10;
        if (bit[4] == 1)
        {
            file_.read (tmp, 4);
            size = 0;
            for (int i = 0; i < 4; i++)
            {
                size = size << 8;
                size += tmp[i];
            }
            tmp = new char[4];
            file_.read (tmp, size - 4);
            n += size;
        }
        takalbum_end (n , size_);
    }
    else
        std::cout << "Unable to open file" << std::endl;
}

void Reader::takartist () {
    char* id3 = new char[3];
    char* tmp;
    int vers;
    char* flags = new char[1];
    int size;
    int size_;
    int n = 0;
    std::bitset<8> bit;

    if (file_.is_open ())
    {
        file_.read (id3, 3);
        file_.read (reinterpret_cast<char*>(&vers), 2);
        file_.read (flags, 1);
        bit = std::bitset<8>(flags[0]);
        tmp = new char[4];
        file_.read (tmp, 4);
        for (int i = 0; i < 4; i++)
        {
            size = size << 8;
            size += tmp[i];
        }
        size_ = size;
        n += 10;
        if (bit[4] == 1)
        {
            file_.read (tmp, 4);
            size = 0;
            for (int i = 0; i < 4; i++)
            {
                size = size << 8;
                size += tmp[i];
            }
            tmp = new char[4];
            file_.read (tmp, size - 4);
            n += size;
        }
        takartist_end (n , size_);
    }
    else
        std::cout << "Unable to open file" << std::endl;
}
