// This file is generated by kconfig_compiler from phpsettings.kcfg.
// All changes you do to this file will be lost.
#ifndef PHPSETTINGS_H
#define PHPSETTINGS_H

#include <kconfigskeleton.h>

class PHPSettings : public KConfigSkeleton
{
  public:
    PHPSettings();

    ~PHPSettings();

    void setDefaultDebugger(QString name)
    {
      mDefaultDebugger = name;
    }

    QString defaultDebugger() const
    {
      return mDefaultDebugger;
    }

  protected:

    // PHP Debugger
    QString mDefaultDebugger;

  private:
};

#endif
