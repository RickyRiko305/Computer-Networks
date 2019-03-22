import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.*;
public class mainServer
{
  public static void main(String[] args)throws Exception
  {
       System.out.println("Server started");
      // String ip="localhost_1";
      // ServerSocket ss=new ServerSocket(9999);
      // System.out.println("Server waiting");
      // Socket s=ss.accept();
      // System.out.println("Connected");
      // BufferedReader br=new BufferedReader(new InputStreamReader(s.getInputStream()));
      // String str=br.readLine();
      // System.out.println("Client Data :"+str);
      ServerSocket ss = new ServerSocket(9999);

      // running infinite loop for getting
      // client request

          Socket s = null;

            // socket object to receive incoming client requests
              s = ss.accept();

              System.out.println("A new client is connected : " + s);

              // obtaining input and out streams
              DataInputStream dis = new DataInputStream(s.getInputStream());
              DataOutputStream dos = new DataOutputStream(s.getOutputStream());
      // File file = new File("./text.txt");
      // BufferedReader br=new BufferedReader(new FileReader(file));
      // String str = br.readLine();
      //
      //  StringBuilder sb = new StringBuilder();
      // while(str != null){
      //
      //   sb.append(str).append("\n");
      //       str = br.readLine();
      // }
      while(true){
        String received = dis.readUTF();
        String str = received;
        System.out.println("receive data " + str);
        String string1 = new String("magazine");
        String string2 = new String("Practice");
        String string3 = new String("Geeks");

        if(str.matches("magazine")){
          // OutputStreamWriter os=new OutputStreamWriter(s.getOutputStream());
          // PrintWriter out=new PrintWriter(os);
          //System.out.println(sb);
          //str = sb;
            System.out.println("data send");
          String str1 = "magazine send";
          dos.writeUTF(str1);
          // os.write(str1);
          // os.flush();
        }
        else if(str.matches("politics")){
        //  OutputStreamWriter os=new OutputStreamWriter(s.getOutputStream());
        //  PrintWriter out=new PrintWriter(os);
          //System.out.println(sb);
          //str = sb;
          String str1 = "politics send";
          // os.write(str1);
          // os.flush();
          dos.writeUTF(str1);
          // os.write(str+ " send");
          // os.flush();
        }
        else if(str.matches("economic")){
          // OutputStreamWriter os=new OutputStreamWriter(s.getOutputStream());
          // PrintWriter out=new PrintWriter(os);
          //System.out.println(sb);
          //str = sb;
          String str1 = "economic send";
          dos.writeUTF(str1);
          // os.write(str1);
          // os.flush();
          // os.write(str+ " send");
          // os.flush();
        }
        else{
          // OutputStreamWriter os=new OutputStreamWriter(s.getOutputStream());
          // PrintWriter out=new PrintWriter(os);
          // //System.out.println(sb);
          // //str = sb;
          String str1 = "no match";
          dos.writeUTF(str1);
          // os.write(str+ " not present");
          // os.flush();
        }

      }
       // s.close();
       // dis.close();
       // dos.close();

} }
