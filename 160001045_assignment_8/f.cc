#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"


using namespace ns3;


NS_LOG_COMPONENT_DEFINE ("OnOff_Example");

int
main (int argc, char *argv[])
{
        CommandLine cmd;
        cmd.Parse (argc, argv);

        NodeContainer nodes,nodes01,nodes12,nodes13;
        nodes.Create (4);
        nodes01.Add(nodes.Get(0));
	nodes01.Add(nodes.Get(1));
	nodes12.Add(nodes.Get(1));
	nodes12.Add(nodes.Get(2));
        nodes13.Add(nodes.Get(1));
	nodes13.Add(nodes.Get(3));

	 
	PointToPointHelper p2pHelper01;
	p2pHelper01.SetChannelAttribute ("Delay", StringValue ("1ms"));
	p2pHelper01.SetQueue("ns3::DropTailQueue");
	p2pHelper01.SetDeviceAttribute ("DataRate", StringValue ("200kbps"));
	
	PointToPointHelper p2pHelper12;
	p2pHelper12.SetChannelAttribute ("Delay", StringValue ("1ms"));
        p2pHelper12.SetQueue("ns3::DropTailQueue");
	p2pHelper12.SetDeviceAttribute ("DataRate", StringValue ("200kbps"));  

	PointToPointHelper p2pHelper13;
	p2pHelper13.SetChannelAttribute ("Delay", StringValue ("1ms"));
        p2pHelper13.SetQueue("ns3::DropTailQueue");
	p2pHelper13.SetDeviceAttribute ("DataRate", StringValue ("200kbps")); 


        NetDeviceContainer devices;
        devices = p2pHelper01.Install (nodes01);

        NetDeviceContainer devices12;	
	devices12 = p2pHelper12.Install (nodes12);
        
        NetDeviceContainer devices13;	
	devices13 = p2pHelper13.Install (nodes13);

        InternetStackHelper stack;
        stack.Install (nodes);

        Ipv4AddressHelper address;

        address.SetBase ("10.1.1.0", "255.255.255.0");
        Ipv4InterfaceContainer interfaces = address.Assign (devices);


	
	// Defining addresses for nodes 0, 1
	address.SetBase ("10.1.2.0", "255.255.255.0");
	Ipv4InterfaceContainer interface12 = address.Assign (devices12);

        address.SetBase ("10.1.3.0", "255.255.255.0");
	Ipv4InterfaceContainer interface13 = address.Assign (devices13);

	
        
//------------------------------------------------------------------------------------------------------------------------------------------------
        uint16_t port = 9999;

        OnOffHelper onoffHelper("ns3::TcpSocketFactory", InetSocketAddress(interface12.GetAddress(1), port));
	onoffHelper.SetAttribute ("DataRate", StringValue ("10Mbps"));
	onoffHelper.SetAttribute ("PacketSize", UintegerValue(1000));
	onoffHelper.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=10]"));
	onoffHelper.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));



 	//OnOffHelper onoffHelper1("ns3::TcpSocketFactory", InetSocketAddress(interface13.GetAddress(1), port));
	//onoffHelper1.SetAttribute ("DataRate", StringValue ("10Mbps"));
	//onoffHelper1.SetAttribute ("PacketSize", UintegerValue(1000));
	//onoffHelper1.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=10]"));
	//onoffHelper1.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	
        ApplicationContainer app = onoffHelper.Install (nodes.Get(0)); //source
    	app.Start (Seconds (0.0));
    	app.Stop (Seconds (0.10));

    	PacketSinkHelper sink("ns3::TcpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), port));   //destination	
        app = sink.Install(nodes12.Get(1));
    	app.Start (Seconds (0.0));
    	app.Stop (Seconds (0.10));



       
	
        ApplicationContainer app1 = onoffHelper.Install (nodes.Get(3)); //source
    	app1.Start (Seconds (0.0));
    	app1.Stop (Seconds (0.10));

    	PacketSinkHelper sink1("ns3::TcpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), port));   //destination	
        app1 = sink1.Install(nodes13.Get(1));
    	app1.Start (Seconds (0.0));
    	app1.Stop (Seconds (0.10));




//--------------------------------------------------------------------------------------------------------------

// Applying Global routing
        Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

        // Using NetAnim
	AnimationInterface::SetConstantPosition (nodes.Get (0), 10.0, 20.0);
	AnimationInterface::SetConstantPosition (nodes.Get (1), 20.0, 20.0);
	AnimationInterface::SetConstantPosition (nodes.Get (2), 30.0, 20.0);
	AnimationInterface::SetConstantPosition (nodes.Get (3), 20.0, 30.0);
	
	AnimationInterface anim ("OF_anim.xml"); 

        AsciiTraceHelper ascii;
        p2pHelper01.EnableAsciiAll (ascii.CreateFileStream ("OnOff.tr"));
        p2pHelper01.EnablePcapAll ("OnOff");


        Simulator::Stop(Seconds(0.11));
        Simulator::Run ();
        Simulator::Destroy ();


  return 0;
}
