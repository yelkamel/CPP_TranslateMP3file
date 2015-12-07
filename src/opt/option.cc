#include "option.hh"

void helper (void)
{
  std::cout << "Usage: zik-end [-f] [-h] [-o]" << std::endl;
  std::cout << "-f inputfile outputfile          read information of \
inputfile and set this in outputfile" << std::endl;
  std::cout << "-o inputfile                     read information of \
inputfile and set this in output" << std::endl;
  std::cout << "-h                               display this help and\
 exit" << std::endl;
}

int parsopt (char **argv)
{
  if (argv[1] && !strcmp (argv[1], "-h"))
      helper ();
      else
	if (argv[1] && argv[2] && !strcmp (argv[1], "-o"))
	  {
	    return (1);
	  }
	else if (argv[1] && argv[2] && argv[3] && !strcmp (argv[1], "-f"))
	  {
	    return (2);
	    }
	  else
	    {
	      std::cout << "[!] invalid argument !\n" << std::endl;
	      helper ();
	    }

	  return (0);
}
