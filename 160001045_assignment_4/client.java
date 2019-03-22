import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.io.*;
public class client
{
     public static void main(String[] args)throws Exception
     {
       String ip="localhost";
       int port=9999;
       Socket s=new Socket(ip,port);

       BufferedReader br=new BufferedReader(new InputStreamReader(s.getInputStream()));
      String str=br.readLine();
       System.out.println("Client_1 Data :"+str);
       File file = new File("./textClient.txt");
       BufferedWriter writer =new BufferedWriter(new FileWriter(file));
       writer.write(str);
       writer.close();
     }
}
