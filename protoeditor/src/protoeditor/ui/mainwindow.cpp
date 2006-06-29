/***************************************************************************
 *   Copyright (C) 2004-2006 by Thiago Silva                               *
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

#include "mainwindow.h"
#include "editorui.h"
#include "debuggerui.h"
#include "statusbarwidget.h"

#include "protoeditor.h"
#include "configdlg.h"

#include <kapplication.h>

#include <kmessagebox.h>
#include <kcombobox.h>
#include <kconfig.h>
#include <kkeydialog.h>
#include <kedittoolbar.h>

#include <qlayout.h>
#include <qsplitter.h>

#include <ktexteditor/view.h> 
#include <kpopupmenu.h>

#include <klocale.h>
#include <kaction.h>

#include "protoeditorsettings.h"
#include <qaction.h>

MainWindow::MainWindow(QWidget* parent, const char* name, WFlags fl)
    : KParts::MainWindow(parent, name, fl)
{
  if(!name) 
  { 
    setName("MainWindow"); 
  }

  createWidgets();  

  setupActions();

  createGUI(0);

  stateChanged("init");

  resize( QSize(633, 533).expandedTo(minimumSizeHint()) );
  clearWState(WState_Polished);  
}

MainWindow::~MainWindow()
{
}

void MainWindow::createWidgets()
{
  setCentralWidget(new QWidget(this));
  QVBoxLayout* mainFormBaseLayout = new QVBoxLayout(centralWidget(), 1, 1);

  QSplitter* splitter = new QSplitter(centralWidget());
  splitter->setOrientation( Qt::Vertical  );
  mainFormBaseLayout->addWidget(splitter);

  m_editorUI = new EditorUI(splitter, this);
  splitter->setCollapsible(m_editorUI, false);
  splitter->setOpaqueResize(true); 
  
  m_debuggerUI = new DebuggerUI(splitter);
  splitter->setCollapsible(m_debuggerUI, false);
  m_debuggerUI->setGeometry(0,0,0,height()/15);

  m_statusBar = new StatusBarWidget(this);

  m_cbArguments = new KHistoryCombo(true, this);
}

void MainWindow::setupActions()
{
  //menu "file"
  KStdAction::openNew(Protoeditor::self(), SLOT(slotAcNewFile()), actionCollection());
  KAction* open = KStdAction::open(Protoeditor::self(), SLOT(slotAcOpenFile()), actionCollection());

  m_actionRecent = KStdAction::openRecent(Protoeditor::self(), SLOT(slotAcFileRecent(const KURL&)), actionCollection());
  m_actionRecent->loadEntries(kapp->config());
  connect(m_actionRecent, SIGNAL(activated()), open, SLOT(activate()));

  KStdAction::save(Protoeditor::self(), SLOT(slotAcSaveCurrentFile()), actionCollection());
  KStdAction::saveAs(Protoeditor::self(), SLOT(slotAcSaveCurrentFileAs()), actionCollection());


  KStdAction::close(Protoeditor::self(), SLOT(slotAcCloseFile()), actionCollection());

  (void)new KAction(i18n("Close All"), 0, Protoeditor::self(), SLOT(slotAcCloseAllFiles()), actionCollection(), "file_close_all");

  KStdAction::quit(Protoeditor::self(), SLOT(slotAcQuit()), actionCollection());
  

  //menu "script"
  m_siteAction     = new KSelectAction(i18n("Site"), 0, actionCollection(), "site_selection");
  m_siteAction->setComboWidth(150);

  connect(m_siteAction, SIGNAL(activated(const QString&)),
      ProtoeditorSettings::self(), SLOT(slotCurrentSiteChanged(const QString&)));

  m_activeScriptAction = new KToggleAction(i18n("Use Current Script"), "attach", 0, actionCollection(), "use_current_script");

  m_executeAction = new KToolBarPopupAction(i18n("Execute in Console"), "gear", "Shift+F9", 
                      this, SLOT(slotAcExecuteScript()), actionCollection(), "script_execute");

  connect(m_executeAction->popupMenu(), SIGNAL(activated(int)), this, SLOT(slotAcExecuteScript(int)));


  connect(this, SIGNAL(sigExecuteScript(const QString&)), Protoeditor::self(),
      SLOT(slotAcExecuteScript(const QString&)));

  m_debugAction = new KToolBarPopupAction(i18n("Start Debug"), "dbgstart", "F9", this,
                    SLOT(slotAcDebugStart()), actionCollection(), "debug_start");

  connect(m_debugAction->popupMenu(), SIGNAL(activated(int)), this, SLOT(slotAcDebugStart(int)));

  connect(this, SIGNAL(sigDebugScript(const QString&)), Protoeditor::self(),
      SLOT(slotAcDebugStart(const QString&)));

  (void)new KAction(i18n("Stop Debug"), "stop", "Escape", Protoeditor::self(),
                    SLOT(slotAcDebugStop()), actionCollection(), "debug_stop");

  (void)new KAction(i18n("Run to Cursor"), "dbgrunto", 0, Protoeditor::self(),
                    SLOT(slotAcDebugRunToCursor()), actionCollection(), "debug_run_to_cursor");


  (void)new KAction(i18n("Step Over"), "dbgnext", "F10", Protoeditor::self(),
                    SLOT(slotAcDebugStepOver()), actionCollection(), "debug_step_over");

  (void)new KAction(i18n("Step Into"), "dbgstep", "F11", Protoeditor::self(),
                    SLOT(slotAcDebugStepInto()), actionCollection(), "debug_step_into");


  (void)new KAction(i18n("Step Out"), "dbgstepout", "F12", Protoeditor::self(),
                    SLOT(slotAcDebugStepOut()), actionCollection(), "debug_step_out");

 (void)new KAction(i18n("Profile (DBG only)"), "math_sum", "Alt+P", 
      Protoeditor::self(), SLOT(slotProfile()), actionCollection(), "script_profile");
  
  (void)new KAction(i18n("Toggle Breakpoint"), "activebreakpoint", "Alt+B", Protoeditor::self(),
                    SLOT(slotAcDebugToggleBp()), actionCollection(), "debug_toggle_bp");


  KWidgetAction* comboAction = new KWidgetAction(argumentCombo(), i18n("Argument Bar "), 0,
                  0, 0, actionCollection(), "argument_combobox" );

  comboAction->setShortcutConfigurable(false);
  comboAction->setAutoSized(true);

  (void)new KAction(i18n("Clear Arguments"), "clear_left", 0, argumentCombo(),
                    SLOT(clearEdit()), actionCollection(), "argument_clear");

  (void)new KWidgetAction(new QLabel(i18n("Arguments: "), this), i18n("Arguments "), "Alt+a", 
      this, SLOT(slotAcFocusArgumentBar()), actionCollection(), "argument_label" );
  

  //menu "settings"
  KStdAction::keyBindings(this, SLOT(slotAcEditKeys()), actionCollection());
  KStdAction::configureToolbars(this, SLOT(slotAcEditToolbars()), actionCollection());
  KStdAction::preferences(this, SLOT(slotAcShowSettings()), actionCollection(), "settings_protoeditor");


  setStandardToolBarMenuEnabled(true);
}

EditorUI* MainWindow::editorUI()
{
  return m_editorUI;
}

DebuggerUI* MainWindow::debuggerUI()
{
  return m_debuggerUI;
}

StatusBarWidget*  MainWindow::statusBar()
{
  return m_statusBar;
}

KHistoryCombo* MainWindow::argumentCombo()
{
  return m_cbArguments;
}

void MainWindow::actionStateChanged(const QString& state)
{
  stateChanged(state);
}

void MainWindow::saveArgumentList()
{
  QString arg = argumentCombo()->currentText();
  if(!arg.isEmpty()) 
  {
    argumentCombo()->addToHistory(arg);
  }
}

QString MainWindow::currentSiteName()
{
  return m_siteAction->currentText();
}

void MainWindow::setSiteNames(const QStringList& sites)
{
  m_siteAction->setItems(sites);
}

void MainWindow::setCurrentSite(int idx)
{
  m_siteAction->setCurrentItem(idx);
}

void MainWindow::addRecentURL(const KURL& url)
{
  m_actionRecent->addURL(url);
}

void MainWindow::removeRecentURL(const KURL& url)
{
  m_actionRecent->removeURL(url);
}

bool MainWindow::isCurrentScriptActionChecked()
{
  return m_activeScriptAction->isChecked();
}

void MainWindow::saveRecentEntries()
{
  m_actionRecent->saveEntries(kapp->config());
}

void MainWindow::clearLanguages()
{
  m_executeAction->popupMenu()->clear();
  m_debugAction->popupMenu()->clear();
  m_lastLang = QString::null;
}

void MainWindow::addLanguage(const QString& langName)
{
  static int id = 0;
  KPopupMenu *execpopup  = m_executeAction->popupMenu();
  KPopupMenu *debugpopup = m_debugAction->popupMenu();

  execpopup->insertItem(langName, id);
  debugpopup->insertItem(langName, id);

  m_langMap[id++] = langName;

  //get the first language registered as our default language
  if(m_lastLang.isEmpty()) 
  {
    m_lastLang = langName;
  }
}

void MainWindow::showError(const QString& msg) const
{
  KMessageBox::error(0, msg);
}

void MainWindow::showSorry(const QString& msg) const
{
  KMessageBox::sorry(0, msg);
}

void MainWindow::closeEvent(QCloseEvent * e)
{
  if(m_editorUI->closeAllDocuments())
  {
    KMainWindow::closeEvent(e);
  }
}

void MainWindow::slotAcEditKeys()
{
  KKeyDialog dlg;
  dlg.insert(actionCollection());

  if(m_editorUI->count() != 0)
  {
    KTextEditor::View* view  = m_editorUI->currentView();
    if(view)
    {
      dlg.insert(view->actionCollection());
    }
  }

  dlg.configure();
}

void MainWindow::slotAcEditToolbars()
{
  KEditToolbar dlg(guiFactory());
  if (dlg.exec())
  {
    applyMainWindowSettings(KGlobal::config(), autoSaveGroup());
  }
}

void MainWindow::slotAcShowSettings()
{
  ConfigDlg::showDialog();
}

void MainWindow::slotAcFocusArgumentBar()
{
  m_cbArguments->setFocus();
  m_cbArguments->lineEdit()->selectAll();
}


void MainWindow::slotAcDebugStart(int id)
{
  m_lastLang = m_langMap[id];
  emit sigDebugScript(m_lastLang);
}

void MainWindow::slotAcDebugStart()
{
  emit sigDebugScript(m_lastLang);
}

void MainWindow::slotAcExecuteScript(int id)
{
  m_lastLang = m_langMap[id];
  emit sigExecuteScript(m_lastLang);
}

void MainWindow::slotAcExecuteScript()
{
  emit sigExecuteScript(m_lastLang);
}

#include "mainwindow.moc"
