/*
Project "Combine vector-pixel graphic editor"

Author
  Sibilev Alexander S.

Web
  www.saliLab.com
  www.saliLab.ru

Description
  SaliPixel configuration and history

History
  27.02.2022 v0.1  created
  05.02.2022 v0.3  global refactor
                   file now saved as command list i.e. source form,
                     it is possible open and change previously created files
                   png saved as export
             v0.4  Fix: file new not clear previous file name
                        no export to png
             v0.5  Append vector edit service
  10.02.2022 v0.6  Refactor mode to possibility insert more than one objects into the drawing
                   Remove triangle as single object and replace it with three line objects
                   Append parallelogramm and round rect modes
*/
#ifndef SPCONFIG_H
#define SPCONFIG_H

//Do'nt change this name
#define SP_AUTHOR                    "Alexander Sibilev"
#define SP_ORGANIZATION_NAME         "SaliLAB"
#define SP_ORGANIZATION_DOMAIN       "http://SaliLab.com/"
#define SP_APPLICATION_NAME          "SaliPixel"

//Version definition
#define SP_VERSION_MAJOR             0
#define SP_VERSION_MINOR             6

#define SP_EXTENSION                 ".salipixel"

//Settings key names
#define KEY_LANGUAGE                 "Language"

#endif // SPCONFIG_H
