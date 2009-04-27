/*
 * gnote
 *
 * Copyright (C) 2009 Hubert Figuiere
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */




#ifndef __ADDINMANAGER_HPP__
#define __ADDINMANAGER_HPP__

#include <list>
#include <map>
#include <string>

#include <sigc++/signal.h>

#include "sharp/modulemanager.hpp"
#include "note.hpp"
#include "noteaddin.hpp"

namespace gnote {

class ApplicationAddin;
class PreferenceTabAddin;
class AddinPreferenceFactoryBase;


class AddinManager
{
public:
  AddinManager(const std::string & conf_dir);
  ~AddinManager();

  void load_addins_for_note(const Note::Ptr &);
  void get_application_addins(std::list<ApplicationAddin*> &) const;
  void get_preference_tab_addins(std::list<PreferenceTabAddin *> &) const;

  const sharp::ModuleList & get_modules() const
    { 
      return m_module_manager.get_modules(); 
    }

  Gtk::Widget * create_addin_preference_widget(const std::string & id);

  sigc::signal<void> & signal_application_addin_list_changed();
private:

  void initialize_sharp_addins();
    
  const std::string m_gnote_conf_dir;
  sharp::ModuleManager m_module_manager;
  /// Key = TypeExtensionNode.Id
  typedef std::map<std::string, ApplicationAddin*> AppAddinMap;
  AppAddinMap                               m_app_addins;
  typedef std::map<Note::Ptr, std::list<NoteAddin*> > NoteAddinMap;
  NoteAddinMap                              m_note_addins;
  /// Key = TypeExtensionNode.Id
  /// the iface factory is not owned by the manager.
  /// TODO: make sure it is removed if the dynamic module is unloaded.
  typedef std::map<std::string, sharp::IfaceFactoryBase*> IdInfoMap;
  IdInfoMap                                m_note_addin_infos;
  typedef std::map<std::string, PreferenceTabAddin*> IdPrefTabAddinMap;
  IdPrefTabAddinMap                        m_pref_tab_addins;
  typedef std::map<std::string, AddinPreferenceFactoryBase*> IdAddinPrefsMap;
  IdAddinPrefsMap                          m_addin_prefs;
  sigc::signal<void>         m_application_addin_list_changed;
};

}

#endif

