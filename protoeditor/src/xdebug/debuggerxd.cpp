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
 
#include "debuggerxd.h"
#include "xdnet.h"
#include "xdsettings.h"

#include "debuggerbreakpoint.h"
#include "debuggerstack.h"
#include "debuggermanager.h"
#include "protoeditorsettings.h"

#include "phpvariable.h"

#include <kdebug.h>
#include <klocale.h>

DebuggerXD::DebuggerXD(DebuggerManager* manager)
  : AbstractDebugger(manager), m_name("Xdebug"), m_isRunning(false), m_isJITActive(false),
    m_xdSettings(0)
{
  m_xdSettings = new XDSettings(m_name);

  ProtoeditorSettings::self()->registerDebuggerSettings(m_xdSettings, m_name);

  connect(ProtoeditorSettings::self(), SIGNAL(sigSettingsChanged()),
          this, SLOT(slotSettingsChanged()));

  m_net = new XDNet(this);
  connect(m_net, SIGNAL(sigXDStarted()), this, SLOT(slotXDStarted()));
  connect(m_net, SIGNAL(sigXDClosed()), this, SLOT(slotXDClosed()));
  connect(m_net, SIGNAL(sigError(const QString&)), this, SLOT(slotInternalError(const QString&)));
  connect(m_net, SIGNAL(sigStepDone()), this, SLOT(slotStepDone()));
  //connect(m_net, SIGNAL(sigBreakpoint()), this, SLOT(slotBreakpoint()));  
}

DebuggerXD::~DebuggerXD()
{
  delete m_xdSettings;
  //  delete m_profileDialog;
  delete m_net;
}


QString DebuggerXD::name() const
{
  return m_name;
}

bool DebuggerXD::isRunning() const
{
  return m_isRunning;
}

void DebuggerXD::init()
{
  slotSettingsChanged();
}

void DebuggerXD::run(const QString& filepath)
{
  SiteSettings* site  = ProtoeditorSettings::self()->currentSiteSettings();

  //dbgint sessionid = kapp->random();

  if(!m_isJITActive && !startJIT())
  {
    return;
  }

  m_net->startDebugging(filepath, site);
}

void DebuggerXD::continueExecution()
{
  m_net->requestContinue();
}

void DebuggerXD::stop()
{
  m_net->requestStop();
}

void DebuggerXD::stepInto()
{
  m_net->requestStepInto();
}

void DebuggerXD::stepOver()
{
  m_net->requestStepOver();
}

void DebuggerXD::stepOut()
{
  m_net->requestStepOut();
}

void DebuggerXD::addBreakpoints(const QValueList<DebuggerBreakpoint*>& bps)
{
  if(isRunning())
  {
    QValueList<DebuggerBreakpoint*>::const_iterator it;
    for(it = bps.begin(); it != bps.end(); ++it)
    {
      m_net->requestBreakpoint(*it);
    }
  }  
}

void DebuggerXD::addBreakpoint(DebuggerBreakpoint* bp)
{
  if(isRunning())
  {
    m_net->requestBreakpoint(bp);
  }
}

void DebuggerXD::changeBreakpoint(DebuggerBreakpoint*)
{
}

void DebuggerXD::removeBreakpoint(DebuggerBreakpoint*)
{
}

void DebuggerXD::changeCurrentExecutionPoint(DebuggerExecutionPoint* execPoint)
{
  m_currentExecutionPointID = execPoint->id();
  if(isRunning())
  {
    m_net->requestVariables(m_currentExecutionPointID, XDNet::LOCAL_SCOPE);
  }
}

void DebuggerXD::modifyVariable(Variable* var, DebuggerExecutionPoint* execPoint)
{
  if(isRunning())
  {
    QString name  =  var->compositeName();
    QString value =  var->value()->toString();

    if(value.isEmpty()) value = "null";

    m_net->requestWatch(name + "=" + value, execPoint->id());

    //reload variables (global/local/watches) to get the new value.
    requestVars();
/*    m_net->requestVariables(m_globalExecutionPointID, true);
    m_net->requestVariables(m_currentExecutionPointID, false);
    requestWatches(m_currentExecutionPointID);*/
  }
}

