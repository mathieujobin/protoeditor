/***************************************************************************
 *   Copyright (C) 2004 by Thiago Silva                                    *
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
#include "sitesettingswidget.h"

#include "sitesettingsdialog.h"

#include "sitesettings.h"
#include "protoeditorsettings.h"

#include <qlayout.h>
#include <qlistbox.h>
#include <qlabel.h>

#include <kpushbutton.h>
#include <kdebug.h>
#include <kmessagebox.h>

SiteSettingsWidget::SiteSettingsWidget(QWidget *parent, const char *name)
    : QWidget(parent, name)
{
  QVBoxLayout* mainLayout = new QVBoxLayout(this, 10, 0);

  QLabel * lbSites = new QLabel(this);
  lbSites->setText("Sites:");
  mainLayout->addWidget(lbSites);

  QVBoxLayout* buttonLayout = new QVBoxLayout(this, 10, 10);

  QHBoxLayout* hlayout = new QHBoxLayout(this, 10, 10);

  m_sitesListBox = new QListBox(this);
  hlayout->addWidget(m_sitesListBox);

  m_btAdd = new KPushButton(this);
  m_btAdd->setText("Add...");
  buttonLayout->addWidget(m_btAdd);

  m_btModify = new KPushButton(this);
  m_btModify->setText("Modify...");
  m_btModify->setEnabled(false);
  buttonLayout->addWidget(m_btModify);

  m_btRemove = new KPushButton(this);
  m_btRemove->setText("Remove");
  m_btRemove->setEnabled(false);
  buttonLayout->addWidget(m_btRemove);
  buttonLayout->addItem(new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding ));

  hlayout->addLayout(buttonLayout);

  mainLayout->addLayout(hlayout);

  connect(m_btAdd, SIGNAL(clicked()), this, SLOT(slotAdd()));
  connect(m_btModify, SIGNAL(clicked()), this, SLOT(slotModify()));
  connect(m_btRemove, SIGNAL(clicked()), this, SLOT(slotRemove()));

  connect(m_sitesListBox, SIGNAL(highlighted(int)),
    this, SLOT(slotListChanged(int)));

  connect(m_sitesListBox, SIGNAL(doubleClicked(QListBoxItem*)),
    this, SLOT(slotListDoubleClicked(QListBoxItem*)));

  loadValues();
}

SiteSettingsWidget::~SiteSettingsWidget()
{}

void SiteSettingsWidget::loadValues()
{
  QValueList<SiteSettings*> list = ProtoeditorSettings::self()->siteSettingsList();
  QValueList<SiteSettings*>::iterator it;
  for(it = list.begin(); it != list.end(); ++it) {
    m_siteMap[(*it)->name()] = (*it);
    m_sitesListBox->insertItem((*it)->name());
  }
}

void SiteSettingsWidget::slotAdd()
{
  SiteSettingsDialog* dialog = new SiteSettingsDialog(this);

  while(dialog->exec() == QDialog::Accepted) {
    if(m_sitesListBox->findItem(dialog->name()) != 0) {
      KMessageBox::sorry(this, QString("Site \"") + dialog->name() + "\" already exists.");
    } else {
      addSite(dialog->name(), dialog->host(), dialog->port(),
              dialog->remoteBaseDir(), dialog->localBaseDir());
      break;
    }
  }

  delete dialog;
}

void SiteSettingsWidget::slotModify()
{
  if(m_sitesListBox->currentItem() == -1) return;

  SiteSettingsDialog* dialog = new SiteSettingsDialog(this);

  SiteSettings* s = m_siteMap[m_sitesListBox->text(m_sitesListBox->currentItem())];

  dialog->populate(s->name(), s->host(), s->port(), s->remoteBaseDir(), s->localBaseDir());
  dialog->setUpdate();
  if(dialog->exec() == QDialog::Accepted) {
    modifySite(dialog->name(), dialog->host(), dialog->port(),
            dialog->remoteBaseDir(), dialog->localBaseDir());
  }
  delete dialog;
}

void SiteSettingsWidget::slotRemove()
{
  if(m_sitesListBox->currentItem() == -1) return;

  m_siteMap.remove(m_sitesListBox->text(m_sitesListBox->currentItem()));
  m_sitesListBox->removeItem(m_sitesListBox->currentItem());
}


void SiteSettingsWidget::slotListChanged(int index)
{
  if(index == -1) {
    m_btModify->setEnabled(false);
    m_btRemove->setEnabled(false);
  } else {
    m_btModify->setEnabled(true);
    m_btRemove->setEnabled(true);
  }
}

void SiteSettingsWidget::slotListDoubleClicked(QListBoxItem*)
{
  slotModify();
}

void SiteSettingsWidget::modifySite(const QString& name, const QString& host, int port,
                                 const QString& remoteBaseDir, const QString& localBaseDir)
{
  SiteSettings* s = m_siteMap[name];
  s->setName(name);
  s->setHost(host);
  s->setPort(port);
  s->setRemoteBaseDir(remoteBaseDir);
  s->setLocalBaseDir(localBaseDir);
  //s->setMatchCase
  //s->setDebuggger
}

void SiteSettingsWidget::addSite(const QString& name, const QString& host, int port,
                                 const QString& remoteBaseDir, const QString& localBaseDir)
{
  SiteSettings* s = new SiteSettings(QString::number(m_sitesListBox->count()));
  s->load(name, host, port, remoteBaseDir, localBaseDir,
    /* TODO: */
    false, "DBG");

  m_siteMap[name] = s;
  m_sitesListBox->insertItem(name);
}

void SiteSettingsWidget::updateSettings()
{
  ProtoeditorSettings::self()->clearSites();

  QMap<QString, SiteSettings*>::Iterator it;
  for(it = m_siteMap.begin(); it != m_siteMap.end(); ++it ) {
    ProtoeditorSettings::self()->addSite(it.data());
  }
}

#include "sitesettingswidget.moc"
