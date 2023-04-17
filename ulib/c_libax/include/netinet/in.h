
#ifndef _IN_H
#define _IN_H 1

#include <bits/sockaddr.h>
#include <stdint.h>
#include <sys/socket.h>

enum {
    IPPROTO_IP = 0, /* Dummy protocol for TCP.  */
#define IPPROTO_IP IPPROTO_IP
    IPPROTO_ICMP = 1, /* Internet Control Message Protocol.  */
#define IPPROTO_ICMP IPPROTO_ICMP
    IPPROTO_IGMP = 2, /* Internet Group Management Protocol. */
#define IPPROTO_IGMP IPPROTO_IGMP
    IPPROTO_IPIP = 4, /* IPIP tunnels (older KA9Q tunnels use 94).  */
#define IPPROTO_IPIP IPPROTO_IPIP
    IPPROTO_TCP = 6, /* Transmission Control Protocol.  */
#define IPPROTO_TCP IPPROTO_TCP
    IPPROTO_EGP = 8, /* Exterior Gateway Protocol.  */
#define IPPROTO_EGP IPPROTO_EGP
    IPPROTO_PUP = 12, /* PUP protocol.  */
#define IPPROTO_PUP IPPROTO_PUP
    IPPROTO_UDP = 17, /* User Datagram Protocol.  */
#define IPPROTO_UDP IPPROTO_UDP
    IPPROTO_IDP = 22, /* XNS IDP protocol.  */
#define IPPROTO_IDP IPPROTO_IDP
    IPPROTO_TP = 29, /* SO Transport Protocol Class 4.  */
#define IPPROTO_TP IPPROTO_TP
    IPPROTO_DCCP = 33, /* Datagram Congestion Control Protocol.  */
#define IPPROTO_DCCP IPPROTO_DCCP
    IPPROTO_IPV6 = 41, /* IPv6 header.  */
#define IPPROTO_IPV6 IPPROTO_IPV6
    IPPROTO_RSVP = 46, /* Reservation Protocol.  */
#define IPPROTO_RSVP IPPROTO_RSVP
    IPPROTO_GRE = 47, /* General Routing Encapsulation.  */
#define IPPROTO_GRE IPPROTO_GRE
    IPPROTO_ESP = 50, /* encapsulating security payload.  */
#define IPPROTO_ESP IPPROTO_ESP
    IPPROTO_AH = 51, /* authentication header.  */
#define IPPROTO_AH IPPROTO_AH
    IPPROTO_MTP = 92, /* Multicast Transport Protocol.  */
#define IPPROTO_MTP IPPROTO_MTP
    IPPROTO_BEETPH = 94, /* IP option pseudo header for BEET.  */
#define IPPROTO_BEETPH IPPROTO_BEETPH
    IPPROTO_ENCAP = 98, /* Encapsulation Header.  */
#define IPPROTO_ENCAP IPPROTO_ENCAP
    IPPROTO_PIM = 103, /* Protocol Independent Multicast.  */
#define IPPROTO_PIM IPPROTO_PIM
    IPPROTO_COMP = 108, /* Compression Header Protocol.  */
#define IPPROTO_COMP IPPROTO_COMP
    IPPROTO_SCTP = 132, /* Stream Control Transmission Protocol.  */
#define IPPROTO_SCTP IPPROTO_SCTP
    IPPROTO_UDPLITE = 136, /* UDP-Lite protocol.  */
#define IPPROTO_UDPLITE IPPROTO_UDPLITE
    IPPROTO_MPLS = 137, /* MPLS in IP.  */
#define IPPROTO_MPLS IPPROTO_MPLS
    IPPROTO_ETHERNET = 143, /* Ethernet-within-IPv6 Encapsulation.  */
#define IPPROTO_ETHERNET IPPROTO_ETHERNET
    IPPROTO_RAW = 255, /* Raw IP packets.  */
#define IPPROTO_RAW IPPROTO_RAW
    IPPROTO_MPTCP = 262, /* Multipath TCP connection.  */
#define IPPROTO_MPTCP IPPROTO_MPTCP
    IPPROTO_MAX
};

typedef uint16_t in_port_t;

typedef uint32_t in_addr_t;
struct in_addr {
    in_addr_t s_addr;
};

struct in6_addr {
    union {
        uint8_t __u6_addr8[16];
        uint16_t __u6_addr16[8];
        uint32_t __u6_addr32[4];
    } __in6_u;
#define s6_addr __in6_u.__u6_addr8
#ifdef __USE_MISC
#define s6_addr16 __in6_u.__u6_addr16
#define s6_addr32 __in6_u.__u6_addr32
#endif
};
struct sockaddr_in {
    __SOCKADDR_COMMON(sin_);
    in_port_t sin_port;      /* Port number.  */
    struct in_addr sin_addr; /* Internet address.  */

    /* Pad to size of `struct sockaddr'.  */
    unsigned char sin_zero[sizeof(struct sockaddr) - __SOCKADDR_COMMON_SIZE - sizeof(in_port_t) -
                           sizeof(struct in_addr)];
};

struct sockaddr_in6 {
    __SOCKADDR_COMMON(sin6_);
    in_port_t sin6_port;       /* Transport layer port # */
    uint32_t sin6_flowinfo;    /* IPv6 flow information */
    struct in6_addr sin6_addr; /* IPv6 address */
    uint32_t sin6_scope_id;    /* IPv6 scope-id */
};

#define IPV6_NEXTHOP              9
#define IPV6_AUTHHDR              10
#define IPV6_UNICAST_HOPS         16
#define IPV6_MULTICAST_IF         17
#define IPV6_MULTICAST_HOPS       18
#define IPV6_MULTICAST_LOOP       19
#define IPV6_JOIN_GROUP           20
#define IPV6_LEAVE_GROUP          21
#define IPV6_ROUTER_ALERT         22
#define IPV6_MTU_DISCOVER         23
#define IPV6_MTU                  24
#define IPV6_RECVERR              25
#define IPV6_V6ONLY               26
#define IPV6_JOIN_ANYCAST         27
#define IPV6_LEAVE_ANYCAST        28
#define IPV6_MULTICAST_ALL        29
#define IPV6_ROUTER_ALERT_ISOLATE 30
#define IPV6_RECVERR_RFC4884      31
#define IPV6_IPSEC_POLICY         34
#define IPV6_XFRM_POLICY          35
#define IPV6_HDRINCL              36

#define INET_ADDRSTRLEN  16
#define INET6_ADDRSTRLEN 46

#define IN6ADDR_ANY_INIT                                       \
    {                                                          \
        {                                                      \
            {                                                  \
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 \
            }                                                  \
        }                                                      \
    }
#define IN6ADDR_LOOPBACK_INIT                                  \
    {                                                          \
        {                                                      \
            {                                                  \
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 \
            }                                                  \
        }                                                      \
    }

uint16_t ntohs(uint16_t __netshort);
uint32_t htonl(uint32_t __hostlong);
uint32_t ntohl(uint32_t __netlong);
uint16_t htons(uint16_t __hostshort);

#endif