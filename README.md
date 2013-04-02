# Protoeditor

Project homepage: http://protoeditor.sourceforge.net

## About:

  Protoeditor is a small KDE text editor developed for debugging scripts
  interactively. The goal is to provide a simple editor supporting a variety
  of debuggers for different languages. Currently, it supports the following
  languages and debuggers:

  PHP:
   - DBG debugger (free version 2.13.1) at http://dd.cron.ru/dbg/
   - Xdebug (tested with CVS version 2.0.0beta3-dev).
   - Gubed 0.2.2

  Perl:
   - DBGp debugger, shipped in this package. It can also be
     found at ftp://ftp.activestate.com

  Python
   - DBGp debugger, shipped in this package. It can also be
     found at ftp://ftp.activestate.com

  Protoeditor uses katepart as the text editor, so all the functionalities of
  a _good_ editor are present (highlights, folding marks, etc, etc, etc) wich
  makes the debug experience more pratical.

  Besides the editor, it supports common debugger features like: steps,
  watches, backtrace, breakpoints, etc. Other features depend on what the
  debuggers supports.

  Note: The libraries distributed with this package can be found at data/libs
        directory.

## Requirements:

  * KDE 3.2 + should be fine (if not, let me know :)
  * For local debug, you need an interpreter (ie. PHP, Perl, etc) and, at
    least, one debugger installed in your system.  For remote debug, you need
    the remote system to be properly installed (webserver + debugger module +
    additional configuration).

## Configuration and Use

  See Protoeditor manual for a description of the settings and features
  Protoeditor provides (execute Protoeditor and press F1 or Menu "Help" ->
  "Protoeditor's Handbook").

  For a walk through on installing and configuring the debuggers and
  Protoeditor, see the "Tutorial" section on Protoeditor's homepage.

## Debugger Configuration

### PHP

    For Xdebug and DBG, check you phpinfo() if they were successfuly
    installed.

    For details about DBG installation, check the DBG site:
      http://dd.cron.ru

    For details about Xdebug installation, check the Xdebug site:
      http://www.xdebug.org

    For details about Gubed installation, check the Gubed site:
      http://gubed.sourceforge.net

### Perl and Python

    There is no extra configuration needed to start debugging Perl/Python
    scripts locally. Protoeditor installs automatically the debuggers in it's
    data directory (usually /opt/kde/share/apps/protoeditor/libs) so it
    doesn't conflict with your system library.

    To debug remotelly, you will need to copy the DBGp debugger library to the
    server host and configure the webserver. You might want to check "Enable
    JIT" on Protoeditor language settings as well.

#### Remote debugging Perl

    If the remote server is the localhost, and you are using Apache, you could
    add the following to httpd.conf (assuming mod_env is installed and DBGp is
    in the default directory):

          SetEnv PERL5LIB "/opt/kde/share/apps/protoeditor/libs/perl/"
          SetEnv PERLDB_OPTS "RemotePort=localhost:9001"

    Then, restarting the server and settings "perl -d" to the shebang in the
    cgi-script (ie. "#!/usr/bin/perl -d") should be enough.


    Detailed information can be found at:
    http://aspn.activestate.com/ASPN/docs/Komodo/3.5/komodo-doc-debugperl.html

#### Remote debugging Python

    So far, I haven't tested remote debugging with Python DBGp.  Instructions
    for such can be found at:

    http://aspn.activestate.com/ASPN/docs/Komodo/3.5/komodo-doc-debugpython.html

## Protoeditor configuration

  Check your debugger options on Protoeditor settings. Most of them are self
  explanatory, but I'll give some hints ;)

  In the language tabs:

    The "<Language> command" specifies the path for the interpreter binary.
    Togueter with the "External console" settings in "External Application",
    it is used to execute/debug scripts locally using a console application,
    if desired.

    The "Default debugger" chosen is the one to be used on local debugging
    sessions, when no site is currently selected.

    Every debugger has a JIT option. If enabled, Protoeditor will listen on
    the given port while the application is running. Otherwise, it will only
    listen to the port when a debug session is active.

    In "External Applications" you can select a browser to use while debugging
    remote scripts and a console to execute/debug the scripts locally, using
    the PHP binary.

### Sites

    From version 0.6, Protoeditor supports different settings for remote/local
    directory mapping. On other IDE's this is simply the configuration for a
    given project. Since Protoeditor is not project centric, it uses "Site"
    configuration to figure how to access the HTTP server, how to map the
    paths of the scripts and which debugger it uses.  Each site has the
    following entries:

      -Site name        : a simple name to identify this site.
      -URL              : the URL of the http server.
      -Remote base dir  : the remote directory of the site.
      -Local base dir   : the local directory of the site.
      -Default file     : the default script to be debugged when this site is
                          selected.
      -Debugger         : the debugger for this site.

    Many Sites can be registered, and additional directory mappings added.
    The Sites are selected through the combo box on the main window toolbar or
    in the main menu. Also there is a default "-- Local --", wich is used for
    local debug since it doesn't need a directory mapping, URL, etc.

    When starting the debugger for a remote session, it will make an HTTP
    request directly or use one of the browsers chosen from "External
    Applications" settings. The request uses the Site's host:port and the
    given directories to map file paths from remote to local and vice-versa.
    If the Site has a "default file", it will be opened automatically (or
    activated, if already opened), otherwise, Protoeditor will ask you to open
    a file.

    Example of a local Site:

    Site name       : home
    URL             : http://192.168.0.1:8080
    Remote base dir : /var/www/htdocs
    Local base dir  : /usr/apache/htdocs/phpsite
    Default file    : /usr/apache/htdocs/phpsite/index.php
    Debugger        : PHP DBG


## Kate Plugin

    Protoeditor can be build as a stand alone application or as Kate plugin.
    To build the Kate plugin, execute the configure script with the option
    "--enable-kate-plugin":

    ./configure --enable-kate-plugin
    make
    make install

    This should install the icons and perl/python DBGp libs in the kate data
    directory (such as /opt/kde/share/apps/kate) and the plugin itself.

    Now, run Kate and, in the plugin settings, enable the "Kate script
    debugger".  Two more toolbars should appear: the debugger toolbar and the
    argument toolbar.  Also, the menu "Script" and the debugger tabs will be
    added to the user interface.

--
Thiago Silva <thiago@metareload.com>
