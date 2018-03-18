#include "dict.h"

#include <ios>
#include <iostream>
#include <memory>
#include <unordered_map>
#include "dictglobal.h"

#ifndef NDEBUG
static const bool DEBUG = true;
#else
static const bool DEBUG = false;
#endif

using dict = std::unordered_map<std::string, std::string>;
using dict_ptr = std::unique_ptr<dict>;
using dict_dict = std::unordered_map<unsigned long, dict_ptr>;

namespace {

  /** Returns a map of dictionaries. Initializes the map on the first use. */
  dict_dict& dict_map() {
    static dict_dict dict_map = dict_dict();
    return dict_map;
  }

  /** Returns iterator to dict with given id or to end(). */
  dict_dict::iterator get_dict(unsigned long id) { return dict_map().find(id); }

  /** Says whether iterator points at end(). */
  bool no_dict_at(dict_dict::iterator dict_pos) {
    return dict_map().end() == dict_pos;
  }

  /** Returns iterator to key with given key or to end(). */
  dict::iterator get_key(dict& dict, const char* key) { return dict.find(key); }

  /** Says whether iterator points at end(). */
  bool no_key_at(dict& dict, dict::iterator key_pos) {
    return dict.end() == key_pos;
  }

  /** Sends message to cerr if DEBUG enabled. */
  static void log(std::string s) {
    if (!DEBUG) {
      return;
    }
    static std::ios_base::Init toEnsureInitialization;
    std::cerr << s << std::endl;
  }

  /** Makes a quoted string from C-string, or "NULL" string if empty */
  static std::string add_quotes(const char* chars) {
    return (chars == NULL) ? "NULL" : "\"" + std::string(chars) + "\"";
  }

  /** Makes a human-readable dictionary name from dictionary id */
  static std::string dict_name(unsigned long id) {
    return (id == dict_global()) ? "the Global Dictionary"
                                : "dict " + std::to_string(id);
  }

  /** Puts value in dictionary. Does nothing if putting to full global dict. */
  void dict_put(unsigned long id, dict& dict, std::string key,
                std::string value) {
    if (id == dict_global() && dict.size() == MAX_GLOBAL_DICT_SIZE &&
        no_key_at(dict, dict.find(key))) {
      log("dict_put: the Global Dictionary is full");
      return;
    }

    dict[key] = value;

    log("dict_put: " + dict_name(id) + ", the pair (" + add_quotes(key.c_str()) +
        ", " + add_quotes(value.c_str()) + ") has been inserted");
  }
}

unsigned long dict_new() {
  log(std::string("dict_new()"));

  static unsigned long last_dict_id = 0;
  unsigned long new_dict_id = last_dict_id++;
  dict_map()[new_dict_id] = dict_ptr(new dict());

  log("dict_new: dict " + std::to_string(new_dict_id) + " has been created");
  return new_dict_id;
}

void dict_delete(unsigned long id) {
  log("dict_delete(" + std::to_string(id) + ")");

  if (dict_global() == id) {
    log("dict_delete: an attempt to remove the Global Dictionary");
    return;
  }

  auto dict_pos = get_dict(id);
  if (no_dict_at(dict_pos)) {
    log("dict_delete: " + dict_name(id) + " does not exist");
    return;
  }

  dict_map().erase(dict_pos);
  log("dict_delete: " + dict_name(id) + " has been deleted");
}

size_t dict_size(unsigned long id) {
  log("dict_size(" + std::to_string(id) + ")");

  auto dict_pos = get_dict(id);
  if (no_dict_at(dict_pos)) {
    log("dict_size: " + dict_name(id) + " does not exist");
    return 0;
  }
  auto& dict = *(dict_pos->second);

  log("dict_size: " + dict_name(id) + " contains " +
      std::to_string(dict.size()) + " element(s)");

  return dict.size();
}

void dict_insert(unsigned long id, const char* key, const char* value) {
  log("dict_insert(" + std::to_string(id) + ", " + add_quotes(key) + ", " +
      add_quotes(value) + ")");

  if (key == NULL) {
    log("dict_insert: " + dict_name(id) + ", an attempt to insert NULL key");
  }

  if (value == NULL) {
    log("dict_insert: " + dict_name(id) + ", an attempt to insert NULL value");
  }

  if (key == NULL || value == NULL) {
    return;
  }

  auto dict_pos = get_dict(id);
  if (no_dict_at(dict_pos)) {
    log("dict_insert: " + dict_name(id) + " does not exist");
    return;
  }

  auto& dict = *(dict_pos->second);
  dict_put(id, dict, std::string(key), std::string(value));
}

