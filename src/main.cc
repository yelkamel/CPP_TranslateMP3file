#include "struct/playlist.hh"
#include "opt/option.hh"
#include "readerID3/reader.hh"
#include "struct/filemp3.hh"
#include <boost/filesystem.hpp>


int lookin (char* pathi, PlayList* play)
{

    const std::string my_folder_name (pathi);
    const boost::filesystem::path my_folder
        = boost::filesystem::system_complete (boost::filesystem::path (my_folder_name));

    boost::filesystem::path p (pathi);
    if (boost::filesystem::exists (p) && boost::filesystem::is_directory (p))
    {
        const boost::filesystem::recursive_directory_iterator j;
        for (boost::filesystem::recursive_directory_iterator i (my_folder);
                i != j;
                ++i)
        {
            if (boost::filesystem::is_regular_file (i->status ()))
            {
                if (boost::filesystem::extension (i->path ().filename ())
                        == ".mp3")
                {
                    Mp3 *zic = new Mp3 (i->path().string());
                    Album *alb = new Album ("");
                    Artist *art = new Artist ("");
                    Reader (i->path ().string (), alb).takalbum ();
                    Reader (i->path().string(), art).takartist ();
                    Reader (i->path().string(), zic).read ();
                    play->addsong (*alb, *art, *zic);
                    delete zic;
                    delete alb;
                    delete art;
                }
                else
                std::cout << "Zic-Warning :" << i->path ().filename () << "is not a correct mp3 file" << std::endl;
            }
        }
    }
    else
        std::cout << p << " does not exist or is a file\n";
    return 0;
}

int main (int argc, char** argv)
{
    PlayList* play = new PlayList ("toto");

    argc = parsopt (argv);
    if (argc == 1)
    {
        lookin (argv[2], play);
        play->print ();
    }
    else if (argc == 2)
    {
        std::ofstream fichier (argv[3], std::ios::out | std::ios::trunc);
        lookin (argv[2], play);
        play->printfile (&fichier);
        fichier.close ();
    }

    return (0);
}
