/*
   Copyright (C) 2003 - 2017 by David White <dave@whitevine.net>
   Part of the Battle for Wesnoth Project http://www.wesnoth.org/

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.

   See the COPYING file for more details.
*/

#pragma once

#include "game_events/handlers.hpp"

#include <memory>
#include <unordered_map>

namespace game_events {

	//event_handlers is essentially the implementation details of the manager
	class event_handlers {
		typedef std::unordered_map<std::string, handler_list> map_t;
		typedef std::unordered_map<std::string, std::weak_ptr<event_handler> > id_map_t;

	public:
		typedef handler_vec::iterator iterator;
		typedef handler_vec::const_iterator const_iterator;

	private:
		handler_vec  active_;  /// Active event handlers. Will not have elements removed unless the event_handlers is clear()ed.
		map_t        by_name_; /// Active event handlers with fixed event names, organized by event name.
		handler_list dynamic_; /// Active event handlers with variables in their event names.
		id_map_t     id_map_;  /// Allows quick locating of handlers by id.


		void log_handlers();
		/// Utility to standardize the event names used in by_name_.
		static std::string standardize_name(const std::string & name);

	public:
		typedef handler_vec::size_type size_type;

		event_handlers()
			: active_()
			, by_name_()
			, dynamic_()
			, id_map_()
		{}

		/// Read-only access to the handlers with varying event names.
		const handler_list & get() const { return dynamic_; }
		/// Read-only access to the handlers with fixed event names, by event name.
		const handler_list & get(const std::string & name) const;

		/// Adds an event handler.
		void add_event_handler(const config & cfg, manager & man, bool is_menu_item=false);
		/// Removes an event handler, identified by its ID.
		void remove_event_handler(const std::string& id);
		/// Gets an event handler, identified by its ID.
		const handler_ptr get_event_handler_by_id(const std::string & id);

		iterator begin() { return active_.begin(); }
		const_iterator begin() const { return active_.begin(); }

		iterator end() { return active_.end(); }
		const_iterator end() const { return active_.end(); }

		/// The number of active event handlers.
		size_type size() const { return active_.size(); }
		/// Access to active event handlers by index.
		handler_ptr & operator[](size_type index) { return active_[index]; }
	};//event_handlers

} //end namespace game_events
