import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.*;
public class server
{
  public static void main(String[] args)throws Exception
  {
      System.out.println("Server started");
      String ip="localhost";
      ServerSocket ss=new ServerSocket(9999);
      System.out.println("Server waiting");
      Socket s=ss.accept();
      System.out.println("Connected");
      File file = new File("./text.txt");
      BufferedReader br=new BufferedReader(new FileReader(file));
      String str = br.readLine();
      //String val;
       StringBuilder sb = new StringBuilder();
      while(str != null){
        //val += str;
        sb.append(str).append("\n");
            str = br.readLine();
      }
      // String str=br.readLine();
      // System.out.println("Client Data :"+str);
      // int port=9999;
      //
      // System.out.println("Server waiting");
      //  s=ss.accept();
      // System.out.println("Connected");
      OutputStreamWriter os=new OutputStreamWriter(s.getOutputStream());
      PrintWriter out=new PrintWriter(os);
      System.out.println(sb);
      //str = sb;
      os.write(sb.toString());
      os.flush();
} }
