#include <string>
using namespace std;
#include "version.h"
char Version::revision[] = "$Revision: 1.15 $";
char Version::date[] = "$Date: 2003/08/06 17:40:34 $";
char *Version::ident[] = {
"$" "Id:" " Makefile 1.49 2003/08/06 17:13:53 dds Exp dds $",
"$" "Id:" " attr.cpp 1.12 2003/07/28 20:09:31 dds Exp $",
"$" "Id:" " attr.h 1.11 2003/07/28 20:09:31 dds Exp $",
"$" "Id:" " color.cpp 1.9 2002/09/28 13:22:40 dds Exp $",
"$" "Id:" " cscout.cpp 1.54 2003/08/06 17:12:03 dds Exp $",
"$" "Id:" " ctoken.cpp 1.22 2003/08/03 16:12:11 dds Exp $",
"$" "Id:" " ctoken.h 1.4 2001/09/12 07:09:08 dds Exp $",
"$" "Id:" " debug.cpp 1.2 2001/09/03 08:13:51 dds Exp $",
"$" "Id:" " debug.h 1.6 2003/08/02 10:52:22 dds Exp $",
"$" "Id:" " defs.h 1.12 2002/12/25 19:35:42 dds Exp $",
"$" "Id:" " des.c 1.9 2003/07/08 13:16:20 dds Exp $",
"$" "Id:" " des.h 1.3 2003/05/17 07:38:32 dds Exp $",
"$" "Id:" " eclass.cpp 1.24 2003/07/28 20:09:31 dds Exp $",
"$" "Id:" " eclass.h 1.18 2003/07/28 20:09:31 dds Exp $",
"$" "Id:" " engine.cpp 1.3 2002/09/17 10:53:02 dds Exp $",
"$" "Id:" " error.cpp 1.11 2003/06/01 09:03:06 dds Exp $",
"$" "Id:" " error.h 1.4 2001/10/27 13:46:12 dds Exp $",
"$" "Id:" " eval.y 1.9 2003/06/01 09:03:06 dds Exp $",
"$" "Id:" " fchar.cpp 1.25 2003/07/31 15:23:30 dds Exp $",
"$" "Id:" " fchar.h 1.11 2003/06/19 11:11:01 dds Exp $",
"$" "Id:" " fileid.cpp 1.26 2003/08/02 21:02:04 dds Exp $",
"$" "Id:" " fileid.h 1.16 2003/07/31 15:23:30 dds Exp $",
"$" "Id:" " id.h 1.2 2001/09/21 14:14:19 dds Exp $",
"$" "Id:" " incs.h 1.1 2002/09/05 16:43:58 dds Exp $",
"$" "Id:" " license.c 1.9 2003/07/08 10:46:53 dds Exp $",
"$" "Id:" " license.h 1.6 2003/07/08 10:13:51 dds Exp $",
"$" "Id:" " macro.cpp 1.19 2003/08/02 20:42:31 dds Exp $",
"$" "Id:" " macro.h 1.8 2003/08/02 10:52:41 dds Exp $",
"$" "Id:" " metrics.cpp 1.10 2003/07/31 15:23:30 dds Exp $",
"$" "Id:" " metrics.h 1.9 2003/06/22 23:27:04 dds Exp $",
"$" "Id:" " obfuscate.cpp 1.2 2003/07/02 10:47:15 dds Exp $",
"$" "Id:" " parse.y 1.78 2003/08/03 16:33:05 dds Exp $",
"$" "Id:" " pdtoken.cpp 1.82 2003/08/01 14:52:30 dds Exp $",
"$" "Id:" " pdtoken.h 1.24 2003/07/15 07:40:00 dds Exp $",
"$" "Id:" " pltoken.cpp 1.10 2003/06/01 08:54:27 dds Exp $",
"$" "Id:" " pltoken.h 1.25 2003/06/19 11:11:01 dds Exp $",
"$" "Id:" " ptoken.cpp 1.9 2003/06/01 08:55:15 dds Exp $",
"$" "Id:" " ptoken.h 1.9 2001/09/10 12:17:32 dds Exp $",
"$" "Id:" " simple_cpp.cpp 1.14 2002/10/03 10:54:01 dds Exp $",
"$" "Id:" " stab.cpp 1.24 2003/08/03 16:12:11 dds Exp $",
"$" "Id:" " stab.h 1.16 2003/08/03 16:12:11 dds Exp $",
"$" "Id:" " tchar.cpp 1.12 2003/06/01 08:56:40 dds Exp $",
"$" "Id:" " tchar.h 1.5 2002/12/26 12:46:24 dds Exp $",
"$" "Id:" " tclfuns.cpp 1.7 2002/09/17 10:53:02 dds Exp $",
"$" "Id:" " token.cpp 1.15 2003/06/01 08:56:40 dds Exp $",
"$" "Id:" " token.h 1.9 2002/12/26 12:46:24 dds Exp $",
"$" "Id:" " tokid.cpp 1.21 2003/07/29 21:31:14 dds Exp $",
"$" "Id:" " tokid.h 1.16 2003/07/29 21:31:14 dds Exp $",
"$" "Id:" " tokmap.cpp 1.3 2002/09/17 10:53:02 dds Exp $",
"$" "Id:" " tokmap.h 1.1 2001/08/15 18:08:00 dds Exp $",
"$" "Id:" " tokname.pl 1.6 2003/06/02 13:55:09 dds Exp $",
"$" "Id:" " type.cpp 1.31 2003/08/06 17:12:03 dds Exp $",
"$" "Id:" " type.h 1.26 2003/08/06 17:12:03 dds Exp $",
"$" "Id:" " type2.h 1.14 2003/08/06 17:12:03 dds Exp $",
"$" "Id:" " webmap.cpp 1.20 2002/10/07 20:13:59 dds Exp $",
"$" "Id:" " webmap.cpp 1.20 2002/10/07 20:13:59 dds Exp $",
"$" "Id:" " workdb.cpp 1.10 2002/10/07 20:13:59 dds Exp $",
"$" "Id:" " ytoken.h 1.6 2003/08/03 16:12:11 dds Exp $",
"$" "Id:" " prjcomp.pl 1.12 2003/07/08 08:48:12 dds Exp $",
"$" "Id:" " version.h 1.3 2003/06/04 18:37:03 dds Exp $",
"$" "Id:" " getopt.c 1.2 2003/07/07 23:18:17 dds Exp $",
"$" "Id:" " getopt.h 1.2 2003/07/07 23:08:25 dds Exp $",
0 };
