/***************************************************************************
 *   Copyright (C) 2005 by Thiago Silva                                    *
 *   thiago.silva@kdemail.net                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef SITESETTINGSWIDGET_H
#define SITESETTINGSWIDGET_H

#include <qwidget.h>
#include <kurl.h>

class KPushButton;
class QListBox;
class QListBoxItem;
class SiteSettings;

class SiteSettingsWidget : public QWidget
{
  Q_OBJECT
public:
  SiteSettingsWidget(QWidget *parent = 0, const char *name = 0);
  ~SiteSettingsWidget();

  KPushButton   *m_btAdd;
  KPushButton   *m_btModify;
  KPushButton   *m_btRemove;

  QListBox      *m_sitesListBox;

  void populate();
  void updateSettings();
private slots:
  void slotAdd();
  void slotModify();
  void slotRemove();
  void slotListChanged(int);
  void slotListDoubleClicked(QListBoxItem*);

private:
  void addSite(const QString& name, const KURL& url,
               const KURL& remoteBaseDir, const KURL& localBaseDir,
               const KURL& defaultFile, const QString& debuggerClinet);

  void modifySite(const QString& name, const KURL& url,
                  const KURL& remoteBaseDir, const KURL& localBaseDir,
                  const KURL& defaultFile, const QString& debuggerClinet);

  class Site
  {
  public:
    Site() {};
    Site(const QString& n, const KURL& u,
         const KURL& r, const KURL& l, const KURL& d, const QString& c)
        : name(n), url(u), remoteBaseDir(r), localBaseDir(l), defaultFile(d),
          debuggerClient(c){}
    ~Site() {}

    QString name;
    KURL    url;
    KURL    remoteBaseDir;
    KURL    localBaseDir;
    KURL    defaultFile;
    QString debuggerClient;
  };

  QMap<QString, Site> m_siteMap;
};

#endif
