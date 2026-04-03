#include <ios>
#include <iostream>
#include <istream>
#include <limits>
#include <ostream>
#include <string>
#include <unordered_map>

namespace shirokov
{
  struct Note
  {
  };

  void note(std::istream& in, std::ostream&, std::unordered_map< std::string, shirokov::Note > notes);
  void line(std::istream& in, std::ostream&, std::unordered_map< std::string, shirokov::Note > notes);
  void show(std::istream& in, std::ostream& out, std::unordered_map< std::string, shirokov::Note > notes);
  void drop(std::istream& in, std::ostream&, std::unordered_map< std::string, shirokov::Note > notes);
  void link(std::istream& in, std::ostream&, std::unordered_map< std::string, shirokov::Note > notes);
  void halt(std::istream& in, std::ostream&, std::unordered_map< std::string, shirokov::Note > notes);
  void mind(std::istream& in, std::ostream& out, std::unordered_map< std::string, shirokov::Note > notes);
  void expired(std::istream& in, std::ostream& out, std::unordered_map< std::string, shirokov::Note > notes);
  void refresh(std::istream& in, std::ostream&, std::unordered_map< std::string, shirokov::Note > notes);
}

int main()
{
  std::unordered_map< std::string, shirokov::Note > notes;

  using cmd_t = void (*)(std::istream&, std::ostream&, std::unordered_map< std::string, shirokov::Note >);
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
