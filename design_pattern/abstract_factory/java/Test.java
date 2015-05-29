public class Test {

    //测试类，没什么意义
    interface Sender {
        public void Send();
    }

    class MailSender implements Sender {
        @Override
        public void Send() {
            System.out.println("this is mailsender!");
        }
    }

    class SmsSender implements Sender {
        @Override
        public void Send() {
            System.out.println("this is smssender!");
        }
    }

    //抽象工厂
    interface Provider {
        public Sender produce();
    }

    //两个工厂实现类
    class MailSenderFactory implements Provider {
        @Override
        public Sender produce() {
            return new MailSender();
        }
    }

    class SmsSenderFactory implements Provider {
        @Override
        public Sender produce() {
            return new SmsSender();
        }
    }

    public static void main(String[] args) {
        Provider provider = new SmsSenderFactory();
        Sender sender = provider.produce();
        sender.Send();
    }
}

