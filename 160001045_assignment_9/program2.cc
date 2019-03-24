#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/netanim-module.h"
using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("LanScriptExample");

int main (int argc, char *argv[])
{
  uint32_t nCsma = 3;

  CommandLine cmd;
  cmd.AddValue ("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);

  cmd.Parse (argc,argv);

  NodeContainer csmaNodes;
  csmaNodes.Create (nCsma);

  NodeContainer p2pNodes2;
  p2pNodes2.Add (csmaNodes.Get (1));
  p2pNodes2.Create (1);

  NodeContainer p2pNodes3;
  p2pNodes3.Add (csmaNodes.Get (1));
  p2pNodes3.Create (1);

  NodeContainer p2pNodes1;
  p2pNodes1.Add (p2pNodes2.Get (1));
  p2pNodes1.Create (1);

  NodeContainer p2pNodes4;
  p2pNodes4.Add (p2pNodes3.Get (1));
  p2pNodes4.Create (1);

  NodeContainer p2pNodes5;
  p2pNodes5.Add (p2pNodes2.Get (1));
  p2pNodes5.Create (1);

  NodeContainer csmaNodes1;
  csmaNodes1.Add(p2pNodes5.Get(1));
  csmaNodes1.Create (2);

  NodeContainer p2pNodes6;
  p2pNodes6.Add (p2pNodes3.Get (1));
  p2pNodes6.Add (p2pNodes5.Get (1));

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer p2pDevices1;
  p2pDevices1 = pointToPoint.Install (p2pNodes1);

  NetDeviceContainer p2pDevices2;
  p2pDevices2 = pointToPoint.Install (p2pNodes2);

  NetDeviceContainer p2pDevices3;
  p2pDevices3 = pointToPoint.Install (p2pNodes3);

  NetDeviceContainer p2pDevices4;
  p2pDevices4 = pointToPoint.Install (p2pNodes4);

  NetDeviceContainer p2pDevices5;
  p2pDevices5 = pointToPoint.Install (p2pNodes5);

  NetDeviceContainer p2pDevices6;
  p2pDevices6 = pointToPoint.Install (p2pNodes6);

  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

  NetDeviceContainer csmaDevices;
  csmaDevices = csma.Install (csmaNodes);

  NetDeviceContainer csmaDevices1;
  csmaDevices1 = csma.Install (csmaNodes1);

  InternetStackHelper stack;
  stack.Install (csmaNodes);
  stack.Install (p2pNodes2.Get (1));
  stack.Install (p2pNodes3.Get (1));
  stack.Install (p2pNodes1.Get (1));
  stack.Install (p2pNodes4.Get (1));
  stack.Install (p2pNodes5.Get (1));
  stack.Install (csmaNodes1.Get(1));
  stack.Install (csmaNodes1.Get(2));

  Ipv4AddressHelper address;
  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces1;
  p2pInterfaces1 = address.Assign (p2pDevices1);

  address.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer csmaInterfaces;
  csmaInterfaces = address.Assign (csmaDevices);

  address.SetBase ("10.1.7.0", "255.255.255.0");
  Ipv4InterfaceContainer csmaInterfaces1;
  csmaInterfaces1 = address.Assign (csmaDevices1);

  address.SetBase ("10.1.4.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces2;
  p2pInterfaces2 = address.Assign (p2pDevices2);

  address.SetBase ("10.1.5.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces3;
  p2pInterfaces3 = address.Assign (p2pDevices3);

  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces4;
  p2pInterfaces4 = address.Assign (p2pDevices4);

  address.SetBase ("10.1.6.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces5;
  p2pInterfaces5 = address.Assign (p2pDevices5);

  address.SetBase ("10.1.8.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces6;
  p2pInterfaces6 = address.Assign (p2pDevices6);

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (csmaNodes.Get(0));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (csmaInterfaces.GetAddress (0), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (csmaNodes1.Get(0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

  ApplicationContainer serverApps1 = echoServer.Install (csmaNodes1.Get(2));
  serverApps1.Start (Seconds (1.0));
  serverApps1.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient1 (csmaInterfaces1.GetAddress (2), 9);
  echoClient1.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient1.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient1.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps1 = echoClient1.Install (csmaNodes.Get(2));
  clientApps1.Start (Seconds (2.0));
  clientApps1.Stop (Seconds (10.0));

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
  Ipv4GlobalRoutingHelper ashish;
  Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper>("routing-tables.txt", std::ios::out);
  ashish.PrintRoutingTableAllAt (Seconds (10), routingStream);
  pointToPoint.EnablePcapAll ("val-3");
  csma.EnablePcap ("val-3", csmaDevices.Get (1), true);

 // Using NetAnim
	AnimationInterface::SetConstantPosition (csmaNodes.Get (0), 20.0, 20.0);
	AnimationInterface::SetConstantPosition (csmaNodes.Get (1), 30.0, 20.0);
	AnimationInterface::SetConstantPosition (csmaNodes.Get (2), 40.0, 20.0);
	AnimationInterface::SetConstantPosition (p2pNodes1.Get (1), 15.0, 30.0);
	AnimationInterface::SetConstantPosition (p2pNodes2.Get (1), 25.0, 30.0);
	AnimationInterface::SetConstantPosition (p2pNodes3.Get (1), 35.0, 30.0);
	AnimationInterface::SetConstantPosition (p2pNodes4.Get (1), 45.0, 30.0);
	AnimationInterface::SetConstantPosition (p2pNodes5.Get (1), 30.0, 40.0);
	AnimationInterface::SetConstantPosition (csmaNodes1.Get (1), 40.0, 40.0);
	AnimationInterface::SetConstantPosition (csmaNodes1.Get (2), 50.0, 40.0);
	AnimationInterface anim ("Q.xml");

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
