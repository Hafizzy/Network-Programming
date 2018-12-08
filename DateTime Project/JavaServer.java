import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.net.ServerSocket;
import java.net.Socket;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class JavaServer
{
  public static void main(String[] args)throws IOException
 { 
   ServerSocket ss = new ServerSocket(3030);

   while (true)
  { 
    Socket s = ss.accept();
    System.out.println("new socket" + s.getLocalSocketAddress() + " " + s.getRemoteSocketAddress());

    Calendar cal = Calendar.getInstance();
    Date date=cal.getTime();
    DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");

    String formattedDate=dateFormat. format(date);

    try (Write out = new OutputStreamWriter(s.getOutputStream()))
    {
      out.write(formattedDate);
      out.flush();
    }
   }
  }
}