public class ClassDemo {
    public static void main(String[] args) {
        try {
            String name = "caterpillar";
            Class stringClass = name.getClass();
            //Class stringClass = int.class;
            System.out.println("类名称: " + stringClass.getName());
            System.out.println("是否为接口: " + stringClass.isInterface());
            System.out.println("是否为基本类型:" + stringClass.isPrimitive());
            System.out.println("是否为数组:" + stringClass.isArray());
            System.out.println("父类名称:" + stringClass.getSuperclass().getName());
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
