import java.io.*;
import java.text.*;
import java.util.*;
import java.net.*;



public class server
{

    public static void main(String[] args) throws IOException
    {

        ServerSocket ss = new ServerSocket(5056);


        while (true)
        {
            Socket s = null;

            try
            {

                s = ss.accept();

                System.out.println("A new client is connected : " + s);


                DataInputStream dis = new DataInputStream(s.getInputStream());
                DataOutputStream dos = new DataOutputStream(s.getOutputStream());

                System.out.println("Assigning new thread for this client");


                Thread t = new ClientHandler(s, dis, dos);


                t.start();

            }
            catch (Exception e){
                s.close();
                e.printStackTrace();
            }
        }
    }
}


class ClientHandler extends Thread
{
    DateFormat fordate = new SimpleDateFormat("yyyy/MM/dd");
    DateFormat fortime = new SimpleDateFormat("hh:mm:ss");
    final DataInputStream dis;
    final DataOutputStream dos;
    final Socket s;



    public ClientHandler(Socket s, DataInputStream dis, DataOutputStream dos)
    {
        this.s = s;
        this.dis = dis;
        this.dos = dos;
    }

    @Override
    public void run()
    {
        String received;
        String toreturn;
        while (true)
        {
            try {


                dos.writeUTF("What do you want?[]..\n"+
                            "Type Exit to terminate connection.");


                received = dis.readUTF();

                if(received.equals("Exit"))
                {
                    System.out.println("Client " + this.s + " sends exit...");
                    System.out.println("Closing this connection.");
                    this.s.close();
                    System.out.println("Connection closed");
                    break;
                }


                Date date = new Date();


                //Socket mainS = new ServerSocket(9999);
                //String ip_1 = "localhost";
                InetAddress ip_1 = InetAddress.getByName("localhost");
                Socket s_1 = new Socket(ip_1, 9999);
                System.out.println("mainserver");

          			DataInputStream dis_1 = new DataInputStream(s_1.getInputStream());
          			DataOutputStream dos_1 = new DataOutputStream(s_1.getOutputStream());



          				//System.out.println(dis_1.readUTF());
          				String tosend = received; //scn.nextLine();
                  System.out.println("send data\n");
          				dos_1.writeUTF(tosend);


          				if(tosend.equals("Exit"))
          				{
          					System.out.println("Closing this connection : " + s_1);
          					s_1.close();
          					System.out.println("Connection closed");
          					break;
          				}

                  System.out.println("receive data\n");
          				String rev ;
                  rev = dis_1.readUTF();
          				System.out.println(rev);
          			  // dos.writeUFT(rev);
                  dos.writeUTF(rev);
                  s_1.close();
                dis_1.close();
            			dos_1.close();
                // switch (received) {
                //
                //     case "Date" :
                //
                //         toreturn = fordate.format(date);
                //         dos.writeUTF(toreturn);
                //         break;
                //
                //     case "Time" :
                //         toreturn = fortime.format(date);
                //         dos.writeUTF(toreturn);
                //         break;
                //
                //     default:
                //         dos.writeUTF("Invalid input");
                //         break;
                // }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        try
        {
            // closing resources
            this.dis.close();
            this.dos.close();

        }catch(IOException e){
            e.printStackTrace();
        }
    }
}