void dict_remove(unsigned long id, const char* key) {
  log("dict_remove(" + std::to_string(id) + ", " + add_quotes(key) + ")");

  auto dict_pos = get_dict(id);
  if (no_dict_at(dict_pos)) {
    log("dict_remove: " + dict_name(id) + " does not exist");
    return;
  }

  auto& dict = *(dict_pos->second);
  auto key_pos = get_key(dict, key);
  if (no_key_at(dict, key_pos)) {
    log("dict_remove: " + dict_name(id) + " does not contain the key " +
        add_quotes(key));
    return;
  }

  dict.erase(key_pos);
  log("dict_remove: " + dict_name(id) + ", the key " + add_quotes(key) +
      " has been removed");
}

static const char* dict_find_global(unsigned long id, const char* key) {
  auto dict_pos = get_dict(dict_global());
  auto& dict = *(dict_pos->second);
  auto key_pos = get_key(dict, key);
  if (no_key_at(dict, key_pos)) {
    log("dict_find: the key " + add_quotes(key) + " not found");
    return NULL;
  } else {
    log("dict_find: " + dict_name(id) + ", the key " + add_quotes(key) +
        " has the value " + add_quotes(key_pos->second.c_str()));
    return key_pos->second.c_str();
  }
}

const char* dict_find(unsigned long id, const char* key) {
  log("dict_find(" + std::to_string(id) + ", " + add_quotes(key) + ")");

  if (key == NULL) {
    log("dict_find: an attempt to search a NULL key");
    return NULL;
  }

  auto dict_pos = get_dict(id);
  if (no_dict_at(dict_pos)) {
    log("dict_find: " + dict_name(id) + " does not exist");
    log("dict_find: the key " + add_quotes(key) +
        " not found, looking up the Global Dictionary");
    return dict_find_global(id, key);
  }

  auto& dict = *(dict_pos->second);
  auto key_pos = get_key(dict, key);
  if (no_key_at(dict, key_pos) && id == dict_global()) {
    log("dict_find: the key " + add_quotes(key) + " not found");
    return NULL;
  } else if (no_key_at(dict, key_pos)) {
    log("dict_find: the key " + add_quotes(key) +
        " not found, looking up the Global Dictionary");
    return dict_find_global(id, key);
  }

  log("dict_find: " + dict_name(id) + ", the key " + add_quotes(key) +
      " has the value " + add_quotes(key_pos->second.c_str()));
  return key_pos->second.c_str();
}

void dict_clear(unsigned long id) {
  log("dict_clear(" + std::to_string(id) + ")");

  auto dict_pos = get_dict(id);
  if (no_dict_at(dict_pos)) {
    log("dict_clear: " + dict_name(id) + " does not exist");
    return;
  }

  auto& dict = *(dict_pos->second);
  dict.clear();
  log("dict_clear: " + dict_name(id) + " has been cleared");
}

void dict_copy(unsigned long src_id, unsigned long dst_id) {
  log("dict_copy(" + std::to_string(src_id) + ", " + std::to_string(dst_id) +
      ")");

  if (src_id == dst_id) {
    log("dict_copy: An attempt to copy the exact same dict");
    return;
  }

  auto src_dict_pos = get_dict(src_id);
  if (no_dict_at(src_dict_pos)) {
    log("dict_copy: " + dict_name(src_id) + " does not exist");
    return;
  }

  auto dst_dict_pos = get_dict(dst_id);
  if (no_dict_at(dst_dict_pos)) {
    log("dict_copy: " + dict_name(dst_id) + " does not exist");
    return;
  }

  auto& src_dict = *(src_dict_pos->second);
  auto& dst_dict = *(dst_dict_pos->second);
  for (auto& entry : src_dict) {
    dict_put(dst_id, dst_dict, entry.first, entry.second);
  }
  log("dict_copy: " + dict_name(src_id) + " has been copied to " +
      dict_name(dst_id));
}