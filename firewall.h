#include "address.h"
#include "node.h"
#include "object.h"
#include <set>
#include <string>

class FirewallPolicy : public Object
{
public:
  virtual bool isAllowed(Packet *packet) = 0;
  std::string name() override { return "FirewallPolicy"; };
};

class Firewall : public Node
{
private:
  class AllowAnyPolicy : public FirewallPolicy
  {
  private:
    short destPort_;

  public:
    AllowAnyPolicy(short destPort) : destPort_(destPort) {}
    std::string name() override { return "AllowAnyPolicy"; };
    bool isAllowed(Packet *packet)
    {
      if (packet->destPort() == destPort_)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
  };

  class AllowSpecificPolicy : public FirewallPolicy
  {
  private:
    Address srcAddress_;
    short destPort_;

  public:
    AllowSpecificPolicy(Address srcAddress, short destPort)
        : srcAddress_(srcAddress), destPort_(destPort) {}
    std::string name() override { return "AllowSpecificPolicy"; };
    bool isAllowed(Packet *packet)
    {
      if (packet->destPort() == destPort_ && packet->srcAddress() == srcAddress_)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
  };

  Link *receiveLink_ = nullptr;
  std::vector<FirewallPolicy *> policies_;

  void allowPacket(Packet *packet)
  {
    for (auto i : accessableLink)
    {
      if (receiveLink_ == i)
      {
        continue;
      }
      else
      {
        i->connect(this, packet);
        break;
      }
    }
  }
  void dropPacket(Packet *packet)
  {
    log("Dropping " + packet->toString() +
        " with src address " + packet->srcAddress().toString() +
        " and dest port " + std::to_string(packet->destPort()));
  }
  Host *serverHost_;

public:
  std::string name() override { return "Firewall"; };
  void setReceiveLink(Link *link)
  {
    receiveLink_ = link;
    for (auto access : accessableLink)
    {
      if (access != receiveLink_)
      {
        serverHost_ = dynamic_cast<Host *>(access->other(this));
      }
    }
  }

  void addAllowAnyPolicy(short destPort)
  {
    policies_.push_back(new AllowAnyPolicy(destPort));
  }
  void addAllowSpecificPolicy(Address srcAddress, short destPort)
  {
    policies_.push_back(new AllowSpecificPolicy(srcAddress, destPort));
  }

  void send(Packet *packet) {}
  void receive(Packet *packet)
  {
    if (packet->srcAddress() == serverHost_->address())
    {
      receiveLink_->connect(this, packet);
      return;
    }

    for (auto policy : policies_)
    {
      if (policy->isAllowed(packet))
      {
        allowPacket(packet);
        return;
      }
    }
    dropPacket(packet);
  }
};