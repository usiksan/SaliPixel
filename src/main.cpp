#include "SpConfig.h"
#include "Win/SpWinMain.h"

#include <QApplication>
#include <QSettings>
#include <QLocale>
#include <QTranslator>
#include <QThread>

int main(int argc, char *argv[])
  {
  //Setups for settings
  QCoreApplication::setOrganizationName(SP_ORGANIZATION_NAME);
  QCoreApplication::setOrganizationDomain(SP_ORGANIZATION_DOMAIN);
  QCoreApplication::setApplicationName(SP_APPLICATION_NAME);

  QApplication a(argc, argv);


  QSettings s;
  if( !s.contains(KEY_LANGUAGE) ) {
    //Language is not assigned yet, assign it

    //Get system language
    QStringList ui = QLocale::system().uiLanguages();
    QString lang;
    if( ui.count() )
      lang = ui.at(0);
    else
      lang = QStringLiteral("en");

    //Assign default language
    s.setValue( KEY_LANGUAGE, lang );
    }


  //Translation system
  QTranslator appTranslator;
  if( appTranslator.load( QString( QCoreApplication::applicationDirPath() + "/lang_%1.qm").arg( s.value( KEY_LANGUAGE ).toString() ) ) )
    a.installTranslator( &appTranslator );



  SpWinMain w;
  w.show();
  return a.exec();
  }
