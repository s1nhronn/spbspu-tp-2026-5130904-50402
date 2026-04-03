#include <iomanip>
#include <ios>
#include <iostream>
#include <istream>
#include <limits>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace shirokov
{
  struct Note;
}

using map_t = std::unordered_map< std::string, std::shared_ptr< shirokov::Note > >;

namespace shirokov
{
  struct Note
  {
    Note() = default;
    std::vector< std::string > entries;
    std::unordered_map< std::string, std::weak_ptr< Note > > links;
  };

  void note(std::istream& in, std::ostream&, map_t& notes);
  void line(std::istream& in, std::ostream&, map_t& notes);
  void show(std::istream& in, std::ostream& out, map_t& notes);
  void drop(std::istream& in, std::ostream&, map_t& notes);
  void link(std::istream& in, std::ostream&, map_t& notes);
  void halt(std::istream& in, std::ostream&, map_t& notes);
  void mind(std::istream& in, std::ostream& out, map_t& notes);
  void expired(std::istream& in, std::ostream& out, map_t& notes);
  void refresh(std::istream& in, std::ostream&, map_t& notes);
}

int main()
{
  map_t notes;

  using cmd_t = void (*)(std::istream&, std::ostream&, map_t&);
  std::unordered_map< std::string, cmd_t > cmds;
  cmds["note"] = shirokov::note;
  cmds["line"] = shirokov::line;
  cmds["show"] = shirokov::show;
  cmds["drop"] = shirokov::drop;
  cmds["link"] = shirokov::link;
  cmds["halt"] = shirokov::halt;
  cmds["mind"] = shirokov::mind;
  cmds["expired"] = shirokov::expired;
  cmds["refresh"] = shirokov::refresh;

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout, notes);
    }
    catch (...)
    {
      std::cerr << "<INVALID COMMAND>\n";
      auto toIgnore = std::numeric_limits< std::streamsize >::max();
      std::cin.ignore(toIgnore, '\n');
    }
  }
  if (!std::cin.eof())
  {
    std::cerr << "Bad input\n";
    return 1;
  }
}

void shirokov::note(std::istream& in, std::ostream&, map_t& notes)
{
  std::string noteName;
  in >> noteName;
  if (!noteName.empty() && notes.find(noteName) == notes.end())
  {
    notes[noteName] = std::make_shared< Note >();
  }
}

void shirokov::line(std::istream& in, std::ostream&, map_t& notes)
{
  std::string noteName, quotedText;
  in >> noteName >> std::quoted(quotedText);
  notes.at(noteName)->entries.push_back(quotedText);
}

void shirokov::show(std::istream& in, std::ostream& out, map_t& notes)
{
  std::string noteName;
  in >> noteName;
  for (std::string line : notes.at(noteName)->entries)
  {
    out << line << '\n';
  }
  if (notes.at(noteName)->entries.empty())
  {
    out << '\n';
  }
}

void shirokov::drop(std::istream& in, std::ostream&, map_t& notes)
{
  std::string noteName;
  in >> noteName;
  notes.at(noteName);
  notes.erase(noteName);
}

void shirokov::link(std::istream& in, std::ostream&, map_t& notes)
{
  std::string noteTo, noteFrom;
  in >> noteTo >> noteFrom;
  std::shared_ptr< Note > toPtr = notes.at(noteTo);
  std::shared_ptr< Note > fromPtr = notes.at(noteFrom);
  if (!noteTo.empty() && !noteFrom.empty() && fromPtr->links.find(noteTo) == fromPtr->links.end())
  {
    fromPtr->links[noteTo] = toPtr;
  }
}

void shirokov::halt(std::istream& in, std::ostream&, map_t& notes)
{
  std::string noteTo, noteFrom;
  in >> noteTo >> noteFrom;
  std::shared_ptr< Note > fromPtr = notes.at(noteFrom);
  fromPtr->links.erase(noteTo);
}

void shirokov::mind(std::istream& in, std::ostream& out, map_t& notes)
{
  std::string noteFrom;
  in >> noteFrom;
  std::shared_ptr< Note > fromPtr = notes.at(noteFrom);
  for (const auto& pair : fromPtr->links)
  {
    if (pair.second.lock())
    {
      out << pair.first << '\n';
    }
  }
  if (fromPtr->links.empty())
  {
    out << '\n';
  }
}

void shirokov::expired(std::istream& in, std::ostream& out, map_t& notes)
{
  std::string noteFrom;
  in >> noteFrom;
  std::shared_ptr< Note > fromPtr = notes.at(noteFrom);
  size_t k = 0;
  for (const auto& pair : fromPtr->links)
  {
    if (!pair.second.lock())
    {
      ++k;
    }
  }
  out << k << '\n';
}

void shirokov::refresh(std::istream& in, std::ostream&, map_t& notes)
{
  std::string noteFrom;
  in >> noteFrom;
  std::shared_ptr< Note > fromPtr = notes.at(noteFrom);
  for (const auto& pair : fromPtr->links)
  {
    if (!pair.second.lock())
    {
      fromPtr->links.erase(pair.first);
    }
  }
}
