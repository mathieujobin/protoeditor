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
#include "dbgsettingswidget.h"

#include <qcheckbox.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qgroupbox.h>

#include "dbgsettings.h"

DBGSettingsWidget::DBGSettingsWidget(DBGSettings* settings, QWidget *parent, const char *name)
    : QWidget(parent, name) {

  QVBoxLayout *mainLayout = new QVBoxLayout(this, 10, 16);

  QGroupBox* groupbox = new QGroupBox(this);
  groupbox->setTitle("DBG Options");
  groupbox->setColumnLayout(0, Qt::Vertical );
  QVBoxLayout* groupboxLayout = new QVBoxLayout(groupbox->layout());
  groupboxLayout->setAlignment(Qt::AlignTop);

  QGridLayout* grid = new QGridLayout(0, 3, 2, 3, 6);

  m_ckBreakOnLoad = new QCheckBox(groupbox);
  m_ckBreakOnLoad->setText("Break on load");
  grid->addWidget(m_ckBreakOnLoad, 0, 0);

  m_ckSendErrors = new QCheckBox(groupbox);
  m_ckSendErrors->setText("Send erros");
  grid->addWidget(m_ckSendErrors, 1, 0);


  m_ckSendLogs = new QCheckBox(groupbox);
  m_ckSendLogs->setText("Send logs");
  grid->addWidget(m_ckSendLogs, 2, 0);


  m_ckSendOutput = new QCheckBox(groupbox);
  m_ckSendOutput->setText("Send output");
  grid->addWidget(m_ckSendOutput, 0, 1);

  m_ckSendDetailedOutput = new QCheckBox(groupbox);
  m_ckSendDetailedOutput->setText("Send Detailed Output");
  grid->addWidget(m_ckSendDetailedOutput, 1, 1);

  groupboxLayout->addLayout(grid);

  mainLayout->addWidget(groupbox);

  QHBoxLayout* portbox = new QHBoxLayout(0, -1, 16);

  QLabel* lblistenPort = new QLabel(this);
  lblistenPort->setText("Listen on port:");
  portbox->addWidget(lblistenPort);

  m_spListenPort = new QSpinBox(this);
  m_spListenPort->setMaxValue(99999);
  portbox->addWidget(m_spListenPort);
  portbox->addItem(new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum ));

  mainLayout->addLayout(portbox);

  QHBoxLayout* jitbox = new QHBoxLayout(0, -1, 16);

  m_ckEnableJIT = new QCheckBox(this);
  m_ckEnableJIT->setText("Enable JIT");
  jitbox->addWidget(m_ckEnableJIT);
  jitbox->addItem(new QSpacerItem( 324, 20, QSizePolicy::Expanding, QSizePolicy::Minimum ));

  mainLayout->addLayout(jitbox);

  mainLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

  loadValues(settings);
}

DBGSettingsWidget::~DBGSettingsWidget() {}

bool DBGSettingsWidget::breakOnLoad()
{
  return m_ckBreakOnLoad->isChecked();
}

bool DBGSettingsWidget::sendErrors()
{
  return m_ckSendErrors->isChecked();
}

bool DBGSettingsWidget::sendLogs()
{
  return m_ckSendLogs->isChecked();
}

bool DBGSettingsWidget::sendOutput()
{
  return m_ckSendOutput->isChecked();
}

bool DBGSettingsWidget::sendDetailedOutput()
{
  return m_ckSendDetailedOutput->isChecked();
}

int DBGSettingsWidget::listenPort()
{
  return m_spListenPort->value();
}

bool DBGSettingsWidget::enableJIT()
{
  return m_ckEnableJIT->isChecked();
}


void DBGSettingsWidget::loadValues(DBGSettings* settings)
{
  m_ckBreakOnLoad->setChecked(settings->breakOnLoad());
  m_ckSendErrors->setChecked(settings->sendErrors());
  m_ckSendLogs->setChecked(settings->sendLogs());
  m_ckSendOutput->setChecked(settings->sendOutput());
  m_ckSendDetailedOutput->setChecked(settings->sendDetailedOutput());

  m_spListenPort->setValue(settings->listenPort());
  m_ckEnableJIT->setChecked(settings->enableJIT());
}

#include "dbgsettingswidget.moc"
