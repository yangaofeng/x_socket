import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.Date;
import java.util.Set;

public class Client {
    private static ByteBuffer send_buf_ = ByteBuffer.allocate(1024);
    private static ByteBuffer recv_buf_ = ByteBuffer.allocate(1024);

    private InetSocketAddress SERVER;
    private static Selector selector_;
    private static SocketChannel client_;
    private static String receive_text_;
    private static String send_text_;
    private static int count_ = 0;

    public Client(int port) {
        SERVER = new InetSocketAddress("localhost", port);
        init();
    }

    public void init() {
        try {
            SocketChannel socket_channel = SocketChannel.open();
            socket_channel.configureBlocking(false);
            selector_ = selector_.open();
            socket_channel.register(selector_, SelectionKey.OP_CONNECT);
            socket_channel.connect(SERVER);

            while (true) {
                selector_.select();
                Set<SelectionKey> key_set = selector_.selectedKeys();
                for (final SelectionKey key: key_set) {
                    handle(key);
                }
                key_set.clear();
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String args[]) throws IOException {
        Client client = new Client(7777);
    }

    private void handle(SelectionKey selection_key) throws IOException {
        if (selection_key.isConnectable()) {
            client_ = (SocketChannel) selection_key.channel();
            if (client_.isConnectionPending()) {
                client_.finishConnect();
                System.out.println("connect success");
                send_buf_.clear();
                send_buf_.put((new Date().toLocaleString() + " connected!").getBytes());
                send_buf_.flip();
                client_.write(send_buf_);

                new Thread() {
                    @Override
                    public void run() {
                        while (true) {
                            try {
                                send_buf_.clear();
                                InputStreamReader input = 
                                    new InputStreamReader(System.in);
                                BufferedReader br = new BufferedReader(input);
                                send_text_ = br.readLine();
                                send_buf_.put(send_text_.getBytes());
                                send_buf_.flip();
                                client_.write(send_buf_);
                            } catch (IOException e) {
                                e.printStackTrace();
                                break;
                            }
                        }
                    }
                }.start();
            }

            client_.register(selector_, SelectionKey.OP_READ);

        } else if (selection_key.isReadable()) {
            client_ = (SocketChannel) selection_key.channel();
            recv_buf_.clear();
            count_ = client_.read(recv_buf_);
            if (count_ > 0) {
                receive_text_ = new String(recv_buf_.array(), 0, count_);
                System.out.println(receive_text_);
                client_ = (SocketChannel) selection_key.channel();
                client_.register(selector_, SelectionKey.OP_READ);
            }
        }
    }

}
