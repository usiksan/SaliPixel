#include "SpCmdList.h"


#include <QFile>
#include <QByteArray>

SpCmdList::SpCmdList() :
  mWidth(32),
  mHeight(32),
  mDirty(false)
  {

  }

SpCmdList::~SpCmdList()
  {
  clear();
  }

void SpCmdList::clear()
  {
  qDeleteAll(mObjects);
  mObjects.clear();
  mDirty = false;
  }

void SpCmdList::setup(int w, int h)
  {
  mWidth = w;
  mHeight = h;
  clear();
  }

void SpCmdList::append(SpCmdPtr cmd)
  {
  if( cmd != nullptr ) {
    mObjects.append( cmd );
    mDirty = true;
    }
  }

void SpCmdList::undo()
  {
  if( mObjects.count() ) {
    delete mObjects.last();
    mObjects.removeLast();
    mDirty = true;
    }
  }



void SpCmdList::forEach(std::function<void (SpCmd *)> fun)
  {
  for( auto ptr : qAsConst(mObjects) )
    fun( ptr );
  }



void SpCmdList::paint(SpImage &im) const
  {
  if( im.width() != mWidth || im.height() != mHeight )
    im.resize( mWidth, mHeight );
  im.clear();
  for( auto ptr : qAsConst(mObjects) )
    ptr->paint( im );
  }



void SpCmdList::parsePoints(std::function<void (QPoint &)> parser)
  {
  for( auto ptr : qAsConst(mObjects) )
    ptr->parsePoints( parser );
  }



bool SpCmdList::fileSave(const QString &path)
  {
  QFile file(path);
  if( file.open(QIODevice::WriteOnly) ) {
    SvJsonWriter js;
    js.jsonInt( "width", mWidth );
    js.jsonInt( "height", mHeight );
    js.jsonListPtr( "command", mObjects );
    file.write( svJsonObjectToByteArray(js.object()) );
    mDirty = false;
    }
  return false;
  }

bool SpCmdList::fileLoad(const QString &path)
  {
  QFile file(path);
  if( file.open(QIODevice::ReadOnly) ) {
    mDirty = false;
    QJsonObject obj = svJsonObjectFromByteArray(file.readAll());
    SvJsonReader js( obj );
    js.jsonInt( "width", mWidth );
    js.jsonInt( "height", mHeight );
    js.jsonListPtr( "command", mObjects );
    return true;
    }
  return false;
  }
