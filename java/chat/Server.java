import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.nio.charset.Charset;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;


public class Server {
    private int port_ = 7777;
    private Charset cs_ = Charset.forName("gbk");
    private static ByteBuffer send_buf_ = ByteBuffer.allocate(1024);
    private static ByteBuffer recv_buf_ = ByteBuffer.allocate(1024);
    private static Map<String, SocketChannel> clients_map_ =  
        new HashMap<String, SocketChannel>();

    private static Selector selector_;

    public Server(int port) {
        this.port_ = port;
        try {
            Init();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void Init() throws IOException {
        ServerSocketChannel server_ = ServerSocketChannel.open();
        server_.configureBlocking(false);
        ServerSocket server_socket_ = server_.socket();
        server_socket_.bind(new InetSocketAddress(port_));
        selector_ = Selector.open();
        server_.register(selector_, SelectionKey.OP_ACCEPT);

        System.out.println("server start on port: " + port_);
    }

    private void Listen() {
        while (true) {
            try {
                selector_.select();
                Set<SelectionKey> selection_keys = selector_.selectedKeys();
                for (SelectionKey key: selection_keys) {
                    handle(key);
                }
                selection_keys.clear();
            } catch (Exception e) {
                e.printStackTrace();
                break;
            }
        }
    }

    private void handle(SelectionKey selection_key) throws IOException {
        ServerSocketChannel server = null;
        SocketChannel client = null;
        String receive_text = null;
        int count = 0;

        if (selection_key.isAcceptable()) {
            server = (ServerSocketChannel) selection_key.channel();
            client = server.accept();
            client.configureBlocking(false);
            client.register(selector_, SelectionKey.OP_READ);
        } else if (selection_key.isReadable()) {
            client = (SocketChannel)selection_key.channel();
            recv_buf_.clear();
            count = client.read(recv_buf_);
            if (count > 0) {
                recv_buf_.flip();
                receive_text = String.valueOf(cs_.decode(recv_buf_).array());
                System.out.println(client.toString() + ":" + receive_text);
                dispatch(client, receive_text);
                client = (SocketChannel)selection_key.channel();
                client.register(selector_, SelectionKey.OP_READ);
            }
        } 
    }

    private void dispatch(SocketChannel client, String info) throws IOException {
        Socket s = client.socket();
        String name = "[" + s.getInetAddress().toString().substring(1) + 
            ":" + Integer.toHexString(client.hashCode()) + "]";
        if (!clients_map_.isEmpty()) {
            for (Map.Entry<String, SocketChannel> entry: clients_map_.entrySet()) {
                SocketChannel temp = entry.getValue();
                if (!client.equals(temp)) {
                    send_buf_.clear();
                    send_buf_.put((name + ":" + info).getBytes());
                    send_buf_.flip();
                    temp.write(send_buf_);
                }
            }
        }
        clients_map_.put(name, client);
    }

    public static void main(String args[]) throws IOException {
        Server s = new Server(7777);
        s.Listen();
    }
}

