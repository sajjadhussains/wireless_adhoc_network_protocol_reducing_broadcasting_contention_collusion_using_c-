# To run this download and run from the main.cpp file
# A Contention and Collision Aware Timer-based Proactive Approach of Broadcasting to Enhance Reachability for Wireless Ad-hoc Networks

## Broadcast Storm Problem:
During the broadcast in wireless network 3 problems arise,those three problems are called together broadcast storm problems.Those Three Problems are:
- Redundency
- Contention
- Collision
### Redundancy
It occurs when many hosts within the transmission range of a host rebroadcast the same packet,
even if their neighbors have already received it. This redundancy leads to the reception of the
same message over and over.
### Contention:
 After receiving a broadcast message, neighboring hosts simultaneously attempt to
rebroadcast the message, resulting in contention as they compete to send the same message to
the same receiving node.
### Collision:
 is another issue caused by the absence of an RTS/CTS (request-to-send/clear-to-send) mechanism for broadcasting in wireless ad-hoc networks. Since the timing of rebroadcasts is highly
correlated, it is possible for two or more neighboring hosts to forward the message to each other
simultaneously, leading to collisions. 

When contention and collision occurs then the reachibility of the message reduce.But the main condition of the broadcasting is to ensure the reachibility of the message to all nodes.To achieve this we have used a timer mechanisim to reduce the contention and collision problem.

To see details you can download the paper from given link:
**[paper_link](https://example.com](https://drive.google.com/file/d/12oSHrkwSya3WQmN_ti0KvxxIWlAbm1DJ/view?usp=sharing))**
