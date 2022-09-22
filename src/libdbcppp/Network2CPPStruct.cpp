
#include "NetworkImpl.h"
#include "../../include/dbcppp/Network2Functions.h"

using namespace dbcppp;
using namespace dbcppp::Network2CPPStruct;

static const char *header =
    "// This file created by customized dbcppp automatically\n"
    "// Menbers in structure can be access by reflection using RTTR libraries(https://www.rttr.org/)\n"
    "// Change Type to correct variable type\n\n"
    "#include <dbcppp/Network.h>\n"
    "#include <dbcppp/Network2Functions.h>\n"
    "#include <rttr/registration>\n\n";

DBCPPP_API std::ostream &
dbcppp::Network2CPPStruct::operator<<(std::ostream &os, const INetwork &net)
{
  //
  os << boost::format(header);
  for (const auto &msg : net.Messages())
  {
    std::uint64_t cycle_time;
    for (const auto &attr : msg.AttributeValues())
    {
      if (attr.Name() == "GenMsgCycleTime")
        cycle_time = std::get<double>(attr.Value());
    }

    os << boost::format(
              "struct %s\n"
              "{\n") %
              (msg.Name());

    for (const auto &sig : msg.Signals())
    {
      os << boost::format("  Type %s;\n") % (sig.Name());
    }
    os << boost::format("  static const std::uint64_t id = %lf;\n"
                        "  static const std::uint64_t cycle_time = %lf;\n") %
              msg.Id() % cycle_time;
    os << boost::format("  std::uint64_t Id() { return id;}\n"
                        "  std::uint64_t Cycle_time() { return cycle_time;}\n");

    os << boost::format("  RTTR_ENABLE()\n"
                        "};\n");
  }

  os << boost::format("struct Can_Bus : ");
  for (const auto &msg : net.Messages())
  {
    os << boost::format("%s, ") % (msg.Name());
  }
  os.seekp(-2, os.cur); // delete last ", "
  os << boost::format("\n"
                      "{\n"
                      "  RTTR_ENABLE(");
  for (const auto &msg : net.Messages())
  {
    os << boost::format("%s, ") % (msg.Name());
  }
  os.seekp(-2, os.cur); // delete last ", "
  os << boost::format(")\n"
                      "};\n\n");
  os << boost::format("RTTR_REGISTRATION\n"
                      "{\n");
  for (const auto &msg : net.Messages())
  {
    os << boost::format(
              "  rttr::registration::class_<%s>(\"%s\")\n"
              "    .constructor<>()\n") %
              (msg.Name()) % (msg.Name());
    for (const auto &sig : msg.Signals())
    {
      os << boost::format("    .property(\"%s::%s\", &%s::%s)\n") % msg.Name() % sig.Name() % msg.Name() % sig.Name();
    }
    os.seekp(-1, os.cur); // delete last "\n"
    os << boost::format(";\n\n");
  }
  os << boost::format(
      "  rttr::registration::class_<Can_Bus>(\"Can_Bus\")\n"
      "  .constructor<>();\n\n");

  os << boost::format("}");

  return os;
}
