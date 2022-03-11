#include "SpCmd.h"
#include "SpCmdArc.h"
#include "SpCmdAreaMirror.h"
#include "SpCmdAreaMove.h"
#include "SpCmdAreaRectArray.h"
#include "SpCmdAreaRotate.h"
#include "SpCmdAreaRoundArray.h"
#include "SpCmdAreaScale.h"
#include "SpCmdCircle.h"
#include "SpCmdClearCircle.h"
#include "SpCmdClearPoint.h"
#include "SpCmdClearRect.h"
#include "SpCmdFill.h"
#include "SpCmdFillCircle.h"
#include "SpCmdFillRect.h"
#include "SpCmdLine.h"
#include "SpCmdPoint.h"
#include "SpCmdRect.h"
#include "SpCmdImage.h"

SpCmd::SpCmd() :
  mVisible(true)
  {

  }

void SpCmd::jsonWrite(SvJsonWriter &js)
  {
  js.jsonString( "id", id() );
  js.jsonBool( "visible", mVisible );
  js.jsonColor( "color", mColor );
  }

void SpCmd::jsonRead(SvJsonReader &js)
  {
  js.jsonBool( "visible", mVisible );
  js.jsonColor( "color", mColor );
  }

void SpCmd::parsePoints(std::function<void (QPoint &)> parser)
  {
  Q_UNUSED(parser);
  }


SpCmd *SpCmd::build(SvJsonReader &js)
  {
  QString id;
  js.jsonString( "id", id );
  if( id == SP_CMD_ARC )              return new SpCmdArc();
  if( id == SP_CMD_AREA_MIRROR )      return new SpCmdAreaMirror();
  if( id == SP_CMD_AREA_MOVE )        return new SpCmdAreaMove();
  if( id == SP_CMD_AREA_RECT_ARRAY )  return new SpCmdAreaRectArray();
  if( id == SP_CMD_AREA_ROTATE )      return new SpCmdAreaRotate();
  if( id == SP_CMD_AREA_ROUND_ARRAY ) return new SpCmdAreaRoundArray();
  if( id == SP_CMD_AREA_SCALE )       return new SpCmdAreaScale();
  if( id == SP_CMD_CIRCLE )           return new SpCmdCircle();
  if( id == SP_CMD_CLEAR_CIRCLE )     return new SpCmdClearCircle();
  if( id == SP_CMD_CLEAR_POINT )      return new SpCmdClearPoint();
  if( id == SP_CMD_CLEAR_RECT )       return new SpCmdClearRect();
  if( id == SP_CMD_FILL )             return new SpCmdFill();
  if( id == SP_CMD_FILL_CIRCLE )      return new SpCmdFillCircle();
  if( id == SP_CMD_FILL_RECT )        return new SpCmdFillRect();
  if( id == SP_CMD_LINE )             return new SpCmdLine();
  if( id == SP_CMD_POINT )            return new SpCmdPoint();
  if( id == SP_CMD_RECT )             return new SpCmdRect();
  if( id == SP_CMD_IMAGE )            return new SpCmdImage();
  return nullptr;
  }
