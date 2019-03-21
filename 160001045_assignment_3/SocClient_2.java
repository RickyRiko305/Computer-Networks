import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.io.PrintWriter;
public class SocClient_2
{
     public static void main(String[] args)throws Exception
     {
       String ip="localhost";
       int port=9999;
       Socket s=new Socket(ip,port);
       //ServerSocket ss=new ServerSocket(9999);
       //String str="hello its client_2";
       // OutputStreamWriter os=new OutputStreamWriter(s.getOutputStream());
       // PrintWriter out=new PrintWriter(os);
       // os.write(str);
      // System.out.println("client waiting");
       BufferedReader br=new BufferedReader(new InputStreamReader(s.getInputStream()));
      String str=br.readLine();
       System.out.println("Client_1 Data :"+str);
       //os.flush();
     }
}
