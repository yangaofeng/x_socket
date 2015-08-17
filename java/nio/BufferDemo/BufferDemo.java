import java.io.*;
import java.nio.*;
import java.nio.channels.*;

public class BufferDemo {
    public static void main(String[] args)
    {
        try {

            RandomAccessFile aFile = new RandomAccessFile("a.txt", "rw");
            FileChannel inChannel = aFile.getChannel();

            ByteBuffer buf = ByteBuffer.allocate(48);
            
            int bytesRead = inChannel.read(buf);
            while (bytesRead != -1) {
                buf.flip();
                while (buf.hasRemaining()) {
                    System.out.print((char)buf.get());
                }

                buf.clear();
                bytesRead = inChannel.read(buf);
            }

            aFile.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
