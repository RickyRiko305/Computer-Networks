import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

public class SocServer
{
  public static void main(String[] args)throws Exception
  {
      System.out.println("Server started");
      String ip="localhost";
      ServerSocket ss=new ServerSocket(9999);
      System.out.println("Server waiting");
      Socket s=ss.accept();
      System.out.println("Connected");
      BufferedReader br=new BufferedReader(new InputStreamReader(s.getInputStream()));
      String str=br.readLine();
      System.out.println("Client Data :"+str);
      int port=9999;

      System.out.println("Server waiting");
       s=ss.accept();
      System.out.println("Connected");
      OutputStreamWriter os=new OutputStreamWriter(s.getOutputStream());
      PrintWriter out=new PrintWriter(os);
      os.write(str);
      os.flush();
} }
