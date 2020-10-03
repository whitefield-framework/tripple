# Platform API

APIs providing platform abstraction. Typically these would be for:
1. ICMPv6 send/recv
2. Timer control
3. Memory/buffer pool control
4. Routing table interfaces
5. Neighbor cache interfaces

These interfaces have to be defined separately for all the targeted platforms for e.g, Linux, LWIP, and embedded (RIOT/Contiki-ng/...).
