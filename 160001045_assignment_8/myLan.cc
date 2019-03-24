#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/netanim-module.h"

// Default Network Topology
//
//       10.1.1.0
// n0 -------------- n1   n2   n3   n4
//    point-to-point  |    |    |    |
//                    ================
//                      LAN 10.1.2.0


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("LanScriptExample");

int 
main (int argc, char *argv[])
{

  uint32_t nCsma = 2; // 2

  CommandLine cmd;
  cmd.AddValue ("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);


  cmd.Parse (argc,argv);


  NodeContainer p2pNodes1;
  p2pNodes1.Create (2); // 3

  NodeContainer p2pNodes2;
  p2pNodes2.Add(p2pNodes1.Get(1));
  p2pNodes2.Create (1); // 3

  NodeContainer csmaNodes;
  csmaNodes.Add (p2pNodes2.Get (1)); // 2
  csmaNodes.Create (nCsma);

  NodeContainer p2pNodes3;
  p2pNodes3.Create(2);

  csmaNodes.Add(p2pNodes3.Get(0));

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer p2pDevices1, p2pDevices2, p2pDevices3;
  p2pDevices1 = pointToPoint.Install (p2pNodes1);
  p2pDevices2 = pointToPoint.Install (p2pNodes2);
  p2pDevices3 = pointToPoint.Install (p2pNodes3);

  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

  NetDeviceContainer csmaDevices;
  csmaDevices = csma.Install (csmaNodes);

  InternetStackHelper stack;
  stack.Install (p2pNodes1.Get (0));
  stack.Install (p2pNodes1.Get (1));
  stack.Install (csmaNodes);
  stack.Install (p2pNodes3.Get (1));

  Ipv4AddressHelper address;

  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces1;
  p2pInterfaces1 = address.Assign (p2pDevices1);

  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces2;
  p2pInterfaces2 = address.Assign (p2pDevices2);
 
  address.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer csmaInterfaces;
  csmaInterfaces = address.Assign (csmaDevices);
 
  address.SetBase ("10.1.6.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces3;
  p2pInterfaces3 = address.Assign (p2pDevices3);

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (p2pNodes3.Get (1));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (p2pInterfaces3.GetAddress(1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (p2pNodes1.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  pointToPoint.EnablePcapAll ("myLan");
  csma.EnablePcap ("myLan", csmaDevices.Get (1), true);

 // Using NetAnim
	AnimationInterface::SetConstantPosition (p2pNodes1.Get (0), 10.0, 20.0);
	AnimationInterface::SetConstantPosition (p2pNodes1.Get (1), 20.0, 20.0);
	AnimationInterface::SetConstantPosition (p2pNodes2.Get (1), 30.0, 30.0);
        AnimationInterface::SetConstantPosition (csmaNodes.Get (1), 40.0, 10.0);
	AnimationInterface::SetConstantPosition (csmaNodes.Get (2), 50.0, 20.0);
	AnimationInterface::SetConstantPosition (p2pNodes3.Get (0), 60.0, 10.0);
	AnimationInterface::SetConstantPosition (p2pNodes3.Get (1), 70.0, 20.0);
//	AnimationInterface::SetConstantPosition (csmaNodes.Get (3), 50.0, 20.0);

	AnimationInterface anim ("myLan.xml"); 


  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
