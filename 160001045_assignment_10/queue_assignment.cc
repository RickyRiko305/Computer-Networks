#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/traffic-control-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Queue_3_Example");

void CheckQueueSize (Ptr<Queue<Packet>> q1, const char* name)
{
    std::cout << std::endl;
    uint32_t qSize = q1->GetCurrentSize().GetValue();
      std::cout<<"Queue size of "<< name <<" is "<<qSize<<" at "<<Simulator::Now().GetSeconds()<<std::endl;
     Simulator::Schedule(Seconds(.0010), &CheckQueueSize, q1,name);
}

int main (int argc , char * argv[])
{
    CommandLine cmd;
    cmd.Parse(argc,argv);
    Time :: SetResolution (Time :: NS);
    LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
    NodeContainer nodes,nodes02,nodes12,nodes23;
    nodes.Create(4);
    nodes02.Add(nodes.Get(0));
    nodes02.Add(nodes.Get(2));
    nodes12.Add(nodes.Get(1));
    nodes12.Add(nodes.Get(2));
    nodes23.Add(nodes.Get(2));
    nodes23.Add(nodes.Get(3));

    PointToPointHelper p2pHelper;
    p2pHelper.SetChannelAttribute ("Delay",StringValue ("1ms"));
    p2pHelper.SetQueue("ns3::DropTailQueue");
    p2pHelper.SetDeviceAttribute ("DataRate",StringValue ("1Mbps"));

     NetDeviceContainer devices02,devices12,devices23;
    devices02 = p2pHelper.Install (nodes02);
    devices12 = p2pHelper.Install (nodes12);
    devices23 = p2pHelper.Install (nodes23);

    InternetStackHelper stack;
    stack.Install (nodes);

    Ipv4AddressHelper address;
    address.SetBase ("10.1.1.0","255.255.255.0");
    Ipv4InterfaceContainer interfaces02 = address.Assign (devices02);
    address.SetBase ("10.1.2.0","255.255.255.0");
    Ipv4InterfaceContainer interfaces12 = address.Assign (devices12);
    address.SetBase ("10.1.3.0","255.255.255.0");
    Ipv4InterfaceContainer interfaces23 = address.Assign (devices23);

    uint16_t port = 9999;

    OnOffHelper onoffHelper01 ("ns3::UdpSocketFactory",InetSocketAddress(interfaces23.GetAddress(1), port));
    onoffHelper01.SetAttribute ("DataRate", StringValue ("10Mbps"));
    onoffHelper01.SetAttribute ("PacketSize", UintegerValue(1000));
    onoffHelper01.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=10]"));
    onoffHelper01.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));

    ApplicationContainer app1 = onoffHelper01.Install (nodes.Get(0));
    app1.Start (Seconds (0.0));
    app1.Stop (Seconds (0.10));

    //uint16_t port1 = 9000;
    // OnOffHelper onoffHelper02 ("ns3::UdpSocketFactory",InetSocketAddress(interfaces23.GetAddress(1), port1));
    // onoffHelper02.SetAttribute ("DataRate", StringValue ("10Mbps"));
    // onoffHelper02.SetAttribute ("PacketSize", UintegerValue(1000));
    // onoffHelper02.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=10]"));
    // onoffHelper02.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
    //
    // ApplicationContainer app2 = onoffHelper02.Install (nodes.Get(1));
    // app2.Start (Seconds (0.0));
    // app2.Stop (Seconds (0.10));

    PacketSinkHelper sink("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), port));
    //PacketSinkHelper sink1("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), port1));

    app1 = sink.Install(nodes.Get(3));
    app1.Start (Seconds (0.0));
    app1.Stop (Seconds (0.10));

    // app2 = sink1.Install(nodes.Get(3));
    // app2.Start (Seconds (0.0));
    // app2.Stop (Seconds (0.10));

    Ipv4GlobalRoutingHelper::PopulateRoutingTables ();


    Ptr<PointToPointNetDevice> nd1 = StaticCast<PointToPointNetDevice> (devices02.Get (0));
    Ptr<Queue<Packet> > queue1 = nd1->GetQueue();
    Simulator::ScheduleNow(&CheckQueueSize, queue1,"Dev1");

    // Ptr<PointToPointNetDevice> nd2 = StaticCast<PointToPointNetDevice> (devices12.Get (0));
    // Ptr<Queue<Packet> > queue2 = nd2->GetQueue();
    // Simulator::ScheduleNow(&CheckQueueSize, queue1,"Dev2");
    //
    // Ptr<PointToPointNetDevice> nd3 = StaticCast<PointToPointNetDevice> (devices02.Get (1));
    // Ptr<Queue<Packet> > queue3 = nd3->GetQueue();
    // Simulator::ScheduleNow(&CheckQueueSize, queue3,"Dev3");
    //
    // Ptr<PointToPointNetDevice> nd4 = StaticCast<PointToPointNetDevice> (devices23.Get (1));
    // Ptr<Queue<Packet> > queue4 = nd4->GetQueue();
    // Simulator::ScheduleNow(&CheckQueueSize, queue4,"Dev3");

    Simulator::Stop (Seconds (0.2));
    Simulator::Run ();


    Ptr<PacketSink> sink123 = DynamicCast<PacketSink> (app1.Get(0));
    std::cout << "total bytes Received from app1: " << sink123->GetTotalRx () << std::endl;

    // Ptr<PacketSink> sink1234 = DynamicCast<PacketSink> (app2.Get(0));
    // std::cout << "total bytes Received from app2: " << sink1234->GetTotalRx () << std::endl;

}