void DebuggerXD::addWatch(const QString& expression)
{
  m_wathcesList.append(expression);

  if(isRunning())
  {
    m_net->requestWatch(expression);
  }
  else
  {
    PHPVariable* var = new PHPVariable(expression);
    PHPScalarValue* value = new PHPScalarValue(var);
    var->setValue(value);
    updateWatch(var);
  }  
}

void DebuggerXD::removeWatch(const QString&)
{
}

void DebuggerXD::profile(const QString&)
{
}

void DebuggerXD::slotSettingsChanged()
{
  if(m_xdSettings->enableJIT())
  {
    startJIT();
  }
  else
  {
    stopJIT();
  }
}

bool DebuggerXD::startJIT()
{
  if(!m_isJITActive)
  {

    if(m_net->startListener(m_xdSettings->listenPort()))
    {
      m_isJITActive = true;
      kdDebug() << "Xdebug: Listening on port " << m_xdSettings->listenPort() << endl;
    }
    else
    {
      emit sigInternalError(i18n("Unable to listen on port: %1").arg(
          m_xdSettings->listenPort()));
      return false;
    }
  }

  return true;  
}

void DebuggerXD::stopJIT()
{
  if(m_isRunning)
  {
    m_net->requestStop();
  }

  m_net->stopListener();
  m_isJITActive = false;  
}

void DebuggerXD::slotXDStarted()
{
  m_isRunning = true;
  emit sigDebugStarted(this);
}

void DebuggerXD::slotXDClosed()
{
  m_isRunning = false;
  if(!m_xdSettings->enableJIT())
  {
    stopJIT();
  }

  emit sigDebugEnded();
}

void DebuggerXD::requestVars()
{
  requestWatches(m_currentExecutionPointID);
  m_net->requestVariables(m_globalExecutionPointID, XDNet::GLOBAL_SCOPE);
  m_net->requestVariables(m_currentExecutionPointID, XDNet::LOCAL_SCOPE);
}

void DebuggerXD::slotStepDone()
{
  requestVars();
  emit sigStepDone();
}

void DebuggerXD::slotInternalError(const QString& msg)
{
  emit sigInternalError(msg);
}

void DebuggerXD::requestWatches(int ctx_id)
{
  if(isRunning())
  {
    QValueList<QString>::iterator it;
    for(it = m_wathcesList.begin(); it != m_wathcesList.end(); ++it)
    {
      m_net->requestWatch(*it, ctx_id);
    }
  }
}

void DebuggerXD::updateStack(DebuggerStack* stack)
{
  m_currentExecutionPointID = stack->topExecutionPoint()->id();
  m_globalExecutionPointID  = stack->bottomExecutionPoint()->id();
  manager()->updateStack(stack);
}

void DebuggerXD::updateVariables(VariablesList_t* array, bool isGlobal)
{
  if(isGlobal)
  {
    manager()->updateGlobalVars(array);
  }
  else
  {
    manager()->updateLocalVars(array);
  }
}

void DebuggerXD::updateWatch(Variable* var)
{
  if(m_wathcesList.find(var->name()) == m_wathcesList.end())
  {
    //This watch is not on our list.
    //It might happen whe the user modifies the value of a variable (ie. "$var=123").
    //Since we request a watch expression "$var=123", we receive "$var=123" as the name
    //of the variable (str) and we don't want to add something like that to the watchlist
    //everytime the user modifies a variable, right? :)
    return;
  }
  
  manager()->updateWatch(var);
}

void DebuggerXD::updateBreakpoint(int id, const QString& filePath, int line, const QString& state, int hitcount, int skiphits,
                        const QString& condition)
{
  int status;
  if(state == "enabled")
  {
    status = DebuggerBreakpoint::ENABLED;
  }
  
  /*
  switch(state)
  {
    case BPS_DISABLED:
      status = DebuggerBreakpoint::DISABLED;
      break;
    case BPS_UNRESOLVED:
    default:
      status = DebuggerBreakpoint::UNRESOLVED;
      break;
  }
  */
  DebuggerBreakpoint* bp = new DebuggerBreakpoint(id, filePath, line, status, condition, hitcount, skiphits);
  manager()->updateBreakpoint(bp);  
}

// void DebuggerXD::addOutput(const QString& msg)
// {
//   manager()->updateOutput(msg);
// }
#include "debuggerxd.moc"
