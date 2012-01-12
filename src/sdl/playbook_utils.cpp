/*
 * playbook_utils.cpp
 *
 *  Created on: Jan 10, 2012
 *      Author: tnunes
 */


#include "playbook_utils.h";
#include "dirent.h";


static const char *romPath_xxx = "/accounts/1000/shared/misc/roms";
static const char *romPath_nes = "/accounts/1000/shared/misc/roms/nes";
static const char *romPath_gba = "/accounts/1000/shared/misc/roms/gba";

//
//
//
PlaybookRom::PlaybookRom(rom_type_t rtype)
{
  activeRom_m = "";
  activeRomPath_m = "";
  activeRomList_vsm.clear();
  romType_m = rtype;
  activeRomIndex_m =0;

  switch(romType_m)
  {
    case rom_nes_c:
    	 activeRomPath_m = romPath_nes;
         break;

    case rom_gba_c:
    	 activeRomPath_m = romPath_gba;
         break;

    default:  activeRomPath_m = romPath_xxx;
              break;
  }

  // root parth is now set ...

}


bool PlaybookRom::pathExists(string dpath)
{
	if( opendir(dpath.c_str() ) == NULL)
		return false;
	else
		return true;

}

void PlaybookRom::setRomPath(string dpath)
{
 if( pathExists(dpath) == true)
 {
     activeRomPath_m = dpath;
     getRomList();
 }
}

//*********************************************************
//
//*********************************************************
vector<string> PlaybookRom::getRomList( void )
{
 //vector<string> vsList;

#ifdef __QNXNTO__
	DIR* dirp;
	struct dirent* direntp;
#endif

	if(activeRomPath_m == "")
	{
        activeRomList_vsm.clear();
		return activeRomList_vsm;
	}

#ifdef __QNXNTO__
  dirp = opendir( activeRomPath_m.c_str() );
  if( dirp != NULL )
  {
	 for(;;)
	 {
		direntp = readdir( dirp );
		if( direntp == NULL )
		  break;

		 fprintf(stderr,"FILE: '%s' \n", direntp->d_name);
		// FCEUI_DispMessage(direntp->d_name,0);
		  string tmp = direntp->d_name;

		  if( strcmp( direntp->d_name, ".") == 0)
		  {
			 continue;
		  }

		  if( strcmp( direntp->d_name,"..") == 0)
			  continue;


		  if( (tmp.substr(tmp.find_last_of(".") + 1) == "nes") ||
			  (tmp.substr(tmp.find_last_of(".") + 1) == "NES") ||
			  (tmp.substr(tmp.find_last_of(".") + 1) == "gba") )
		  {
	         // fprintf(stderr,"ROM: %s\n", direntp->d_name);
			  activeRomList_vsm.push_back(direntp->d_name);
		  }
	 }
  }
  else
  {
	fprintf(stderr,"dirp is NULL ...\n");
  }

#endif
 fprintf(stderr,"number of files %d\n", activeRomList_vsm.size() );
 return activeRomList_vsm;
}




//
// Automatically iterate through a dir for roms.
//
const char *PlaybookRom::getRomNext(void)
{
    int status = 0;
    fprintf(stderr,"AutoLoadRom: %d", romType_m);

	if( activeRomList_vsm.size() == 0)
	{
	   fprintf(stderr,"AutoLoadRom: error no games in vecList\n");
	   return "";
	}

    if(++activeRomIndex_m >= activeRomList_vsm.size())
    	activeRomIndex_m = 0;

    if( activeRomList_vsm.size() == 1)
    	activeRomIndex_m = 0;

    if( activeRomIndex_m == activeRomList_vsm.size())
    	activeRomIndex_m = 0;

    activeRom_m = activeRomList_vsm[activeRomIndex_m];
    string   baseDir = activeRomPath_m + activeRomList_vsm[activeRomIndex_m];

    fprintf(stderr,"loading: %d/%d '%s'\n", activeRomIndex_m, activeRomList_vsm.size(), baseDir.c_str() );

    return baseDir.c_str();
}



//*******************************
//
//*******************************
void PlaybookRom::updateRomList(void)
{
  (void) getRomList();
}




