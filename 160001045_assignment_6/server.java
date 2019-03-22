import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.*;
import java.util.StringTokenizer;
public class server
{
  public static void main(String[] args)throws Exception
  {
       System.out.println("Server started");


      try{
        ServerSocket ss=new ServerSocket(9999);
        Socket s=ss.accept();//establishes connection
        DataInputStream dis=new DataInputStream(s.getInputStream());
        DataOutputStream dos = new DataOutputStream(s.getOutputStream());
        String  str=(String)dis.readUTF();
        System.out.println("message= "+str);
        StringTokenizer st = new StringTokenizer(str);
        int result;
        int num1 = Integer.parseInt(st.nextToken());
            String operation = st.nextToken();
            int num2 = Integer.parseInt(st.nextToken());

            if (operation.equals("+"))
            {
                result = num1 + num2;
            }

            else if (operation.equals("-"))
            {
                result = num1 - num2;
            }
            else if (operation.equals("*"))
            {
                result = num1 * num2;
            }
            else
            {
                result = num1 / num2;
            }
        while(st.hasMoreTokens()){
          //int num1 = Integer.parseInt(st.nextToken());
              operation = st.nextToken();
              int num3 = Integer.parseInt(st.nextToken());

              if (operation.equals("+"))
              {
                  result += num3;
              }

              else if (operation.equals("-"))
              {
                  result -= num3;
              }
              else if (operation.equals("*"))
              {
                  result *= num3;
              }
              else
              {
                  result /= num3;
              }
        }

            System.out.println("Sending the result...");

            // send the result back to the client.
            dos.writeUTF(Integer.toString(result));
        ss.close();
      }
      catch(Exception e){
        System.out.println(e);
      }


  }

 }
