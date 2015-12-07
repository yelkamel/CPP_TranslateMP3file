#ifndef READER_HH_
# define READER_HH_

# include <iostream>
# include <fstream>
# include <string>
# include <bitset>
# include "../struct/filemp3.hh"
# include "../struct/album.hh"
# include "../struct/artist.hh"
# include <string.h>

class Reader
{
public:
    Reader (std::string path, Mp3 *zik);
    Reader (std::string path, Artist *artist);
    Reader (std::string path, Album *album);
    ~Reader ();
    void read ();
    void read_end (int n, int s);
    void takalbum ();
    void takalbum_end (int n, int s);
    void takartist ();
    void takartist_end (int n, int s);

    void frames (char* f, char* data);
    void artistframe (char* f, char* data);
    void albumframe (char* f, char* data);
    std::string convertInt (int number);
    //void takalbum (std::string path);
    //void takartist (std::string path);
private:
    std::string path_;
    Mp3 *zik_;
    Artist* artist_;
    Album* album_;
    std::ifstream file_;

};

#endif /* READER_HH_ */
