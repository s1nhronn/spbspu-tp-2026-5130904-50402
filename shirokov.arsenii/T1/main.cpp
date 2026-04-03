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
    std::vector< std::string > entries;
    std::vector< std::weak_ptr< Note > > links;
  };

  void note(std::istream& in, std::ostream&, map_t notes);
  void line(std::istream& in, std::ostream&, map_t notes);
  void show(std::istream& in, std::ostream& out, map_t notes);
  void drop(std::istream& in, std::ostream&, map_t notes);
  void link(std::istream& in, std::ostream&, map_t notes);
  void halt(std::istream& in, std::ostream&, map_t notes);
  void mind(std::istream& in, std::ostream& out, map_t notes);
  void expired(std::istream& in, std::ostream& out, map_t notes);
  void refresh(std::istream& in, std::ostream&, map_t notes);
}

int main()
{
  map_t notes;

  using cmd_t = void (*)(std::istream&, std::ostream&, map_t);
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

void shirokov::note(std::istream&, std::ostream&, map_t)
{
  std::cout << "<THERE IS NO IMPLEMENTATION>\n";
  auto toIgnore = std::numeric_limits< std::streamsize >::max();
  std::cin.ignore(toIgnore, '\n');
}

void shirokov::line(std::istream&, std::ostream&, map_t)
{
  std::cout << "<THERE IS NO IMPLEMENTATION>\n";
  auto toIgnore = std::numeric_limits< std::streamsize >::max();
  std::cin.ignore(toIgnore, '\n');
}

void shirokov::show(std::istream&, std::ostream&, map_t)
{
  std::cout << "<THERE IS NO IMPLEMENTATION>\n";
  auto toIgnore = std::numeric_limits< std::streamsize >::max();
  std::cin.ignore(toIgnore, '\n');
}

void shirokov::drop(std::istream&, std::ostream&, map_t)
{
  std::cout << "<THERE IS NO IMPLEMENTATION>\n";
  auto toIgnore = std::numeric_limits< std::streamsize >::max();
  std::cin.ignore(toIgnore, '\n');
}

void shirokov::link(std::istream&, std::ostream&, map_t)
{
  std::cout << "<THERE IS NO IMPLEMENTATION>\n";
  auto toIgnore = std::numeric_limits< std::streamsize >::max();
  std::cin.ignore(toIgnore, '\n');
}

void shirokov::halt(std::istream&, std::ostream&, map_t)
{
  std::cout << "<THERE IS NO IMPLEMENTATION>\n";
  auto toIgnore = std::numeric_limits< std::streamsize >::max();
  std::cin.ignore(toIgnore, '\n');
}

void shirokov::mind(std::istream&, std::ostream&, map_t)
{
  std::cout << "<THERE IS NO IMPLEMENTATION>\n";
  auto toIgnore = std::numeric_limits< std::streamsize >::max();
  std::cin.ignore(toIgnore, '\n');
}

void shirokov::expired(std::istream&, std::ostream&, map_t)
{
  std::cout << "<THERE IS NO IMPLEMENTATION>\n";
  auto toIgnore = std::numeric_limits< std::streamsize >::max();
  std::cin.ignore(toIgnore, '\n');
}

void shirokov::refresh(std::istream&, std::ostream&, map_t)
{
  std::cout << "<THERE IS NO IMPLEMENTATION>\n";
  auto toIgnore = std::numeric_limits< std::streamsize >::max();
  std::cin.ignore(toIgnore, '\n');
}
