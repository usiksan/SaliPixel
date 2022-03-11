#ifndef SPCMDLIST_H
#define SPCMDLIST_H

#include "SpCmd.h"

class SpCmdList
  {
    int          mWidth;
    int          mHeight;
    SpCmdPtrList mObjects;

    bool         mDirty;
  public:
    SpCmdList();
    ~SpCmdList();

    bool isDirty() const { return mDirty; }

    void clear();

    void setup( int w, int h );

    void append( SpCmdPtr cmd );

    void undo();

    void forEach( std::function<void (SpCmd *ptr)> fun );

    void paint( SpImage &im ) const;

    void parsePoints( std::function<void (QPoint &p)> parser );

    int  width() const { return mWidth; }

    int  height() const { return mHeight; }

    bool fileSave( const QString &path );

    bool fileLoad( const QString &path );
  };

#endif // SPCMDLIST_H
