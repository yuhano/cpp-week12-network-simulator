#include "address.h"
#include "host.h"
#include "link.h"
#include <set>
#include <vector>

struct NatEntry
{
  Address internalAddress;
  short internalPort;
  short externalPort;
  NatEntry(Address internalAddr, short internalPrt, short externalPrt) // Parameterized constructor
      : internalAddress(internalAddr), internalPort(internalPrt), externalPort(externalPrt)
  { }
};

class Nat : public Node
{
private:
  Address address_;

  Link *wanLink_;
  std::vector<NatEntry *> natTable_;

  int lastPort_ = 1000;

  int getNewPort()
  {
    return lastPort_++;
  }

  NatEntry *addNatEntry(Packet *packet)
  {
    int natPort = getNewPort();
    NatEntry *entry = new NatEntry(packet->srcAddress(), packet->srcPort(), natPort);
    natTable_.push_back(entry);
    return entry;
  }

  NatEntry *findEntry(Packet *packet)
  {
    for (auto entry : natTable_)
    {
      if (entry)
      {
        if (entry->internalAddress == packet->srcAddress() && entry->internalPort == packet->srcPort())
        {
          return entry;
        }
      }
    }
    for (auto entry : natTable_)
    {
      if (entry)
      {
        if (entry->externalPort == packet->destPort())
        {
          return entry;
        }
      }
    }
    return nullptr;
  }

  Packet *convertLanPacketToInternetPacket(Packet *packet)
  {
    NatEntry *entry = nullptr;
    entry = findEntry(packet);
    if (entry == nullptr)
    {
      entry = addNatEntry(packet);
    }

    Packet *newPacket = new Packet(
        address_,
        packet->destAddress(),
        entry->externalPort,
        packet->destPort(),
        packet->data());

    return newPacket;
  }

  Packet *convertInternetToLanPacket(Packet *packet)
  {
    NatEntry *entry = findEntry(packet);
    Packet *newPacket = new Packet(
        packet->srcAddress(),
        entry->internalAddress,
        packet->srcPort(),
        entry->internalPort,
        packet->data());
    return newPacket;
  }

public:
  Nat(Address address) : address_(address) {}
  std::string name() override { return "Nat"; };

  void setWanLink(Link *link) { wanLink_ = link; }
  // 발신
  void send(Packet *packet)
  {
    wanLink_->connect(this, packet);
  }

  void receive(Packet *packet)
  {
    if (packet->destAddress() == address_)
    {
      Packet *newPacket = convertInternetToLanPacket(packet);
      if (newPacket)
      {
        send(newPacket);
      }
    }
    else
    {
      Packet *newPacket = convertLanPacketToInternetPacket(packet);
      send(newPacket);
    }

  }
};
