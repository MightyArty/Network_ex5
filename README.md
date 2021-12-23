# Network_ex5
ICMP ECHO request's, reply's and ICMP sniffing
# First part
In 'myping.c' I'm sending an ICMP ECHO equest and receives ICMP ECHO reply
Measuring the RTT from the moment the request was sent until we've got the reply.
The address of the server is 8.8.8.8 (google DNS server)

![Picture1](https://user-images.githubusercontent.com/77808208/147288924-aeb6c11c-236e-4e79-a286-782a877ce562.png)

# Second part
In 'sniffer.c' I'm requested to sniff ICMP packet's and to display the packets info --> source, destination, type and code).
I'm performed a simple ping test from the source IP (AWS IP address) and destination IP (google DNS server).
As you can see in the next screenshot, each ECHO request has ICMP type 8 and each ECHO reply has ICMP type 0.

![Picture1](https://user-images.githubusercontent.com/77808208/147289194-a424f0b9-3644-410d-bfd9-3e643aaa2a3d.png)
