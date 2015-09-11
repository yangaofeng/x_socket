
public class Cmd {
    public static void main(String[] args) {
        try {
            //usage, java Cmd abc bcd cde
            System.out.println(args[0]);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
