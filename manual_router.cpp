#include "manual_router.h"

void ManualRouter::addRoutingEntry(const Address &destination, Link *nextLink)
{
    routingTable_.push_back(RoutingEntry (destination, nextLink));
}
