package abc;

import java.io.UnsupportedEncodingException;
import org.jnetpcap.Pcap;
import org.jnetpcap.packet.JPacket;
import org.jnetpcap.packet.JPacketHandler;
import org.jnetpcap.protocol.tcpip.Tcp;
import org.jnetpcap.protocol.tcpip.Udp;
import org.jnetpcap.protocol.tcpip.Http;
import org.jnetpcap.protocol.network.Ip4;
import org.jnetpcap.protocol.network.Ip6;


public class count
{
 
  static int tcpcount = 0;
  static int udpcount = 0;
  static int httpcount = 0;
  static int ip4count = 0;
  static int ip6count = 0;
    public static void main(String[] args)
    {
        String FILENAME = "/home/cse/Downloads/1.pcap";
        StringBuilder errbuf = new StringBuilder();
        Pcap pcap = Pcap.openOffline(FILENAME, errbuf);
        final Tcp tcp = new Tcp();
        final Udp udp = new Udp();
        final Http http = new Http();
        final Ip4 ip4 = new Ip4();
        final Ip6 ip6 = new Ip6();
       
       
       
       
        pcap.loop(-1, new JPacketHandler<StringBuilder>()
        {
            int i=1;
            public void nextPacket(JPacket packet, StringBuilder errbuf)
            {
               
               
                if(packet.hasHeader(tcp))
                {   
                        tcpcount++;
                }
                if(packet.hasHeader(udp))
                {   
                    udpcount++;
                }
                if(packet.hasHeader(http))
                {    byte[] str = http.getPayload();
                    try {
                        String s = new String(str,"UTF-8");
                        if(s.length()!=0)
                        {
                            System.out.println(s.charAt(0));
                            System.out.println(s.charAt(s.length()-1));
                        }
                    } catch (UnsupportedEncodingException e) {
                        // TODO Auto-generated catch block
                        e.printStackTrace();
                    }
                    httpcount++;
                    int length = http.getPayloadLength();
                    System.out.println("Packet "+i+": Payloadlength "+length);
                    i++;
                }
                if(packet.hasHeader(ip4))
                {   
                    ip4count++;
                }
                if(packet.hasHeader(ip6))
                {   
                    ip6count++;
                }
            }
        },errbuf);
        System.out.println("Tcp count is "+tcpcount);   
        System.out.println("Udp count is "+udpcount);
        System.out.println("Http count is "+httpcount);
        System.out.println("Ip4 count is "+ip4count);
        System.out.println("Ip6 count is "+ip6count);
    }
}
