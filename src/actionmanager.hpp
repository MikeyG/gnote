/*
 * gnote
 *
 * Copyright (C) 2012-2013 Aurimas Cernius
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

#ifndef __ACTIONMANAGER_HPP_
#define __ACTIONMANAGER_HPP_

#include <map>
#include <string>
#include <list>

#include <glibmm/variant.h>
#include <giomm/menu.h>
#include <giomm/simpleaction.h>
#include <gtkmm/action.h>

#include "base/macros.hpp"
#include "iactionmanager.hpp"

namespace gnote {

class ActionManager
  : public IActionManager
{
public:
  ActionManager();

  virtual Glib::RefPtr<Gtk::Action> operator[](const std::string & n) const override
    {
      return find_action_by_name(n);
    }
  void populate_action_groups();
  Glib::RefPtr<Gtk::Action> find_action_by_name(const std::string & n) const;

  virtual Glib::RefPtr<Gio::SimpleAction> get_app_action(const std::string & name) const override;
  const std::vector<Glib::RefPtr<Gio::SimpleAction> > & get_app_actions() const
    {
      return m_app_actions;
    }
  virtual Glib::RefPtr<Gio::SimpleAction> add_app_action(const std::string & name) override;
  virtual void add_app_menu_item(int section, int order, const std::string & label,
                                 const std::string & action_def) override;
  Glib::RefPtr<Gio::Menu> get_app_menu() const;
  virtual void add_main_window_search_action(const Glib::RefPtr<Gtk::Action> & action, int order) override;
  virtual void remove_main_window_search_action(const std::string & name) override;
  virtual std::vector<Glib::RefPtr<Gtk::Action> > get_main_window_search_actions() override;

  virtual void add_tray_menu_item(Gtk::MenuItem & item) override;
  virtual void remove_tray_menu_item(Gtk::MenuItem & item) override;
  virtual std::vector<Gtk::MenuItem*> get_tray_menu_items() override;
private:
  void make_app_actions();
  void make_app_menu_items();
  Glib::RefPtr<Gio::Menu> make_app_menu_section(int section) const;
  void add_main_window_action(std::map<int, Glib::RefPtr<Gtk::Action> > & actions,
                              const Glib::RefPtr<Gtk::Action> & action, int order);
  void remove_main_window_action(std::map<int, Glib::RefPtr<Gtk::Action> > & actions, const std::string & name);
  std::vector<Glib::RefPtr<Gtk::Action> > get_main_window_actions(std::map<int, Glib::RefPtr<Gtk::Action> > & actions);

  Glib::RefPtr<Gtk::ActionGroup> m_main_window_actions;

  std::vector<Glib::RefPtr<Gio::SimpleAction> > m_app_actions;

  struct AppMenuItem
  {
    int order;
    std::string label;
    std::string action_def;

    AppMenuItem(int ord, const std::string & lbl, const std::string & act_def)
      : order(ord)
      , label(lbl)
      , action_def(act_def)
      {}

    struct ptr_comparator
    {
      bool operator() (const AppMenuItem *x, const AppMenuItem *y)
        {
          return x->order < y->order;
        }
    };
  };
  typedef std::multimap<int, AppMenuItem> AppMenuItemMultiMap;
  AppMenuItemMultiMap m_app_menu_items;
  std::map<int, Glib::RefPtr<Gtk::Action> > m_main_window_search_actions;

  std::vector<Gtk::MenuItem*> m_tray_menu_items;
};


}

#endif

